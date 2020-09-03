#include "shape.hpp"

Shape::Shape() :
  name_     {"Unnamed Shape"},
  material_ {nullptr} {}

Shape::Shape(std::string const& name) :
  name_ {name} {}

Shape::Shape(std::string const& name, std::shared_ptr<Material> const& material) :
  name_     {name},
  material_ {material} {}

Shape::~Shape() {}

std::string Shape::name() const {
  return name_;
}

std::shared_ptr<Material> const& Shape::material() const {
  return material_;
}

/* positive angle corresponds to a counterclockwise rotation
   when looking from the positive axis towards the origin */
void Shape::rotate(float& angle, glm::vec3 const& axis) {
  world_transform_ = glm::rotate(world_transform_, glm::radians(angle), axis);
  world_transform_inv_ = glm::inverse(world_transform_);
}

/* scaling a point relative to the origin */
void Shape::scale(glm::vec3 const& point) {
  world_transform_ = glm::scale(world_transform_, point);
  world_transform_inv_ = glm::inverse(world_transform_);
}

/* moving a point by a vector */
void Shape::translate(glm::vec3 const& point) {
  world_transform_ = glm::translate(world_transform_, point);
  world_transform_inv_ = glm::inverse(world_transform_);
}

std::ostream& Shape::print(std::ostream& os) const {
  return os << "\nShape\n-----\n" << "Name:    " << name_ << "\n";
}

std::ostream& operator <<(std::ostream& os, Shape const& s) {
  return s.print(os);
}

/* transform a ray to local space */
Ray transformRay(glm::mat4 const& mat, Ray const& ray) {
  glm::vec4 origin{ray.origin, 1};
  glm::vec4 direction{ray.direction, 0};
  return Ray{glm::vec3{mat * origin}, glm::vec3{mat * direction}};
}

/* transform intersection point and normal back to world space */
void transformBack(HitPoint& hit, glm::mat4 const& mat, glm::mat4 const& mat_inv_trans) {
  hit.point  = glm::vec3{mat * glm::vec4{hit.point, 1.0f}};
  hit.normal = glm::normalize(glm::vec3{mat_inv_trans * glm::vec4{hit.normal, 0.0f}});
}
