#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "shape.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape {

  public:
    Sphere();
    Sphere(glm::vec3 const& ctr, float r);
    Sphere(glm::vec3 const& ctr, float r, std::string const& name);
    Sphere(glm::vec3 const& ctr, float r, std::string const& name, Color const& clr);
    glm::vec3 center() const;
    void center(glm::vec3 const& ctr);
    float radius() const;
    void radius(float r);
    float area() const;
    float volume() const;

  private:
    glm::vec3 center_;
    float radius_;


};

#endif // SPHERE_HPP