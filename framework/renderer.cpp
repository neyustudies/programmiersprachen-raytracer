// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
    : width_(w),
      height_(h),
      color_buffer_(w * h, Color{0.0, 0.0, 0.0}),
      filename_(file),
      ppm_(width_, height_) {}

void Renderer::render(Scene const& scene, Render const& r) {
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p{x, y};
      p.color = scene.ambient;

      // TODO: trace rays
      Ray ray = r.camera->ray(x, y, r.x_res, r.y_res);
      for (auto shape : scene.shapes) {
        auto hitpoint = shape->intersect(ray);
        if (hitpoint.did_intersect) {
          //p.color = hitpoint.clr;
          p.color = color_buffer_.at(x * y);
          p.color = trace(ray);
        }
      } 

      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::write(Pixel const& p) {
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_ * p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
              << "pixel out of ppm_ : " << (int)p.x << "," << (int)p.y
              << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}

 Color Renderer::trace(Ray const& ray) {
   float distance = 0.0f;
   std::shared_ptr<Shape> closest_shape = nullptr;
   for (std::shared_ptr<Shape> const& shape : shapes) {
     HitPoint hp = shape->intersect(ray);   
   }
   if (closest_shape != nullptr) {
     return shade(closest_shape, ray, distance);
   }
   return Color{0.1f, 0.1f, 0.3f};
 }

 Color Renderer::shade(std::shared_ptr<Shape> shape, Ray const& ray, float distance) {
   std::shared_ptr<Material> material = shape->material();
   return material->ka + material->kd + material->ks; 
 } 
