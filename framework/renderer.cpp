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
#include "util.hpp"

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
      float subpixel_step = (1.f/std::sqrt(r.subpixels));
      for (float sub_x = 0; sub_x < 1; sub_x += subpixel_step) {
        for (float sub_y = 0; sub_y < 1; sub_y += subpixel_step) {
          // TODO: trace rays
          Ray ray = r.camera->ray(x + sub_x, y + sub_y, r.x_res, r.y_res);
          recursion_depth_ = 0;
          p.color += trace(ray, scene) * (1.f/r.subpixels);
        }
      }
      tone_mapping(p.color);

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

Color Renderer::trace(Ray const& ray,
                      Scene const& scene,
                      std::shared_ptr<Shape> exclude) {
  HitPoint closest_hitpoint;
  closest_hitpoint.t = INFINITY;
  std::shared_ptr<Shape> closest_shape = nullptr;

  for (std::shared_ptr<Shape> const& shape : scene.shapes) {
    if (shape == exclude)
      continue;
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

  Color ka_total = scene.ambient * material->ka;  // ambient
  Color kd_total;
  Color ks_total;
  for (auto const& light : scene.lights) {
    // diffuse
    auto d = glm::normalize(light.pos - hitpoint.point);
    auto hitpoint_to_light = Ray{hitpoint.point + (EPSILON * d), d};
    auto n = hitpoint.normal;
    auto i = hitpoint_to_light.direction;
    auto n_dot_i = glm::clamp(glm::dot(n, i), 0.f, 1.f);

    // specular
    auto r = i - 2 * glm::dot(i, n) * n;
    auto v = hitpoint.direction;
    auto r_dot_v = glm::clamp(glm::dot(r, v), 0.f, 1.f);

    // shadow test
    bool shadow = false;
    for (auto const& s : scene.shapes) {
      if (shape == s)
        continue;
      if (s->intersect(hitpoint_to_light).did_intersect)
        shadow = true;
    }
    if (!shadow) {
      auto l = light.brightness * light.color;
      kd_total += l * material->kd * n_dot_i;
      ks_total += l * material->ks * std::pow(r_dot_v, material->m);
    }
  }

  Color phong = ka_total + kd_total + ks_total;
  if (++recursion_depth_ > 6)
    return phong;

  Color reflection{};
  float r = material->r;
  if (material->r > 0) {
    auto d = glm::reflect(hitpoint.direction, hitpoint.normal);
    reflection = trace({hitpoint.point, d}, scene, shape);
  }
  Color with_reflection{(1.f - r) * phong + (r * reflection)};

  Color refraction{};
  float o = material->opacity;
  if (material->opacity < 1) {
    auto direction_internal = glm::normalize(
        glm::refract(hitpoint.direction, hitpoint.normal, 1.f / material->n));
    Ray ray_internal{hitpoint.point + EPSILON * direction_internal,
                     direction_internal};
    auto hit_exit = shape->intersect(ray_internal);
    if (hit_exit.did_intersect) {
      auto direction_exit = glm::normalize(glm::refract(
          hit_exit.direction, -hit_exit.normal, 1.f / material->n));
      Ray ray_exit{hit_exit.point + EPSILON * direction_exit, direction_exit};
      refraction = trace(ray_exit, scene, shape);
    }
  }
  return o * with_reflection + (1.f - o) * refraction;

  // return (1.f - material->opacity) * behind + material->opacity * color;
}

// tone mapping
void Renderer::tone_mapping(Color& clr) {
  clr.r = clr.r / (clr.r + 1);
  clr.g = clr.g / (clr.g + 1);
  clr.b = clr.b / (clr.b + 1);
}
