#include "camera.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/mat3x3.hpp>

Camera::Camera() :
  Camera {"Camera", 90.f, {}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}} {}

Camera::Camera(std::string const& name, float fov_x) :
  Camera {name, fov_x, {}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}} {}

Camera::Camera(std::string const& name, float fov_x, glm::vec3 const& eye, glm::vec3 const& dir, glm::vec3 const& up) :
  name_  {name},
  fov_x_ {fov_x},
  eye_   {eye},
  dir_   {dir},
  up_    {up} {

    auto u = glm::cross(dir_, up_);
    auto v = glm::cross(u, dir_);
    transform_ = {
      glm::vec4(glm::normalize(u), 0),
      glm::vec4(glm::normalize(v), 0),
      glm::vec4(-glm::normalize(dir_), 0),
      glm::vec4(eye_, 1)
    };
  }

Ray Camera::ray(float x, float y, unsigned res_x, unsigned res_y) const {
  float d = ((float)res_x/2.f) / tan(fov_x_ * (M_PI / 180.f));
  glm::vec3 s{x - ((float)res_x / 2), y - ((float)res_y / 2), -d};
  auto direction = glm::vec3(transform_ * glm::vec4(s, 1.f));
  return {eye_, glm::normalize(direction)};
}

std::string Camera::name() const {
  return name_;
}

float Camera::fov_x() const {
  return fov_x_;
}

glm::vec3 Camera::eye() const {
  return eye_;
}

glm::vec3 Camera::dir() const {
  return dir_;
}

glm::vec3 Camera::up() const {
  return up_;
}
