// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include <glm/glm.hpp>
#include <string>
#include "render.hpp"
#include "scene.hpp"
#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"

class Renderer {
 public:
  Renderer(unsigned w, unsigned h, std::string const& file);

  void render(Scene const& scene, Render const& r);
  void write(Pixel const& p);

  inline std::vector<Color> const& color_buffer() const {
    return color_buffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP
