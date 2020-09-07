#include "sdfparser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "shape.hpp"
#include "box.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "render.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "composite.hpp"

Color parse_color(std::istringstream &in);
glm::vec3 parse_vec3(std::istringstream &in);
std::shared_ptr<Material> parse_material(std::istringstream& in,
                                         Scene const& scene,
                                         int line);

void warn_unknown(std::string what, std::string name, int line) {
  std::cerr << "[Warning][SDF] In line " << line << ", ignoring unknown "
            << what << " '" << name << "'.\n";
}

Scene read_from_sdf(std::string const& filename) {
  Scene scene;
  std::ifstream in_file(filename, std::ios::in);
  std::string line_buf;
  std::size_t line = 0;

  while(std::getline(in_file, line_buf)) {
    ++line;
    std::istringstream in(line_buf);
    std::string identifier;
    in >> identifier;

    if ("#" == identifier || identifier.empty() || identifier[0] == '#') {
      continue;
    } else if ("define" == identifier) {
      std::string class_name;
      std::string object_name;
      in >> class_name;
      in >> object_name;
      if ("material" == class_name) {
        auto ka = parse_color(in);
        auto kd = parse_color(in);
        auto ks = parse_color(in);
        float m;
        in >> m;
        float r;
        in >> r;
        Material material{object_name, ka, kd, ks, m, r};
        scene.materials.emplace(object_name, material);
      } else if ("shape" == class_name) {
        std::string name;
        in >> name;
        if ("sphere" == object_name) {
          auto center = parse_vec3(in);
          float radius;
          in >> radius;
          auto material = parse_material(in, scene, line);
          if (nullptr == material)
            continue;
          Sphere s{center, radius, name, material};
          scene.shapes.push_back(std::make_shared<Sphere>(s));
        } else if ("box" == object_name) {
          auto p1 = parse_vec3(in);
          auto p2 = parse_vec3(in);
          auto material = parse_material(in, scene, line);
          if (nullptr == material)
            continue;
          Box b{p1, p2, name, material};
          scene.shapes.push_back(std::make_shared<Box>(b));
        } else if ("triangle" == object_name) {
          auto a = parse_vec3(in);
          auto b = parse_vec3(in);
          auto c = parse_vec3(in);
          auto material = parse_material(in, scene, line);
          if (nullptr == material)
            continue;
          Triangle t{a, b, c, name, material};
          scene.shapes.push_back(std::make_shared<Triangle>(t));
        } else if ("composite" == object_name) {
          Composite c{name};
          std::string child;
          while (!in.eof()) {
            in >> child;
            auto it = scene.shapes.begin();
            while((*it)->name() != child) ++it;
            c.add(*it);
          } scene.shapes.push_back(std::make_shared<Composite>(c));
        } else {
          warn_unknown("shape", object_name, line);
        }
      } else if ("light" == class_name) {
        auto pos = parse_vec3(in);
        auto color = parse_color(in);
        float brightness;
        in >> brightness;
        Light light{object_name, pos, color, brightness};
        scene.lights.push_back(light);
      } else if ("camera" == class_name) {
        float fov;
        in >> fov;
        auto eye = parse_vec3(in);
        auto dir = parse_vec3(in);
        auto up  = parse_vec3(in);
        Camera camera{object_name, fov, eye, dir, up};
        scene.cameras.emplace(object_name, camera);
      } else {
        warn_unknown("class", class_name, line);
      }
    } else if ("ambient" == identifier) {
      scene.ambient = parse_color(in);
    } else if ("render" == identifier) {
      std::string camera_name;
      in >> camera_name;
      auto camera_it = scene.cameras.find(camera_name);
      if (scene.cameras.end() == camera_it) {
        warn_unknown("camera", camera_name, line);
        continue;
      }
      auto camera = std::make_shared<Camera>(camera_it->second);
      std::string filename;
      in >> filename;
      unsigned x_res;
      in >> x_res;
      unsigned y_res;
      in >> y_res;
      unsigned subpixels;
      in >> subpixels;
      Render render{camera, filename, x_res, y_res, subpixels};
      scene.renders.push_back(render);
    } else if ("transform" == identifier) {
      std::string shape_name;
      in >> shape_name;
      auto it = scene.shapes.begin();
      while ((*it)->name() != shape_name) ++it;
      std::shared_ptr<Shape> object = *it;
      std::string transform_type;   
      in >> transform_type;
      if ("rotate" == transform_type) { 
        float angle;
        in >> angle;
        angle = angle / 360 * M_PI * 2;
        auto axis = parse_vec3(in);
        object->rotate(angle, axis);
      } else if ("scale" == transform_type) {
        auto point = parse_vec3(in);
        object->scale(point);
      } else if ("translate" == transform_type) {
        auto point = parse_vec3(in);
        object->translate(point);
      } else {
        warn_unknown("transform_type", shape_name, line);
      }
    } else {
      warn_unknown("identifier", identifier, line);
    }
  }

  in_file.close();
  std::cerr << "[Info][SDF] Parsed " << line << " lines.\n";
  return scene;
}

Color parse_color(std::istringstream &in) {
  float r, g, b;
  in >> r >> g >> b;
  return Color{r, g, b};
}

glm::vec3 parse_vec3(std::istringstream &in) {
  float x, y, z;
  in >> x >> y >> z;
  return glm::vec3{x, y, z};
}

std::shared_ptr<Material> parse_material(std::istringstream& in,
                                         Scene const& scene,
                                         int line) {
  std::string material_name;
  in >> material_name;
  auto material_it = scene.materials.find(material_name);
  if (scene.materials.end() == material_it) {
    warn_unknown("material", material_name, line);
    return nullptr;
  }
  return std::make_shared<Material>(material_it->second);
}
