#include "shape.hpp"

Shape::Shape() :
  name_ {"default"} {}

Shape::Shape(std::string const& name) :
  name_ {name} {}

Shape::Shape(std::string const& name, Color const& clr) :
  name_ {name},
  color_{clr} {}

Shape::~Shape() {}

std::string Shape::name() const {
  return name_;
}

Color Shape::color() const {
  return color_;
}

std::ostream& Shape::print(std::ostream& os) const {
  return os << "\nShape\n-----\n" << "Name:    " << name_ << "\nColor:   " << color_;
}

std::ostream& operator <<(std::ostream& os, Shape const& s) {
  return s.print(os);
}