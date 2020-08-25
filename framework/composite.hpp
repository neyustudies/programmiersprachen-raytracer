#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP
#include "shape.hpp"
#include <vector>

class Composite : public Shape {

  public:
    Composite();
    Composite(std::string const& name);
    ~Composite();
    float area() const override;
    float volume() const override;
    void add(std::shared_ptr<Shape> const& shape);
    HitPoint intersect(Ray const& ray) const override;
    //void add(std::shared_ptr<Composite> const& composite);

  private:
    std::vector<std::shared_ptr<Shape>> shapes_;
    //std::vector<std::shared_ptr<Composite>> composites_;

};

#endif // COMPOSITE_HPP