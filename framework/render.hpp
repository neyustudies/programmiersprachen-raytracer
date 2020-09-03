#ifndef RENDER_HPP
#define RENDER_HPP

#include <memory>
#include <string>
#include "camera.hpp"

/**
 * Set of instructions that can be used to render a scene in a specified way.
 * TODO:  Perhaps rename to `RenderSettings` to avoid confusion w/ `Renderer`?
 */
struct Render {
  std::shared_ptr<Camera> camera;
  std::string filename;
  unsigned x_res;
  unsigned y_res;
  /** Number of subpixels used for antialiasing.  Set to 1 to disable AA. */
  unsigned subpixels = 1;
};

#endif  // RENDER_HPP
