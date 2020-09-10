#include "triangle.hpp"
#include <cmath>

Triangle::Triangle() :
  Shape {"Unnamed Triangle", nullptr},
  v0_   {0.0f, 0.0f, 0.0f},
  v1_   {0.0f, 0.5f, 0.0f},
  v2_   {0.0f, 0.0f, 0.5f} {}

Triangle::Triangle(glm::vec3 const& v0, glm::vec3 const& v1, glm::vec3 const& v2) :
  Shape {"Unnamed Triangle", nullptr},
  v0_   {v0},
  v1_   {v1},
  v2_   {v2} {}

Triangle::Triangle(glm::vec3 const& v0, glm::vec3 const& v1, glm::vec3 const& v2, 
                   std::string const& name, std::shared_ptr<Material> const& material) :
  Shape {name, material},
  v0_   {v0},
  v1_   {v1},
  v2_   {v2} {}

Triangle::~Triangle() {}

glm::vec3 Triangle::v0() const {
  return v0_;
}

glm::vec3 Triangle::v1() const {
  return v1_;
}

glm::vec3 Triangle::v2() const {
  return v2_;
}

float Triangle::area() const {
  return glm::length(glm::cross(v1_ - v0_, v2_ - v0_) / 2.f);
}

float Triangle::volume() const {
  return 0;
}

HitPoint Triangle::intersect(Ray const& ray) const{
  HitPoint hit;
  Ray tray = transformRay(world_transform_inv_, ray);
  tray.direction = glm::normalize(tray.direction);
  glm::vec3 intersect(0);
  hit.did_intersect = glm::intersectRayTriangle(tray.origin, 
                                                tray.direction, 
                                                v0_, v1_, v2_, 
                                                intersect);
  if(hit.did_intersect) {
    hit.t         = glm::length(tray.origin - intersect);
    hit.point     = intersect;
    hit.direction = tray.direction;
    hit.name      = name_;
    hit.clr       = material_->ka;
    hit.normal    = glm::cross(v1_ - v0_, v2_ - v0_);
  }

  transformBack(hit, world_transform_, glm::transpose(world_transform_inv_));
  return hit;
}
