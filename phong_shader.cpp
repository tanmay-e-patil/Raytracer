#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{

	vec3 ambient = color_ambient * this->world.ambient_color * this->world.ambient_intensity;
    vec3 diffuse;
    vec3 specular;
     
    for(unsigned int i = 0; i < this->world.lights.size(); i++)
    {
		vec3 light_vector = this->world.lights[i]->position - intersection_point;
		vec3 intensity = this->world.lights[i]->Emitted_Light(light_vector);
		vec3 v = (intersection_point - ray.endpoint).normalized();
		Ray light_ray = Ray(intersection_point + (small_t * normal),light_vector);
		float cos_theta = std::max(dot(light_ray.direction,normal),0.0);
		vec3 reflection = (light_ray.direction - normal * (2 * cos_theta)).normalized();
		float cos_phi = std::max(dot(v,reflection),0.0);	
		if(this->world.enable_shadows)
		{		
			
			Hit hit = this->world.Closest_Intersection(light_ray);
			if(hit.object == 0 || light_vector.magnitude() <= (light_ray.direction * hit.dist).magnitude()) 
			{
				diffuse = diffuse + color_diffuse * intensity * cos_theta;
				specular = specular + color_specular * intensity * pow(cos_phi,specular_power); 
			}			
	    }
	    else
	    {		
			diffuse = diffuse + color_diffuse * intensity * cos_theta;
			specular = specular + color_specular * intensity * pow(cos_phi,specular_power); 
		}	
	}
	return diffuse + ambient + specular; 
}
