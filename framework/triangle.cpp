#include "triangle.hpp"
#include <cmath>
#include <glm/gtx/intersect.hpp>

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
                   std::string const& name, std::shared_ptr<Material> const material) :
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
  Ray tray = transformRay(world_transform_inv_, ray);
  float distance = NAN; 
  tray.direction = glm::normalize(ray.direction);
  glm::vec2 result(0);
  glm::vec3 intersection_point;
  glm::vec3 normal   = glm::cross(v1_ - v0_, v2_ - v0_);
  bool did_intersect = glm::intersectRayTriangle(tray.origin, 
                                                 tray.direction, 
                                                 v0_, v1_, v2_, 
                                                 result, distance);
  if(did_intersect) {
     // 3d intersection point of ray and triangle
    glm::vec3 dir_vec = tray.direction - tray.origin;
    glm::vec3 unit_vec(dir_vec / glm::length(dir_vec));
    intersection_point = unit_vec * distance;
  }
  return HitPoint{
    did_intersect,
    distance,
    name_,
    material_->ka,
    intersection_point,
    tray.direction,
    normal
  };
}
