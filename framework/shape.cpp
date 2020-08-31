#include "shape.hpp"

Shape::Shape() :
  name_ {"Unnamed Shape"},
  material_ {nullptr} {}

Shape::Shape(std::string const& name) :
  name_ {name} {}

Shape::Shape(std::string const& name, std::shared_ptr<Material> const& material) :
  name_ {name},
  material_ {material} {}

Shape::~Shape() {}

std::string Shape::name() const {
  return name_;
}

std::shared_ptr<Material> const& Shape::material() const {
  return material_;
}

void Shape::rotate(float& angle, float& rx, float& ry, float& rz) {
  world_transform_ *= glm::rotate(angle, glm::vec3{rx, ry, rz});
}

void Shape::scale(float& sx, float& sy, float& sz) {
  world_transform_ *= glm::scale(glm::vec3{sx, sy, sz});
}

void Shape::translate(float& tx, float& ty, float& tz) {
  world_transform_ *= glm::translate(glm::vec3{tx, ty, tz});
}

std::ostream& Shape::print(std::ostream& os) const {
  return os << "\nShape\n-----\n" << "Name:    " << name_ << "\n";
}

std::ostream& operator <<(std::ostream& os, Shape const& s) {
  return s.print(os);
}

Ray transformRay(glm::mat4 const& mat, Ray const& ray) {
  glm::vec4 origin{ray.origin, 1};
  glm::vec4 direction{ray.direction, 0};
  return Ray{glm::vec3{mat * origin}, glm::vec3{mat * direction}};
}

void transformBack(HitPoint hit, glm::mat4 const& mat, glm::mat4 const& mat_inv_trans) {
  hit.point = glm::vec3{mat * glm::vec4{hit.point, 1.0f}};
  hit.normal = glm::normalize(glm::vec3{(mat_inv_trans * glm::vec4{hit.normal, 0.0f})});
}
