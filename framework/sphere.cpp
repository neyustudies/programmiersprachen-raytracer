#include "sphere.hpp"
#include <cmath>

Sphere::Sphere() :
  Shape   {"Unnamed Sphere", {}},
  center_ {glm::vec3{}},
  radius_ {1.0f} {}

Sphere::Sphere(glm::vec3 const& ctr, float r) :
  Shape   {"Unnamed Sphere", {}},
  center_ {ctr},
  radius_ {r} {}

Sphere::Sphere(glm::vec3 const& ctr, float r, std::string const& name) :
  Shape   {name, {}},
  center_ {ctr},
  radius_ {r} {}


Sphere::Sphere(glm::vec3 const& ctr, float r, std::string const& name, std::shared_ptr<Material> const& material) :
  Shape   {name, material},
  center_ {ctr},
  radius_ {r} {}

Sphere::~Sphere() {}

glm::vec3 Sphere::center() const {
  return center_;
}

float Sphere::radius() const {
  return radius_;
}

float Sphere::area() const {
  return 4.0f * M_PI * std::pow(radius_, 2.0f);
}

float Sphere::volume() const {
  return 4.0f / 3.0f * M_PI * std::pow(radius_, 3.0f);
}

HitPoint Sphere::intersect(Ray const& ray) const {
  auto ray_direction = glm::normalize(ray.direction);
  float distance = NAN;
  bool did_intersect = glm::intersectRaySphere(
      ray.origin,            // rayStarting
      ray_direction,         // rayNormalizedDirection
      center_,               // sphereCenter
      std::pow(radius_, 2),  // sphereRadiusSquered
      distance               // intersectionDistance
      );
  return HitPoint{
      did_intersect,
      distance,
      name_,
      material_->ka,
      ray.origin + (distance * ray_direction),  // intersection_point
      ray_direction};
}

std::ostream& Sphere::print(std::ostream& os) const {
  Shape::print(os);
  return os << "Center:  (" << center_.x << "," << center_.y << "," << center_.z 
            << ")\nRadius:  " << radius_ << "\nArea:    " << area() 
            << "\nVolume:  " << volume() << "\n";
}