#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP
#include "shape.hpp"
#include <vector>

class Composite : public Shape {

  public:
    Composite();
    Composite(std::string const& name);
    ~Composite();
    
    void add(std::shared_ptr<Shape> const& shape);

    float area() const override;
    float volume() const override;
    void rotate(float& angle, glm::vec3 const& axis) override;
    void scale(glm::vec3 const& point) override;
    void translate(glm::vec3 const& point) override;
    void find_intersected_shapes(HitPoint& first_hit, Ray const& ray) const override;
    HitPoint intersect(Ray const& ray) const override;

  private:
    std::vector<std::shared_ptr<Shape>> shapes_;

};

#endif // COMPOSITE_HPP