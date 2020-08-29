#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "ray.hpp"
#include <glm/vec3.hpp>
#include <string>

class Camera {

  public:
    Camera();
    Camera(std::string const& name, float fov_x);
    Camera(std::string const& name,
           float fov_x,
           glm::vec3 const& eye,
           glm::vec3 const& dir,
           glm::vec3 const& up);

    /**
     * Get a ray onto the image plane at given pixel coordinates.
     */
    Ray ray(unsigned x, unsigned y, unsigned res_x, unsigned res_y) const;

    /* getter setter - to be removed if not needed */
    std::string name() const;
    void name(std::string const& name);
    float fov_x() const;
    void fov_x(float fov_x);
    glm::vec3 eye() const;
    void eye(glm::vec3 const& eye);
    glm::vec3 dir() const;
    void dir(glm::vec3 const& dir);
    glm::vec3 up() const;
    void up(glm::vec3 const& up);

  private:
    std::string name_;
    float fov_x_;
    /** Position of the camera. (default is origin) */
    glm::vec3 eye_;
    /** Direction the camera is facing. (default towards negative z) */
    glm::vec3 dir_;
    /** Up direction (used for rotation, default towards positive y) */
    glm::vec3 up_;

};

#endif // CAMERA_HPP
