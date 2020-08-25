#include "sdfparser.hpp"
#include "box.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "sphere.hpp"
#include "render.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Color parse_color(std::istringstream &in);
glm::vec3 parse_vec3(std::istringstream &in);

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

    if ("#" == identifier || identifier.empty()) {
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
        Material material{object_name, ka, kd, ks, m};
        scene.materials.emplace(object_name, material);
      } else if ("shape" == class_name) {
        std::string name;
        in >> name;
        if ("sphere" == object_name) {
          auto center = parse_vec3(in);
          float radius;
          in >> radius;
          std::string material_name;
          in >> material_name;
          auto material_it = scene.materials.find(material_name);
          if (scene.materials.end() == material_it) {
            warn_unknown("material", material_name, line);
            continue;
          }
          auto material = std::make_shared<Material>(material_it->second);
          Sphere s{center, radius, name, material};
          scene.shapes.push_back(std::make_shared<Sphere>(s));
        } else if ("box" == object_name) {
          auto p1 = parse_vec3(in);
          auto p2 = parse_vec3(in);
          std::string material_name;
          in >> material_name;
          auto material_it = scene.materials.find(material_name);
          if (scene.materials.end() == material_it) {
            warn_unknown("material", material_name, line);
            continue;
          }
          auto material = std::make_shared<Material>(material_it->second);
          Box b{p1, p2, name, material};
          scene.shapes.push_back(std::make_shared<Box>(b));
        } else if ("composite" == object_name) {
            // TODO
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
      Render render{camera, filename, x_res, y_res};
      scene.renders.push_back(render);
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
