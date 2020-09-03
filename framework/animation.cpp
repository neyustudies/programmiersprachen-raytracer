#include "animation.hpp"

std::string Animation::transformation() {
  ++count_;
  std::string transform = "define transform";
  if(shape_ != nullptr) {
    transform += shape_->name() + " ";
    if(type_ == ROTATE) {
      transform += "rotate " + rotation();
    } else if(type_ == SCALE) {
      transform += "scale " + scaling();
    } else if(type_ == TRANSLATE) {
      transform += "translate " + translation();
    } else {std::cerr << "transformation type is not valid";}
  }
}


void Animation::axis(std::string const& axis) {
  if(axis == "X" || axis == "x") {
    axis_ = X;
  } else if(axis == "Y" || axis == "y") {
    axis_ = Y;
  } else if(axis == "Z" || axis == "z") {
    axis_ = Z;
  } else if(axis == "XY" || axis == "xy") {
    axis_ = XY;
  } else if(axis == "XZ" || axis == "xz") {
    axis_ = XZ;
  } else if(axis == "XYZ" || axis == "xyz") {
    axis_ = XYZ;
  } else {std::cerr << "axis type is not valid";}
}


std::string Animation::rotation() {
  float angle = speed_ * count_;
  std::string rotation = std::to_string(angle) + " ";
  if(axis_ == X) {
    rotation += "1 0 0";
  }
  else if(axis_ == Y) {
    rotation += "0 1 0";
  }
  else if(axis_ == Z) {
    rotation += "0 0 1";
  }
  else if(axis_ == XY) {
    rotation += "1 1 0";
  }
  else if(axis_ == XZ) {
    rotation += "1 0 1";
  }
  else if(axis_ == YZ) {
    rotation += "0 1 1";
  }
  else if(axis_ == XYZ) {
    rotation += "1 1 1";
  }
  return rotation;
};


std::string Animation::scaling() {/* todo */};
std::string Animation::translation() {/* todo */};