#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    vec3 w = ray.endpoint - this->center;
    vec3 u = ray.direction.normalized();
    float w_dot_u = dot(w,u);
    float d = w_dot_u * w_dot_u - (w.magnitude_squared() - (this->radius * this->radius)); // Discriminant
    Hit hit;
    
    if (d >= 0)
    {
        float t1 = -w_dot_u + sqrt(d); // First root
        float t2 = -w_dot_u - sqrt(d); // Second Root

        if (t1 > small_t || t2 > small_t)
        {
            if (t1 < small_t)
            {
                hit.object = this;
                hit.dist = t2;
                hit.part = part;
            }
            

            else if (t2 < small_t)
            {
                hit.object = this;
                hit.dist = t1;
                hit.part = part;
            }

            else
            {
                if (t1 < t2)
                {
                    hit.object = this;
                    hit.dist = t1;
                    hit.part = part;
                }
                else
                {
                    hit.object = this;
                    hit.dist = t2;
                    hit.part = part;
                }
                
            }
            return hit;
        }
    }
    return {0,0,0};
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    // compute the normal direction
    normal = (point - this->center);
    normal = normal.normalized();
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    box.hi[0] = this->center[0] + this->radius;
    box.hi[1] = this->center[1] + this->radius;
    box.hi[2] = this->center[2] + this->radius;

    box.lo[0] = this->center[0] - this->radius;
    box.lo[1] = this->center[1] - this->radius;
    box.lo[2] = this->center[2] - this->radius;
    return box;
}
