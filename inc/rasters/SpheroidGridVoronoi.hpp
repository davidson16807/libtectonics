#pragma once

#include <math.h>       // ceil, round 
#include <algorithm> 	// max, min, clamp
#include <vector>		// vectors
#include <array>		// arrays
#include <iostream>		// cout
#include <limits>       // infinity

#include <many/types.hpp>
#include <many/glm/types.hpp>
#include <many/glm/geometric.hpp>

namespace rasters
{
	namespace
	{
		using namespace glm;
		using namespace many;
	}

	// performs O(1) lookups on the surface of a unit sphere 
	// using an octahedron where each side is a 2d cartesian grid
	template <class T>
	class SpheroidGridLookup
	{
	protected:
		static constexpr int OCTAHEDRON_SIDE_COUNT = 8;	// number of sides on the data cube
		static const std::array<vec3, OCTAHEDRON_SIDE_COUNT> OCTAHEDRON_SIDE_Z;
		static const std::array<vec3, OCTAHEDRON_SIDE_COUNT> OCTAHEDRON_SIDE_X;
		static const std::array<vec3, OCTAHEDRON_SIDE_COUNT> OCTAHEDRON_SIDE_Y;

		ivec2 dimensions; // dimensions of the grid on each side of the data cube 
		float cell_width;
		std::vector<T> cells;

		int cell_count() const {
			return OCTAHEDRON_SIDE_COUNT * dimensions.x * dimensions.y;
		}
		int get_memory_id(const int xi2d, const int yi2d, const int side_id) const {
			return  std::clamp(side_id, 0, OCTAHEDRON_SIDE_COUNT-1) * dimensions.x * dimensions.y 
				  + std::clamp(xi2d,    0, dimensions.x-1)          * dimensions.y 
				  + std::clamp(yi2d,    0, dimensions.y-1);
		}
		int get_memory_id(const ivec3 conceptual_id) const {
			return get_memory_id(conceptual_id.x, conceptual_id.y, conceptual_id.z);
		}

		vec3 get_midpoint(const int xi2d, const int yi2d, const int side_id) const 
		{
			// get position of the cell that's projected onto the 2d grid
			float x2d = (float)xi2d * cell_width - 1.;
			float y2d = (float)yi2d * cell_width - 1.;
			// reconstruct the dimension omitted from the grid using pythagorean theorem
			float z2d = sqrt(std::max(1. - (x2d*x2d) - (y2d*y2d), 0.));

			return OCTAHEDRON_SIDE_X[side_id] * x2d +
				   OCTAHEDRON_SIDE_Y[side_id] * y2d +
				   OCTAHEDRON_SIDE_Z[side_id] * z2d ;
		}
		vec3 get_midpoint(const ivec3 conceptual_id) const 
		{
			return get_midpoint(conceptual_id.x, conceptual_id.y, conceptual_id.z);
		}
	public:
		~SpheroidGridLookup()
		{
		}
		explicit SpheroidGridLookup(
			const float cell_width
		) : 
			dimensions((int)ceil(2./cell_width)+1),
			cell_width(cell_width),
			cells(cell_count(), T(0))
		{
		}
		explicit SpheroidGridLookup(
			const float cell_width,
			const T default_value
		) : 
			dimensions((int)ceil(2./cell_width)+1),
			cell_width(cell_width),
			cells(cell_count(), default_value)
		{
		}

		ivec3 get_conceptual_id(const int xi2d, const int yi2d, const int side_id) const
		{
			return ivec3(xi2d, yi2d, side_id);
		}
		ivec3 get_conceptual_id(const vec3 point, const int side_id) const
		{
			const double x2d = dot( OCTAHEDRON_SIDE_X[side_id], point );
			const double y2d = dot( OCTAHEDRON_SIDE_Y[side_id], point );

			const int xi2d = (x2d + 1.) / cell_width;
			const int yi2d = (y2d + 1.) / cell_width;
			
			return ivec3(xi2d, yi2d, side_id);
		}
		ivec3 get_conceptual_id(const vec3 point) const
		{
			const unsigned int side_id = 
			  (( point.x > 0) << 0) +
			  (( point.y > 0) << 1) +
			  (( point.z > 0) << 2) ; 
			
			return get_conceptual_id(point, side_id);
		}

		T& get_ref(const ivec3 conceptual_id)
		{
			return cells[get_memory_id(conceptual_id)];
		}

		T get_value(const ivec3 conceptual_id) const
		{
			return cells[get_memory_id(conceptual_id)];
		}
		T& get_ref(const vec3 point)
		{
			return get_ref(get_conceptual_id(point));
		}

		T get_value(const vec3 point) const
		{
			return get_value(get_conceptual_id(point));
		}

		void get_values(const vec3s& points, tmany<T>& out) const
		{
			for (unsigned int i = 0; i < points.size(); ++i)
			{
				out[i] = get_value(get_conceptual_id(points[i]));
			}
		}

	};


