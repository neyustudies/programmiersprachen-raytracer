#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <glm/vec3.hpp>
#include "shape.hpp"
#include "light.hpp"

/**
 * A scene that can be rendered, consisting of shapes and point light sources.
 */
struct Scene {
  std::vector<Shape> shapes;
  std::vector<Light> lights;
  const glm::vec3 camera_pos{0, 0, 0};
  const glm::vec3 camera_direction{0, 0, -1};
};

#endif  // SCENE_HPP
