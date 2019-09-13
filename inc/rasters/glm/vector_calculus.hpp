#pragma once

#include <glm/vec3.hpp>               // *vec3

#include "../types.hpp"

namespace rasters
{
	template<typename T1, typename T2, qualifier Q>
	void gradient(const traster<T1>& scalar_field, traster<glm::vec<3,T2,Q>>& result)
	{
		// NOTE: 
		// The naive implementation is to estimate the gradient based on each individual neighbor,
		//  then take the average between the estimates.
		// This is wrong! If dx is very small, 
		//  then the gradient estimate along that dimension will be very big.
		// This will result in very strange behavior.
		//
		// The correct implementation is to use the Gauss-Green theorem: 
		//   ∫∫∫ᵥ ∇ϕ dV = ∫∫ₐ ϕn̂ da
		// so:
		//   ∇ϕ = 1/V ∫∫ₐ ϕn̂ da
		// So if this were 3d, we'd find flux out of an area, then divide by volume.
		// Since we're dealing with a 2d surface,
		//   we find flux out of a perimeter, then divide by area.
		// The "perimeter" and "area" that we measure is for a circle around the vertex. 
		//   The circle reaches halfway to its neighbors, so its radius is half the distance to its neighbor
		uvec2 arrow (0);
		uint  from  (0);
		uint  to    (0);
		float df    (0);
		fill(result, glm::vec<3,T2,Q>(0));
		for (unsigned int i = 0; i < scalar_field.grid->arrow_vertex_ids.size(); ++i)
		{
			arrow = scalar_field.grid->arrow_vertex_ids[i]; 
			from  = arrow.x; 
			to    = arrow.y; 
			df    = scalar_field[to] - scalar_field[from]; 
			// we multiply df by the circumference of a circle around the vertex that reaches halfway to its neighbor,
			//   this gives us the flux out of this representative circle 
			// we then add the flux to result in prep to find the average flux around the vertex
			result[from] += df * scalar_field.grid->arrow_offsets[i]; // (PI cancels out)
		}
		// we divide by the number of neighbors to get the average flux around the vertex
		result /= scalar_field.grid->vertex_neighbor_counts; 
		// we then divide by the area of the circle to get the gradient
		result *= 1.f / ((scalar_field.grid->arrow_average_distance/2) * (scalar_field.grid->arrow_average_distance/2)); // (PI cancels out)
	}
}