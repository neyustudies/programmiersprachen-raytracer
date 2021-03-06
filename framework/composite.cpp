#include "composite.hpp"

Composite::Composite() :
  Shape{"Unnamed Shape", nullptr} {}

Composite::Composite(std::string const& name) :
  Shape{name, nullptr} {}

Composite::~Composite() {
  shapes_.clear();
}

std::vector<std::shared_ptr<Shape>> Composite::shapes() const {
  return shapes_;
}

void Composite::add(std::shared_ptr<Shape> const& shape) {
  shapes_.push_back(shape);
}

float Composite::area() const {
  float area = 0.0f;
  for(auto shape : shapes_) {
    area += shape->area();
  } return area;
}

float Composite::volume() const {
  float volume = 0.0f;
  for(auto shape : shapes_) {
    volume += shape->volume();
  } return volume;
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
  HitPoint first_hit;
  Ray tray = transformRay(world_transform_inv_, ray);
  for(auto shape : shapes_) {
    HitPoint hit = shape->intersect(tray);
    if(hit.t < first_hit.t) {
      first_hit = hit;
    }
  }
  transformBack(first_hit, world_transform_, glm::transpose(world_transform_inv_));
  return first_hit;
}