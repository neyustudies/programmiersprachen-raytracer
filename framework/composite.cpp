#include "composite.hpp"

Composite::Composite() :
  Shape{"Unnamed Shape", nullptr} {}

Composite::Composite(std::string const& name) :
  Shape{name, nullptr} {}

Composite::~Composite() {}

void Composite::add(std::shared_ptr<Shape> const& shape) {
  shapes_.push_back(shape);
}

float Composite::area() const {
  return 0;
}

float Composite::volume() const {
  return 0;
}

/* rotate all shapes in composite */
void Composite::rotate(float& angle, glm::vec3 const& axis) {
  for(auto const shape : shapes_) {
    shape->rotate(angle, axis);
  }
}

/* scale all shapes in composite */
void Composite::scale(glm::vec3 const& point) {
  for(auto const shape : shapes_) {
    shape->scale(point);
  }
}

/* translate all shapes in composite */
void Composite::translate(glm::vec3 const& point) {
  for(auto const shape : shapes_) {
    shape->translate(point);
  }
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