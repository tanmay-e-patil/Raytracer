#include "plane.h"
#include "ray.h"
#include <cfloat>
#include <limits>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
    vec3 plane_vector = ray.endpoint - x1;
    float plane_eq = dot(plane_vector,normal);
    float ray_dot_normal = dot(ray.direction,normal);

    Hit hit = {0,0,0};

    if (plane_eq <= 0)
    {
        if (ray_dot_normal <= 0)
        {
            hit.object = this;
            hit.dist = DBL_MAX;
        }
        else
        {
            hit.object = this;
            hit.dist = - plane_eq / ray_dot_normal ;
        }
    }
    else
    {
        if (ray_dot_normal < 0)
        {
            hit.object = this;
            hit.dist = - plane_eq / ray_dot_normal ;
        }
        
    }
    return hit;
}

vec3 Plane::Normal(const vec3& point, int part) const
{
    return normal;
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo=-b.hi;
    return b;
}
