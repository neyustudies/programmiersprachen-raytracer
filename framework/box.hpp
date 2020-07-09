#ifndef BOX_HPP
#define BOX_HPP
#include "shape.hpp"
#include <glm/vec3.hpp>

class Box : public Shape {

  public:
    Box();
    float area() const;
    float volume() const;
    glm::vec3 min() const;
    glm::vec3 max() const;

  private:
    glm::vec3 min_;
    glm::vec3 max_;

};

#endif // BOX_HPP