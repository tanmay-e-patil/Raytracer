#include <algorithm>
#include "hierarchy.h"

// Reorder the entries vector so that adjacent entries tend to be nearby.
// You may want to implement box.cpp first.
void Hierarchy::Reorder_Entries()
{
    if(!entries.size()) return;

    TODO;
}

// Populate tree from entries.
void Hierarchy::Build_Tree()
{
    Box b;

    if(!entries.size()) return;
    b.Union(entries[0].box);
    for (int i=1;i<entries.size();i++)
    {
        b.Union(entries[i].box);
    }
    TODO;
}

// Return a list of candidates (indices into the entries list) whose
// bounding boxes intersect the ray.
void Hierarchy::Intersection_Candidates(const Ray& ray, std::vector<int>& candidates) const
{
    TODO;
}
 // for (int j = 0;j<i;j++)
        // {
        //     tree.push_back(entries[i].box);
        // }