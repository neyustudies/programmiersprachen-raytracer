#ifndef UTIL_HPP
#define UTIL_HPP

#include <ostream>
#include <glm/vec3.hpp>

#define EPSILON 0.0001f

template <typename T>
inline bool in_between_epsilon(T min, T f, T max) {
  return (min - EPSILON) <= (f + EPSILON) && (f - EPSILON) <= (max + EPSILON);
}

inline std::ostream& operator<<(std::ostream& os, glm::vec3 vec) {
  return os << vec.x << ", " << vec.y << ", " << vec.z;
}

#endif  // UTIL_HPP
