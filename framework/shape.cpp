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

glm::vec3 transformOrigin(glm::mat4 const& mat, glm::vec3 const& point) {
  return glm::vec3{glm::vec4{mat * glm::vec4{point, 1}}};
}

glm::vec3 transformDirection(glm::mat4 const& mat, glm::vec3 const& point) {
  return glm::vec3{glm::vec4{mat * glm::vec4{point, 0}}};
}

Ray transformRay(glm::mat4 const& mat, Ray const& ray) {
  glm::vec3 new_origin = transformOrigin(mat, ray.origin);
  glm::vec3 new_direction = transformDirection(mat, ray.direction);
  return Ray{new_origin, new_direction};
}

std::ostream& Shape::print(std::ostream& os) const {
  return os << "\nShape\n-----\n" << "Name:    " << name_ << "\n";
}

std::ostream& operator <<(std::ostream& os, Shape const& s) {
  return s.print(os);
}