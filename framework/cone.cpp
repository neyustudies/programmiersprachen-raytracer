#include "cone.hpp"

Cone::Cone() :
  Shape   {"Unnamed Cone", nullptr},
  base_   {glm::vec3{}},
  radius_ {0.0f},
  height_ {0.0f} {}

Cone::Cone(glm::vec3 const& base, float r, float h) :
  Shape   {"Unnamed Cone", nullptr},
  base_   {base},
  radius_ {r},
  height_ {h} {}

Cone::Cone(glm::vec3 const& base, float r, float h,
           std::string const& name, std::shared_ptr<Material> const& material) :
  Shape   {name, material},
  base_   {base},
  radius_ {r},
  height_ {h} {}

Cone::~Cone() {}

glm::vec3 Cone::base() const {
  return base_;
}

float Cone::radius() const {
  return radius_;
}

float Cone::height() const {
  return height_;
}

float Cone::area() const {
  float slant_height = powf(radius_, 2.0f) + sqrtf(powf(height_, 2.0f));
  return M_PI * (1.0f / 3.0f) * (slant_height + radius_);
}

float Cone::volume() const {
  return M_PI * (1.0f / 3.0f) * powf(radius_, 2.0f) * height_;
}

HitPoint Cone::intersect(Ray const& ray) const {
  Ray tray = transformRay(world_transform_inv_, ray);
  HitPoint hit;
  glm::vec3 hitpoint;
  glm::vec3 normal;
  glm::vec3 hit1, hit2;
  float distance = NAN;

	float a = powf(tray.direction.x, 2.f) +
            powf(tray.direction.y, 2.f) - 
            powf(tray.direction.z, 2.f);

	float b = 2.f * tray.origin.x * tray.direction.x + 
            2.f * tray.origin.y * tray.direction.y - 
            2.f * tray.origin.z * tray.direction.z;

	float c = powf(tray.origin.x, 2.f) + 
            powf(tray.origin.y, 2.f) - 
            powf(tray.origin.z, 2.f);

	float t1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	float t2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);

  
	if(pow(b, 2) - 4 * a * c > 0) {
		bool c1 = false;
		bool c2 = false;
		if(t1 > 0) {
			glm::vec3 hit1 = tray.origin + t1 * tray.direction;
			if(hit1.z <= 0.0f && hit1.z >= -1.0f) {
				c1 = true;
			}
		}
		if (t2 > 0) {
			glm::vec3 hit2 = tray.origin + t2 * tray.direction;
			if (hit2.z <= 0.0f && hit2.z >= -1.0f) {
				c2 = true;
			}
		}

    glm::vec3 tmp;
    bool normalize = false;
    bool did_hit = false;
    if(normalize) {
      tmp    = glm::normalize(glm::vec3{hitpoint.x, hitpoint.y, 0});
			normal = glm::normalize(glm::vec3{tmp.x, tmp.y, 1.0f});
    }
		
		if(c1 && c2) {
			if(t2 < t1) {
				hitpoint  = hit2;
				distance  = t2;
				normalize = true;
				did_hit   = true;
			} else {
				hitpoint  = hit1;
				distance  = t1;
				normalize = true;
				did_hit   = true;
			}
		} else if(c1) {
			hitpoint  = hit1;
			distance  = t1;
			normalize = true;
			did_hit   = true;
		} else if(c2) {
			hitpoint  = hit2;
			distance  = t2;
			normalize = true;
			did_hit   = true;
		} else {
      did_hit = false;
    }

		Plane p{glm::vec3{0,0,-1}, glm::vec3{0,0,-1}};
		float t_base = (glm::dot(p.normal, p.origin) - 
                    glm::dot(tray.origin, p.normal)) / 
                   (glm::dot(tray.direction, p.normal));
    glm::vec3 base_hit = tray.origin + t_base * tray.direction;

		if(t_base > 0) {
			if(glm::length(base_hit - glm::vec3{ 0,0,-1}) <= 1) {
				if((c1 && c2 && t_base < t1 && t_base < t2) || 
           (c1 && t_base < t1) || 
           (c2 && t_base < t2)) {
					hitpoint = base_hit;
					distance = t_base;
					normal   = glm::normalize(glm::vec3{ 0, 0 , -1.0f });
					did_hit  = true;
				}
			}
		}
  
    if(did_hit) { 
      /* for calculating hitpoint and normal */
      glm::vec4 t_hit    = world_transform_ * glm::vec4{hitpoint, 1};
		  glm::vec4 t_normal = glm::normalize(glm::transpose(world_transform_inv_) * 
                           glm::vec4{normal, 0});

      hit.did_intersect  = did_hit;
      hit.point          = glm::vec3{t_hit.x, t_hit.y, t_hit.z };
      hit.t              = glm::length(hitpoint - ray.origin);
      hit.name           = name_;
      hit.clr            = material_->ka;
      hit.direction      = tray.direction;
      hit.normal         = glm::vec3{t_normal.x, t_normal.y, t_normal.z};
    }
  }

  //transformBack(hit, world_transform_, glm::transpose(world_transform_inv_));
  return hit;
}