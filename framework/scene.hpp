#ifndef SCENE_HPP
#define SCENE_HPP

#include <glm/vec3.hpp>
#include <map>
#include <string>
#include <vector>
#include "camera.hpp"
#include "color.hpp"
#include "light.hpp"
#include "render.hpp"
#include "shape.hpp"

/**
 * A scene that can be rendered, consisting of shapes and point light sources.
 */
struct Scene {
  std::map<std::string, Material> materials;
  std::vector<std::shared_ptr<Shape>> shapes;
  std::vector<Light> lights;
  std::map<std::string, Camera> cameras;
  Color ambient;
  std::vector<Render> renders;
};

#endif  // SCENE_HPP
