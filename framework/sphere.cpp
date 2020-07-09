#include "sphere.hpp"

Sphere::Sphere() :
  center_ {glm::vec3{}},
  radius_ {1.0f} {}

Sphere::Sphere(glm::vec3 const& ctr, float r) :
  center_ {ctr},
  radius_ {r} {}
