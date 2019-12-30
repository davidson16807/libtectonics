#pragma once

#include "../LayeredGrid/LayeredGrid.hpp"
#include "../SpheroidGrid/string_cast.hpp"

namespace rasters
{
	template <unsigned int L, typename T, glm::qualifier Q>
	std::string to_string(
		const LayeredSpheroidGrid& grid, 
		const many::tmany<glm::vec<L,T,Q>>& a, 
		const uint line_char_width = 80, 
		const glm::vec3 up = vec3(0,0,1)
	) {
		std::cout << "foo: " << a.size() << " " << grid.vertex_count << " " << grid.layer_count << std::endl;
		assert(a.size() == grid.vertex_count * grid.layer_count);
		many::tmany<T> layer_raster(grid.vertex_count);
		std::string out("");
		for (uint i = 0; i < grid.layer_count; ++i)
		{
			get_layer(a, i, layer_raster);
			out += to_string(grid.voronoi, grid.vertex_normals, layer_raster, line_char_width, up);
			out += "\n";
		}
		return out;
	}


	template <typename T>
	std::string to_string(
		const LayeredSpheroidGrid& grid, 
		const many::tmany<T>& a, 
		const uint line_char_width = 80, 
		const glm::vec3 up = vec3(0,0,1)
	) {
		std::cout << "foo: " << a.size() << " " << grid.vertex_count << " " << grid.layer_count << std::endl;
		assert(a.size() == grid.vertex_count * grid.layer_count);
		many::tmany<T> layer_raster(grid.vertex_count);
		std::string out("");
		for (uint i = 0; i < grid.layer_count; ++i)
		{
			get_layer(a, i, layer_raster);
			out += to_string(grid.voronoi, layer_raster, min(a), max(a), line_char_width);
			out += "\n";
		}
		return out;
	}

}//namespace rasters



