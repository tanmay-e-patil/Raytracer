#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    Hit hit;
    Hit closest_hit = {0,0,0};
    float min_distance = -1;

    for(unsigned int i = 0; i < this->objects.size(); i++)
    {
        hit = this->objects[i]->Intersection(ray,i);
        if(hit.dist == 0)
        {
            continue;
        }
        float distance = hit.dist;
        if(min_distance == -1)
        {
            if (distance > small_t)
            {
                closest_hit = hit;
                min_distance = distance;
                
            }
        } 
        else
        {
            if (min_distance > distance)
            {
                closest_hit = hit;
                min_distance = distance;
            }
        }
    }
    return closest_hit;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    // set up the initial view ray here
    Ray ray;
    vec3 direction;
    ray.endpoint = this->camera.position;
	direction = this->camera.World_Position(pixel_index);
    ray.direction = direction.normalized();
    vec3 color=Cast_Ray(ray,recursion_depth_limit);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
    
	
    
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    if (recursion_depth == 0)
    {
        return this->background_shader->Shade_Surface(ray,ray.endpoint,ray.endpoint,this->recursion_depth_limit);//{0.0,0.0,0.0};
    }
    vec3 color;
    // determine the color here
    Hit closest_hit = this->Closest_Intersection(ray);
    if (closest_hit.dist == 0)
    {
        color = this->background_shader->Shade_Surface(ray,ray.endpoint,ray.endpoint,this->recursion_depth_limit);
    }
    else
    {
        vec3 intersection_point = ray.endpoint + (closest_hit.dist * ray.direction);
        vec3 normal = closest_hit.object->Normal(intersection_point, closest_hit.part).normalized();
        color = closest_hit.object->material_shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
    }
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    //TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.
    unsigned int size = 0;

    for(unsigned int i = 0; i < this->objects.size(); i++)
    {
        size += this->objects[i]->number_parts;
    }

    hierarchy.entries.resize(size);
    hierarchy.tree.resize(2*size - 1);

    
    for(unsigned int i = 0; i < this->objects.size(); i++)
    {
        for(int j = 0; j < this->objects[i]->number_parts; j++)
        {

            hierarchy.entries[j] = Entry{this->objects[i], j, this->objects[i]->Bounding_Box(j)};

        }    
    }

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
