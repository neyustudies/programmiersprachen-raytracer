#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include "shape.hpp"
#include <memory>
#include <string>
#include <iostream>
#include <sstream>

class Animation {

  public:
    /* set axis for animation */
    void axis(std::string const& axis);
    /* return transformation for next frame */
    std::string transformation();
    unsigned int count_ = 0;
    unsigned int speed_ = 0;
    

  protected:
    std::string scaling();
    std::string rotation();
    std::string translation();

  private:
    Axis axis_;
    Transformation type_;
    std::shared_ptr<Shape> shape_;
    
};

enum Transformation {ROTATE, SCALE, TRANSLATE};
enum Axis {X, Y, Z, XY, XZ, YZ, XYZ};

#endif //ANIMATION_HPP