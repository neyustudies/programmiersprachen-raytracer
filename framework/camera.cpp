#include "camera.hpp"
#include <cmath>
#include <glm/glm.hpp>

Camera::Camera() :
  name_  {"Camera"},
  fov_x_ {90.0f},
  eye_   {glm::vec3{}},
  dir_   {glm::vec3{0.0f, 0.0f, -1.0f}},
  up_    {glm::vec3{0.0f, 1.0f, 0.0f}} {}

Camera::Camera(std::string const& name, float fov_x) :
  name_  {name},
  fov_x_ {fov_x},
  eye_   {glm::vec3{}},
  dir_   {glm::vec3{0.0f, 0.0f, -1.0f}},
  up_    {glm::vec3{0.0f, 1.0f, 0.0f}} {}

Camera::Camera(std::string const& name, float fov_x, glm::vec3 const& eye, glm::vec3 const& dir, glm::vec3 const& up) :
  name_  {name},
  fov_x_ {fov_x},
  eye_   {eye},
  dir_   {dir},
  up_    {up} {}

Ray Camera::ray(float x, float y, unsigned res_x, unsigned res_y) const {
  float d = ((float)res_x/2.f) / tan(fov_x_ * (M_PI / 180.f));
  glm::vec3 s{x - ((float)res_x / 2), y - ((float)res_y / 2), 0};
  return {eye_, s + (d * glm::normalize(dir_))};
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
