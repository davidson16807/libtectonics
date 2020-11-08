#pragma once

// 3rd party libraries
#define GLM_FORCE_PURE      // disable anonymous structs so we can build with ISO C++
#include <glm/vec3.hpp>               // *vec3

// in-house libraries
#include <many/types.hpp>
#include <many/glm/types.hpp>
#include <many/glm/random.hpp>

#include <meshes/mesh.hpp>

#include <rasters/entities/raster.hpp>
#include <rasters/entities/convenience.hpp>
#include <rasters/entities/operators.hpp>

#include "LayeredGrid.hpp"
#include "layered_raster.hpp"
#include "layering.hpp"

#include <rasters/entities/Grid/Grid_test_utils.hpp>

rasters::LayeredGrid<int,float> layered_diamond_grid(diamond_grid, 1.0f, 0.0f, 2u);

rasters::LayeredGrid<int,float> layered_tetrahedron_grid(tetrahedron_grid, 1.0f, 0.0f, 2u);

rasters::LayeredGrid<int,float> layered_nonspheroid_octahedron_grid(nonspheroid_octahedron_grid, 1.0f, 0.0f, 2u);

rasters::LayeredGrid<int,float> layered_nonspheroid_icosahedron_grid(nonspheroid_icosahedron_grid, 1.0f, 0.0f, 2u);

template <typename Tid, typename Tgrid, typename Tgenerator>
rasters::layered_raster<float,rasters::LayeredGrid<Tid,Tgrid>> get_random_layered_raster(rasters::LayeredGrid<Tid,Tgrid> layered_grid, Tgenerator generator){
    rasters::Grid<Tid,Tgrid> grid(layered_grid);

    auto a_flat      = rasters::make_raster<float>(grid);
    many::get_elias_noise(grid.cache->vertex_positions, generator, a_flat);

    auto a_offset    = rasters::make_raster<float>(grid);
    many::get_elias_noise(grid.cache->vertex_positions, generator, a_offset);

    // offset the middle layer to test vector calculus operations across layers
    auto a           = rasters::make_layered_raster<float>(layered_grid);
    rasters::repeat_layers(a_flat, a);
    rasters::set_layer(a, 1, a_flat+a_offset, a);

    return a;
}

template <typename Tid, typename Tgrid, typename Tgenerator>
rasters::layered_raster<glm::vec3, rasters::LayeredGrid<Tid,Tgrid>> get_random_layered_vector_raster(rasters::LayeredGrid<Tid,Tgrid> layered_grid, Tgenerator generator)
{
    auto u = rasters::make_layered_raster<glm::vec3>(layered_grid);

    many::set_x(u, get_random_layered_raster(layered_grid, generator), u);
    many::set_y(u, get_random_layered_raster(layered_grid, generator), u);
    many::set_z(u, get_random_layered_raster(layered_grid, generator), u);

    return u;
}