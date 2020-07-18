#pragma once

// #include "../LayeredGrid/LayeredGrid.hpp"
#include "../SpheroidGrid/SpheroidGrid.hpp"

namespace rasters 
{

	/*
	The LayeredSpheroidGrid struct is an extension of the SpheroidGrid struct
	It assumes the grid is comprised of a series of grid cells 
	over the surface of a roughly spherical object. 
	Each grid may be subdivided into several "layers" that occur at regular
	intervals along a dimension that's perpendicular to the surface. 
	*/
	struct LayeredSpheroidGrid: public SpheroidGrid//, public LayeredGrid
	{
		float profile_height;
		float layer_count;
		float layer_height;

		~LayeredSpheroidGrid()
		{

		}
		explicit LayeredSpheroidGrid(
			const many::vec3s& vertices, 
			const many::uvec3s& faces, 
			const float profile_height, 
			const float layer_count
		)
			: SpheroidGrid(vertices, faces),
			//  voronoi(vertices, 
			//		min(arrow_lengths / 8.f), 
			//		max(arrow_lengths * 1.f)
			//	),
			  profile_height(profile_height),
			  layer_count(layer_count),
			  layer_height(profile_height/layer_count)
		{

		}
	};

	template <typename T>
	void get_layer(const many::tmany<T>& a, const uint layer_id, many::tmany<T>& out) 
	{
		assert(a.size() > out.size());
		assert(a.size() % out.size() == 0);
		uint L = a.size() / out.size();
		for (uint i = 0; i < out.size(); ++i)
		{
			out[i] = a[i*L+layer_id];
		}
	}

	template <typename T, glm::qualifier Q>
	void get_layer(const many::tmany<glm::vec<2,T,Q>>& a, const uint layer_id, many::tmany<glm::vec<2,T,Q>>& out) 
	{
		assert(a.size() > out.size());
		assert(a.size() % out.size() == 0);
		uint L = a.size() / out.size();
		for (uint i = 0; i < out.size(); ++i)
		{
			out[i] = a[i*L+layer_id];
		}
	}

	template <typename T, glm::qualifier Q>
	void get_layer(const many::tmany<glm::vec<3,T,Q>>& a, const uint layer_id, many::tmany<glm::vec<3,T,Q>>& out) 
	{
		assert(a.size() > out.size());
		assert(a.size() % out.size() == 0);
		uint L = a.size() / out.size();
		for (uint i = 0; i < out.size(); ++i)
		{
			out[i] = a[i*L+layer_id];
		}
	}
}




