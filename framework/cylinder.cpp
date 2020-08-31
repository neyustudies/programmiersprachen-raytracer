#include "cylinder.hpp"

Cylinder::Cylinder() :
  Shape   {"Unnamed Cylinder", nullptr},
  v0_     {glm::vec3{}},
  radius_ {0.0f},
  height_ {0.0f} {}

Cylinder::Cylinder(glm::vec3 const& v0, float r, float h) :
  Shape   {"Unnamed Cylinder", nullptr},
  v0_     {v0},
  radius_ {r},
  height_ {h} {}

Cylinder::Cylinder(glm::vec3 const& v0, float r, float h, std::string const& name, 
                   std::shared_ptr<Material> const& material) :
  Shape   {name, material},
  v0_     {v0},
  radius_ {r},
  height_ {h} {}

Cylinder::~Cylinder() {}

glm::vec3 Cylinder::v0() const {
  return v0_;
}

float Cylinder::height() const {
  return height_;
}

float Cylinder::radius() const {
  return radius_;
}

float Cylinder::volume() const {
  return powf(radius_, 2.0f) * M_PI * height_;
}

float Cylinder::area() const {
  return powf(radius_, 2.0f) * M_PI * 2 + radius_ * M_PI * 2 * height_;
}

HitPoint Cylinder::intersect(Ray const& ray) const {
  HitPoint hit;
  Ray tray = transformRay(world_transform_inv_, ray);
  auto tray_direction = glm::normalize(tray.direction);
  float distance = NAN;
  //...
  transformBack(hit, world_transform_, glm::transpose(world_transform_inv_));
  return hit;
}
