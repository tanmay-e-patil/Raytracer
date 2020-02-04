#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"
#include "phong_shader.h"

int i; 
vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color = this->shader->Shade_Surface(ray,intersection_point,normal,recursion_depth);
    // int i = this->shader->world.recursion_depth_limit
    // std::cout<<this->shader->world.recursion_depth_limit<<"\t"<<recursion_depth<<std::endl;
    
    vec3 reflected_vector = ray.direction - normal* (2 * dot(ray.direction,normal));
    Ray reflected_ray = Ray(intersection_point + (normal * small_t),reflected_vector);
   
    color = (1 - reflectivity) * color;
    color += reflectivity*(this->world.Cast_Ray(reflected_ray,recursion_depth - 1));
    return color;
    
}
