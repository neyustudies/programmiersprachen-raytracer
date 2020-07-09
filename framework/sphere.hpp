#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "shape.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape {

  public:
    Sphere();
    float area() const;
    float volume() const;
    float radius() const;
    glm::vec3 center() const;



};

#endif // SPHERE_HPP