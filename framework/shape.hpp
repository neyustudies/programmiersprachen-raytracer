#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "material.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/vector_angle.hpp>
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
    
    virtual void rotate(float& angle, glm::vec3 const& axis);
    virtual void scale(glm::vec3 const& point);
    virtual void translate(glm::vec3 const& point);   
    virtual HitPoint intersect(Ray const& ray) const = 0;
    virtual std::ostream& print(std::ostream& os) const;
    virtual float area() const = 0;
    virtual float volume() const = 0;

  protected:
    std::string name_;
    std::shared_ptr<Material> material_;
    glm::mat4 world_transform_;
    glm::mat4 world_transform_inv_;

};

Ray transformRay(glm::mat4 const& mat, Ray const& ray);
void transformBack(HitPoint& hit, glm::mat4 const& mat, glm::mat4 const& mat_inv_trans);

#endif // SHAPE_HPP