#include "composite.hpp"

Composite::Composite() :
  Shape{"Unnamed Shape", nullptr} {}

Composite::Composite(std::string const& name) :
  Shape{name, nullptr} {}

Composite::~Composite() {}

void Composite::add(std::shared_ptr<Shape> const& shape) {
  shapes_.push_back(shape);
}

HitPoint Composite::intersect(Ray const& ray) const {
  HitPoint result;
  Ray tray = transformRay(Shape::world_transform_inv_, ray);
  for(auto child : shapes_) {
    HitPoint hit = child->intersect(tray);
    if(hit.t < result.t) {
      result = hit;
    }
  }
  return HitPoint{
    // result.did_intersect
    // TODO
  };
}