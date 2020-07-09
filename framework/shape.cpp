#include "shape.hpp"

Shape::Shape() :
  name_ {"default"} {}

Shape::Shape(std::string const& name) :
  name_ {name} {}

Shape::Shape(std::string const& name, Color const& clr) :
  name_ {name},
  color_{clr} {}

std::string Shape::name() const {
  return name_;
}

void Shape::name(std::string const& name) {
  name_ = name;
}

Color Shape::color() const {
  return color_;
}