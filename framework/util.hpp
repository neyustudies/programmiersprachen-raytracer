#ifndef UTIL_HPP
#define UTIL_HPP

#define EPSILON 0.000001

template <typename T>
inline bool in_between_epsilon(T min, T f, T max) {
  return (min - EPSILON) <= (f + EPSILON) && (f - EPSILON) <= (max + EPSILON);
}

#endif  // UTIL_HPP
