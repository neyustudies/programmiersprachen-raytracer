#ifndef SCENE_HPP
#define SCENE_HPP

#include "camera.hpp"
#include "color.hpp"
#include "light.hpp"
#include "shape.hpp"
#include <glm/vec3.hpp>
#include <map>
#include <string>
#include <vector>

/**
 * A scene that can be rendered, consisting of shapes and point light sources.
 */
struct Scene {
  std::map<std::string, Material> materials;
  std::vector<std::shared_ptr<Shape>> shapes;
  std::vector<Light> lights;
  std::vector<Camera> cameras;
  Color ambient;
};

#endif  // SCENE_HPP
