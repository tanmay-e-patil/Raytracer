#include "mesh.h"
#include <fstream>
#include <string>
#include <limits>

// Consider a triangle to intersect a ray if the ray intersects the plane of the
// triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]
static const double weight_tolerance = 1e-4;

// Read in a mesh from an obj file.  Populates the bounding box and registers
// one part per triangle (by setting number_parts).
void Mesh::Read_Obj(const char* file)
{
    std::ifstream fin(file);
    if(!fin)
    {
        exit(EXIT_FAILURE);
    }
    std::string line;
    ivec3 e;
    vec3 v;
    box.Make_Empty();
    while(fin)
    {
        getline(fin,line);

        if(sscanf(line.c_str(), "v %lg %lg %lg", &v[0], &v[1], &v[2]) == 3)
        {
            vertices.push_back(v);
            box.Include_Point(v);
        }

        if(sscanf(line.c_str(), "f %d %d %d", &e[0], &e[1], &e[2]) == 3)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
        }
    }
    number_parts=triangles.size();
}

// Check for an intersection against the ray.  See the base class for details.
Hit Mesh::Intersection(const Ray& ray, int part) const
{
    //TODO;
    Hit hit = {0,0,0};
    double dist = 0.0;
    Hit temp = {0,0,0};
    for (int i = 0;i < number_parts;i++)
    {    
        if (Intersect_Triangle(ray,i,dist))
        {
            hit.dist = dist;
            hit.object = this;
            hit.part = i;
            if(temp.dist == 0)
            {
                temp = hit;
            }
            if(temp.dist > hit.dist)
            {
                temp = hit;
            }
        }
    }
    

    return temp;
}

// Compute the normal direction for the triangle with index part.
vec3 Mesh::Normal(const vec3& point, int part) const
{
    assert(part>=0);
    //TODO;
    vec3 A = vertices[triangles[part][0]];
    vec3 B = vertices[triangles[part][1]];
    vec3 C = vertices[triangles[part][2]];
    vec3 normal = cross(B-A,C-B).normalized();
    return normal;
}

// This is a helper routine whose purpose is to simplify the implementation
// of the Intersection routine.  It should test for an intersection between
// the ray and the triangle with index tri.  If an intersection exists,
// record the distance and return true.  Otherwise, return false.
// This intersection should be computed by determining the intersection of
// the ray and the plane of the triangle.  From this, determine (1) where
// along the ray the intersection point occurs (dist) and (2) the barycentric
// coordinates within the triangle where the intersection occurs.  The
// triangle intersects the ray if dist>small_t and the barycentric weights are
// larger than -weight_tolerance.  The use of small_t avoid the self-shadowing
// bug, and the use of weight_tolerance prevents rays from passing in between
// two triangles.
bool Mesh::Intersect_Triangle(const Ray& ray, int tri, double& dist) const
{
    //TODO;
    vec3 A = vertices[triangles[tri][0]];
    vec3 B = vertices[triangles[tri][1]];
    vec3 C = vertices[triangles[tri][2]];

    vec3 v = B - A;
    vec3 w = C - A;
    vec3 y = ray.endpoint - A;
    vec3 u = ray.direction;

    double opt = dot(cross(w,u),v);
    double beta = dot(cross(w,u),y)/opt;
    double gamma = dot(cross(u,v),y)/opt;
    double alpha = (1 - beta -gamma);
    
    bool is_beta = beta >= -weight_tolerance;// && beta <= (1 + weight_tolerance);
    bool is_gamma = gamma >= -weight_tolerance;// && gamma <= (1 + weight_tolerance);
    bool is_alpha = alpha >= -weight_tolerance;// && alpha <= (1 + weight_tolerance);
    // if (beta >= weight_tol && gamma >= weight_tol && (1 - beta - gamma) >= weight_tol)
    if(is_alpha && is_beta && is_gamma)
    {
        dist = -(dot(cross(v,w),y))/opt;
        if (dist >small_t)
        {
            return true;
        }
        
    }
    
    return false;
}

// Compute the bounding box.  Return the bounding box of only the triangle whose
// index is part.
Box Mesh::Bounding_Box(int part) const
{
    Box b;
    vec3 A = vertices[triangles[part][0]];
    vec3 B = vertices[triangles[part][1]];
    vec3 C = vertices[triangles[part][2]];
    b.Make_Empty();
    b.Include_Point(A);
    b.Include_Point(B);
    b.Include_Point(C);

    //TODO;
    return b;
}