	template <class T>
	const std::array<vec3, SpheroidGridLookup<T>::OCTAHEDRON_SIDE_COUNT> SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z =
		{
			glm::normalize(glm::vec3(-1,-1,-1)),
			glm::normalize(glm::vec3( 1,-1,-1)),
			glm::normalize(glm::vec3(-1, 1,-1)),
			glm::normalize(glm::vec3( 1, 1,-1)),
			glm::normalize(glm::vec3(-1,-1, 1)),
			glm::normalize(glm::vec3( 1,-1, 1)),
			glm::normalize(glm::vec3(-1, 1, 1)),
			glm::normalize(glm::vec3( 1, 1, 1))
		};
	template <class T>
	const std::array<vec3, SpheroidGridLookup<T>::OCTAHEDRON_SIDE_COUNT> SpheroidGridLookup<T>::OCTAHEDRON_SIDE_X =
		{
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[0], vec3(0,0,1))),
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[1], vec3(0,0,1))),
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[2], vec3(0,0,1))),
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[3], vec3(0,0,1))),
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[4], vec3(0,0,1))),
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[5], vec3(0,0,1))),
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[6], vec3(0,0,1))),
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[7], vec3(0,0,1)))
		};
	template <class T>
	const std::array<vec3, SpheroidGridLookup<T>::OCTAHEDRON_SIDE_COUNT> SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Y =
		{
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[0], SpheroidGridLookup<T>::OCTAHEDRON_SIDE_X[0])),
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[1], SpheroidGridLookup<T>::OCTAHEDRON_SIDE_X[1])),
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[2], SpheroidGridLookup<T>::OCTAHEDRON_SIDE_X[2])),
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[3], SpheroidGridLookup<T>::OCTAHEDRON_SIDE_X[3])),
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[4], SpheroidGridLookup<T>::OCTAHEDRON_SIDE_X[4])),
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[5], SpheroidGridLookup<T>::OCTAHEDRON_SIDE_X[5])),
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[6], SpheroidGridLookup<T>::OCTAHEDRON_SIDE_X[6])),
			glm::normalize(glm::cross(SpheroidGridLookup<T>::OCTAHEDRON_SIDE_Z[7], SpheroidGridLookup<T>::OCTAHEDRON_SIDE_X[7]))
		};

	// performs cached O(1) nearest neighbor lookups on the surface of a unit sphere
	// using a SpheroidGridLookup of vectors to optimize initialization
	class SpheroidGridVoronoi : public SpheroidGridLookup<uint>
	{
	public:
		explicit SpheroidGridVoronoi(
			const vec3s& points, 
			const float cell_width,
			const float max_vertex_distance
		  )	: 
			SpheroidGridLookup<uint>(cell_width, 0)
		{
			std::cout << "populating" << std::endl;
			// Populate a map of nearest neighbor ids and their distances
			// Since the nearest neighbor is guaranteed not to exceed max_vertex_distance,
			//  we traverse over the list of neighbors and populate all cells within that distance.
			// This is way faster than traversing over all cells to find the nearest neighbor
			std::vector<std::pair<int, float>> temp(cells.size(), std::pair<int, float>(-1, std::numeric_limits<float>::infinity()));
			int vicinity_radius = (max_vertex_distance/cell_width)/2 + 1;
			glm::ivec3 offset_id;
			glm::vec3 midpoint;
			float point_distance;
			float min_distance;
			for (uint point_id = 0; point_id < points.size(); ++point_id)
			{
				for (uint side_id = 0; side_id < OCTAHEDRON_SIDE_COUNT; ++side_id)
				{
					if (dot(OCTAHEDRON_SIDE_Z[side_id], points[point_id]) < (1/sqrt(3)) - max_vertex_distance) { continue; }
					glm::ivec3 center_id = get_conceptual_id(points[point_id], side_id);
					float center_distance = glm::distance(points[point_id], get_midpoint(center_id));
					if (center_distance > max_vertex_distance) { continue; }
					for (int xi2d = -vicinity_radius; xi2d < vicinity_radius; ++xi2d)
					{
						for (int yi2d = -vicinity_radius; yi2d < vicinity_radius; ++yi2d)
						{
							offset_id = center_id + glm::ivec3(xi2d, yi2d, 0);
							midpoint = get_midpoint(offset_id);
							point_distance = glm::distance(points[point_id], midpoint);
							if (point_distance > max_vertex_distance) { continue; }
							min_distance = temp[get_memory_id(offset_id)].second;
							if (point_distance >= min_distance) { continue; }
							temp[get_memory_id(offset_id)].first  = point_id;
							temp[get_memory_id(offset_id)].second = point_distance;
						}
					}
				}
			}
			// We won't need to use nearest neighbor distances any more, 
			//  and we want to reduce the footprint of memory that is accessed out-of-order,
			//  so we populate a final map containing only nearest neighbor ids
			for (uint i = 0; i < cells.size(); ++i)
			{
				cells[i] = temp[i].first;
			}
			std::cout << "populated" << std::endl;
		}
	};
}