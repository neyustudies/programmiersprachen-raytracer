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

Ray transformRay(glm::mat4 const& mat, Ray const& ray) {
  glm::vec4 origin{ray.origin, 1};
  glm::vec4 direction{ray.direction, 0};
  return Ray{glm::vec3{mat * origin}, glm::vec3{mat * direction}};
}

std::ostream& Shape::print(std::ostream& os) const {
  return os << "\nShape\n-----\n" << "Name:    " << name_ << "\n";
}

std::ostream& operator <<(std::ostream& os, Shape const& s) {
  return s.print(os);
}