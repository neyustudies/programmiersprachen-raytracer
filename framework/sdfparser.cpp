#include "sdfparser.hpp"
#include "color.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Color parse_color(std::istringstream &in);
glm::vec3 parse_vec3(std::istringstream &in);

void warn_unknown(std::string what, std::string name, int line) {
  std::cerr << "[Warning][SDF] In line " << line << ", ignoring unknown "
            << what << " '" << name << "'\n";
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
          Sphere s{center, radius, object_name, material};
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
          Box b{p1, p2, object_name, material};
          scene.shapes.push_back(std::make_shared<Box>(b));
        } else {
          warn_unknown("shape", object_name, line);
        }
      } else if ("light" == class_name) {
      } else if ("camera" == class_name) {
      } else {
        warn_unknown("class", class_name, line);
      }
    } else if ("render" == identifier) {
      // TODO
    } else {
      warn_unknown("identifier", identifier, line);
    }
  }

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
