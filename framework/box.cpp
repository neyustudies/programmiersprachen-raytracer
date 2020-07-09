#include "box.hpp"

Box::Box() :
  min_ {glm::vec3{}},
  max_ {glm::vec3{}} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
  min_ {min},
  max_ {max} {}

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