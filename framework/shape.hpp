#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "color.hpp"
#include "material.hpp"
#include "hitpoint.hpp"
#include <glm/gtx/intersect.hpp>
#include "ray.hpp"
#include <string>
#include <memory>

class Shape {

  public:
    Shape();
    Shape(std::string const& name);
    Shape(std::string const& name, std::shared_ptr<Material> const& material);
    virtual ~Shape();
    std::shared_ptr<Material> const& material() const;
    std::string name() const;
    Color color() const;
    virtual HitPoint intersect(Ray const& ray, float t) const = 0;
    virtual std::ostream& print(std::ostream& os) const;
    virtual float area() const = 0;
    virtual float volume() const = 0;

  protected:
    std::string name_;
    Color color_;
    std::shared_ptr<Material> material_;

};

#endif // SHAPE_HPP