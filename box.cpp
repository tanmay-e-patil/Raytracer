#include <limits>
#include "box.h"

// Return whether the ray intersects this box.
bool Box::Intersection(const Ray& ray) const
{
    TODO;
    double xe = ray.endpoint[0];
    double ye = ray.endpoint[1];
    double ze = ray.endpoint[2];

    // double xd = ray.direction[0];
    // double yd = ray.direction[1];
    // double zd = ray.direction[2];

    // double t_xmin,t_ymin,t_zmin;
    // double t_xmax,t_ymax,t_zmax;

    bool is_x = xe > this->lo[0] && xe < this->hi[0];
    bool is_y = ye > this->lo[1] && ye < this->hi[1];
    bool is_z = ze > this->lo[2] && ze < this->hi[2];
    if(is_x && is_y && is_z)
    {
        return true;
    }
    return false;
    
    // if(xe > this->lo[])

    // if (xd >= 0)
    // {
    //     t_xmin = (this->lo[0] - xe)/xd;
    //     t_xmax = (this->hi[0] - xe)/xd;
    // }
    // else
    // {
    //     t_xmin = (this->hi[0] - xe)/xd;
    //     t_xmax = (this->lo[0] - xe)/xd;
    // }

    // if (yd >= 0)
    // {
    //     t_ymin = (this->lo[1] - ye)/yd;
    //     t_ymax = (this->hi[1] - ye)/yd;
    // }
    // else
    // {
    //     t_ymin = (this->hi[1] - ye)/yd;
    //     t_ymax = (this->lo[1] - ye)/yd;
    // }

    // if (zd >= 0)
    // {
    //     t_zmin = (this->lo[2] - ze)/zd;
    //     t_zmax = (this->hi[2] - ze)/zd;
    // }
    // else
    // {
    //     t_zmin = (this->hi[2] - ze)/zd;
    //     t_zmax = (this->lo[2] - ze)/zd;
    // }

    



    // return true;
}

// Compute the smallest box that contains both *this and bb.
Box Box::Union(const Box& bb) const
{
    Box box;
    TODO;
    box.hi[0] = std::max(this->hi[0],bb.hi[0]);
    box.hi[1] = std::max(this->hi[1],bb.hi[1]);
    box.hi[2] = std::max(this->hi[2],bb.hi[2]);

    box.lo[0] = std::min(this->hi[0],bb.hi[0]);
    box.lo[1] = std::min(this->hi[1],bb.hi[1]);
    box.lo[2] = std::min(this->hi[2],bb.hi[2]);
    return box;
}

// Enlarge this box (if necessary) so that pt also lies inside it.
void Box::Include_Point(const vec3& pt)
{
    this->hi[0] = std::max(this->hi[0],pt[0]);
    this->hi[1] = std::max(this->hi[1],pt[1]);
    this->hi[2] = std::max(this->hi[2],pt[2]);

    this->lo[0] = std::min(this->lo[0],pt[0]);
    this->lo[1] = std::min(this->lo[1],pt[1]);
    this->lo[2] = std::min(this->lo[2],pt[2]);

    TODO;
}

// Create a box to which points can be correctly added using Include_Point.
void Box::Make_Empty()
{
    lo.fill(std::numeric_limits<double>::infinity());
    hi=-lo;
}
