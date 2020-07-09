#include "box.hpp"

Box::Box() :
  min_ {glm::vec3{}},
  max_ {glm::vec3{}} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
  min_ {min},
  max_ {max} {}