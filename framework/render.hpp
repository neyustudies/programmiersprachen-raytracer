#ifndef RENDER_HPP
#define RENDER_HPP

#include "scene.hpp"
#include <memory>

/**
 * Set of instructions that can be used to render a scene in a specified way.
 */
struct Render {
  // std::shared_ptr<Scene> scene;
  std::shared_ptr<Camera> camera;
  std::string filename;
  unsigned x_res;
  unsigned y_res;
};

#endif  // RENDER_HPP
