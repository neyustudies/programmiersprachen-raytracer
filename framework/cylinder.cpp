#include "cylinder.hpp"

Cylinder::Cylinder() :
  Shape     {"Unnamed Cylinder", nullptr},
  point_1_  {glm::vec3{}},
  point_2_  {glm::vec3{}},
  radius_   {0.0f} {}

Cylinder::Cylinder(glm::vec3 const& point_1, glm::vec3 const& point_2, float r) :
  Shape     {"Unnamed Cylinder", nullptr},
  point_1_  {point_1},
  point_2_  {point_2},
  radius_   {r} {}

Cylinder::Cylinder(glm::vec3 const& point_1, glm::vec3 const& point_2, float r, std::string const& name, std::shared_ptr<Material> const& material) :
  Shape     {name, material},
  point_1_  {point_1},
  point_2_  {point_2},
  radius_   {r} {}

Cylinder::~Cylinder() {}

float Cylinder::height() const {
  return glm::distance(point_1_, point_2_);
}

float Cylinder::volume() const {
  return powf(radius_, 2.0f) * M_PI * height();
}

float Cylinder::area() const {
  return powf(radius_, 2.0f) * M_PI * 2 + radius_ * M_PI * 2 * height();
}

HitPoint Cylinder::intersect(Ray const& ray) const {
  // TODO
  return HitPoint{};
}
