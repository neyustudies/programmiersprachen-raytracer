#include "camera.hpp"

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

std::string Camera::name() const {
  return name_;
}

void Camera::name(std::string const& name) {
  name_ = name;
}

float Camera::fov_x() const {
  return fov_x_;
}

void Camera::fov_x(float fov_x) {
  fov_x_ = fov_x;
}

glm::vec3 Camera::eye() const {
  return eye_;
}

void Camera::eye(glm::vec3 const& eye) {
  eye_ = eye;
}

glm::vec3 Camera::dir() const {
  return dir_;
}

void Camera::dir(glm::vec3 const& dir) {
  dir_ = dir;
}

glm::vec3 Camera::up() const {
  return up_;
}

void Camera::up(glm::vec3 const& up) {
  up_ = up;
}

/* to be added: method to construct a camera ray */