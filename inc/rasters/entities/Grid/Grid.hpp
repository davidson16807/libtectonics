#pragma once


// std libraries
#include <memory>

// 3rd party libraries
#include <glm/vec3.hpp>               // *vec3

// in-house libraries
#include <many/types.hpp>
#include <many/glm/types.hpp>

#include <rasters/components/MeshCache.hpp>

namespace rasters
{

	/*
	"types.hpp" represents the objects and functions of a mathematical category.
	The category concerns the ways in which grids and rasters can be specified 
	so that the attributes of an object always maintain internal consistency.

	Since most of the objects of the category are implemented in ways that require memory management,
	we have to encapsulate the objects, and can only expose the functions of the category as methods.
	The implementations are rather small, and often rely on inheritance to share protected attributes.
	For these reasons, we prefer to store the category in a single file,
	where we can easily survey interactions in protected attributes. 

	The category manifests as an implementation of the Entity/Component/System (ECS) pattern.
	A naive implementation of *Grids exhibits a "diamond inheritance" pattern 
	that suggests an ECS implementation would be preferable to an inheritance hierarchy.
	A simple implemention would just pass each component through the signatures of functions that operate on Grids,
	However any combination of these components may have strict relationships that must be preserved, 
	for instance, the vertex indices stored within SpheroidVoronoi must reference valid vertices within MeshCache. 
	so we would like to guarantee both the rasters and grid components we provide are compatible with one another.
	This requires that the class use encapsulation to strictly control the construction of grids and rasters. 
	However we can still leverage the grid components of an ECS implementation to compose the encapsulated classes.
	This allows us to better reason with multiple inhertance concerns.
    We can use templates to prevent much of the headache concerning diamond inheritance,
    and only resort to inheritance where a class needs to be able to access the shared pointers of its base.

	We must also consider that the grid components take up large memory footprints,
	so we cannot simply copy grid components by value, as we would prefer. 
	We instead use shared pointers to alleviate issues we may have with sharing grid component references across many objects,
	and leverage the exising encapsulation requirements (mentioned above) to further regulate where shared pointers go.
	The shared pointers are never exposed to code outside the grid classes.
	The grid then becomes a small object filled only with smart pointers, 
	and since we've found this property is useful when creating rasters, 
	we further go on the offensive to guarantee that the footprint of a Grid class will never exceed 24 bytes.
	*/

    template<typename Tid=std::uint16_t, typename Tfloat=float>
	struct Grid
	{
		std::shared_ptr<MeshCache<Tid,Tfloat>> cache;

		Grid(const many::vec3s& vertices, const many::uvec3s& faces):
			cache(std::make_shared< MeshCache<Tid,Tfloat>>(vertices, faces))
		{}
		const std::size_t cell_count() const
		{
			return this->cache->vertex_count;
		}
		const std::size_t arrow_count() const
		{
			return this->cache->arrow_count;
		}
		bool operator== (const Grid& other) const
		{
		    return (this->cache == other.cache);
		}
		bool operator!= (const Grid& other) const
		{
		    return !((*this)==other);
		}
	};
}