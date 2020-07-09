#include "sphere.hpp"
#include <cmath>

Sphere::Sphere() :
  Shape   {"Unnamed Sphere", {}},
  center_ {glm::vec3{}},
  radius_ {0.0f} {}

Sphere::Sphere(glm::vec3 const& ctr, float r) :
  Shape   {"Unnamed Sphere", {}},
  center_ {ctr},
  radius_ {r} {}

Sphere::Sphere(glm::vec3 const& ctr, float r, std::string const& name) :
  Shape   {name, {}},
  center_ {ctr},
  radius_ {r} {}

Sphere::Sphere(glm::vec3 const& ctr, float r, std::string const& name, Color const& clr) :
  Shape   {name, clr},
  center_ {ctr},
  radius_ {r} {}

glm::vec3 Sphere::center() const {
  return center_;
}

void Sphere::center(glm::vec3 const& ctr) {
  center_ = ctr;
}

float Sphere::radius() const {
  return radius_;
}

void Sphere::radius(float r) {
  radius_ = r;
}

float Sphere::area() const {
  return 4.0f * M_PI * std::pow(radius_, 2.0f);
}

float Sphere::volume() const {
  return 4.0f / 3.0f * M_PI * std::pow(radius_, 3.0f);
}