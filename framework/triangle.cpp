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
                   std::string const& name, std::shared_ptr<Material> const material) :
  Shape {name, material},
  v0_   {v0},
  v1_   {v1},
  v2_   {v2} {}

Triangle::~Triangle() {}

float Triangle::area() const {
  return glm::length(glm::cross(v1_ - v0_, v2_ - v0_) / 2.f);
}

HitPoint Triangle::intersect(Ray const& ray) const{
  Ray tray = transformRay(world_transform_inv_, ray);
  float distance = NAN; 
  tray.direction = glm::normalize(ray.direction);
  glm::vec3 intersect(0);
  glm::vec3 intersection_point;
  glm::vec3 normal   = glm::cross(v1_ - v0_, v2_ - v0_);
  bool did_intersect = glm::intersectRayTriangle(tray.origin, 
                                                 tray.direction, 
                                                 v0_, v1_, v2_, 
                                                 intersect);
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