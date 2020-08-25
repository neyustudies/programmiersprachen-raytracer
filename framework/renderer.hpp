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
  Color trace(Ray const& ray, Scene const& scene);
  Color shade(std::shared_ptr<Shape> shape,
              Ray const& ray,
              HitPoint const& hitpoint,
              Scene const& scene);

  void render(Scene const& scene, Render const& r);
  void write(Pixel const& p);
  void tone_mapping(Color& clr);

  inline std::vector<Color> const& color_buffer() const {
    return color_buffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
  std::vector<std::shared_ptr<Shape>> shapes;
};

#endif // #ifndef BUW_RENDERER_HPP
