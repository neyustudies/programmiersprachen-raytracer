#include "box.hpp"
#include <cmath>

Box::Box() :
  Shape {"Unnamed Box", {}},
  min_  {glm::vec3{}},
  max_  {glm::vec3{}} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
  Shape {"Unnamed Box", {}},
  min_  {min},
  max_  {max} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string const& name) :
  Shape {name, {}},
  min_  {min},
  max_  {max} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string const& name, Color const& clr) :
  Shape {name,clr},
  min_  {min},
  max_  {max} {}

Box::~Box() {}

glm::vec3 Box::min() const {
  return min_;
}

void Box::min(glm::vec3 const& min) {
  min_ = min;
}

glm::vec3 Box::max() const {
  return max_;
}

void Box::max(glm::vec3 const& max) {
  max_ = max;
}

float Box::area() const {
  return 2.0f * std::abs(max_.x - min_.x) +
         2.0f * std::abs(max_.y - min_.y) +
         2.0f * std::abs(max_.z - min_.z);
}

float Box::volume() const {
  return std::abs(max_.x - min_.x) *
         std::abs(max_.y - min_.y) *
         std::abs(max_.z - min_.z);
}

std::ostream& Box::print(std::ostream& os) const {
  Shape::print(os);
  return os << "Minimum: (" << min_.x << "," << min_.y << "," << min_.z 
            << ")\nMaximum: (" << max_.x << "," << max_.y << "," << max_.z 
            << ")\nArea:    " << area() << "\nVolume:  " << volume() << "\n";
}