// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include <glm/ext.hpp>

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
      // TODO: trace rays
      Ray ray = r.camera->ray(x, y, r.x_res, r.y_res);
      p.color = trace(ray, scene);

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

Color Renderer::trace(Ray const& ray, Scene const& scene) {
  HitPoint closest_hitpoint;
  closest_hitpoint.t = INFINITY;
  std::shared_ptr<Shape> closest_shape = nullptr;

  for (std::shared_ptr<Shape> const& shape : scene.shapes) {
    HitPoint hitpoint = shape->intersect(ray);
    if (hitpoint.did_intersect && closest_hitpoint.t > hitpoint.t) {
      closest_hitpoint = hitpoint;
      closest_shape = shape;
    }
  }

  if (nullptr != closest_shape)
    return shade(closest_shape, ray, closest_hitpoint, scene);
  else
    return scene.ambient;
}

Color Renderer::shade(std::shared_ptr<Shape> shape,
                      Ray const& ray,
                      HitPoint const& hitpoint,
                      Scene const& scene) {
  std::shared_ptr<Material> material = shape->material();

  // simple lighting model
  Color kd_total;
  for (auto const& light : scene.lights) {
    auto hitpoint_to_light =
        Ray{hitpoint.point, glm::normalize(light.pos - hitpoint.point)};
    auto n_dot_i = glm::clamp(
        glm::dot(hitpoint.normal, hitpoint_to_light.direction), 0.f, 1.f);
    bool shadow = false;
    for (auto const& s : scene.shapes) {
      if (shape == s)
        continue;
      if (s->intersect(hitpoint_to_light).did_intersect)
        shadow = true;
    }
    if (!shadow)
      kd_total += light.brightness * light.color * material->kd * n_dot_i;
  }

  return scene.ambient * material->ka + kd_total;
  // return scene.ambient * material->ka + intensity_d * material->kd;
  // intensity_s * material->ks;
}

// tone mapping
void Renderer::tone_mapping(Color& clr) {
  clr.r = clr.r / (clr.r + 1);
  clr.g = clr.g / (clr.g + 1);
  clr.b = clr.b / (clr.b + 1);
}
