#include "triangle.hpp"
#include <cmath>

Triangle::Triangle() :
  Shape     {"Unnamed Triangle", nullptr},
  point_1_  {0.0f, 0.0f, 0.0f},
  point_2_  {0.0f, 0.5f, 0.0f},
  point_3_  {0.0f, 0.0f, 0.5f} {}

Triangle::Triangle(glm::vec3 const& point_1, glm::vec3 const& point_2, glm::vec3 const& point_3) :
  Shape     {"Unnamed Triangle", nullptr},
  point_1_  {point_1},
  point_2_  {point_2},
  point_3_  {point_3} {}

Triangle::Triangle(glm::vec3 const& point_1, glm::vec3 const& point_2, glm::vec3 const& point_3, 
                   std::string const& name, std::shared_ptr<Material> const material) :
  Shape     {name, material},
  point_1_  {point_1},
  point_2_  {point_2},
  point_3_  {point_3} {}

Triangle::~Triangle() {}

float Triangle::area() const {
  return fabsf((point_1_.x * (point_2_.y - point_3_.y) +
                point_2_.x * (point_3_.y - point_1_.y) +
                point_3_.x * (point_1_.y - point_2_.y)) / 2.0f);
}

float Triangle::volume() const {}

HitPoint Triangle::intersect(Ray const& ray) const{
  return HitPoint{};
}