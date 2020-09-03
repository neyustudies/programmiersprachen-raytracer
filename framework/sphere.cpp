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
  Ray tray = transformRay(world_transform_inv_, ray);
  float distance = NAN;
  HitPoint hit;
  hit.did_intersect = glm::intersectRaySphere(
    tray.origin,           // rayStarting
    tray.direction,        // rayNormalizedDirection
    center_,               // sphereCenter
    std::pow(radius_, 2),  // sphereRadiusSquared
    distance               // intersectionDistance
    );
  
  if(hit.did_intersect) {
    hit.point     = tray.origin + (distance * tray.direction);
    hit.t         = glm::distance(tray.origin, hit.point);
    hit.name      = name_;
    hit.clr       = material_->ka;
    hit.direction = tray.direction;
    hit.normal    = glm::normalize(hit.point - center_);
  }

  transformBack(hit, world_transform_, glm::transpose(world_transform_inv_));

  return hit;
}

std::ostream& Sphere::print(std::ostream& os) const {
  Shape::print(os);
  return os << "Center:  (" << center_.x << "," << center_.y << "," << center_.z 
            << ")\nRadius:  " << radius_ << "\nArea:    " << area() 
            << "\nVolume:  " << volume() << "\n";
}
