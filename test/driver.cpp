

#define GLM_FORCE_PURE      // disable SIMD support for glm so we can work with webassembly
#include <glm/glm.hpp>               // *vec3

#include <many/many.hpp>  //  floats, etc.
#include <many/glm/glm.hpp>    // *vec*s

#include "rasters/raster.hpp"         
#include "rasters/glm/vec_raster.hpp"
#include "rasters/glm/vector_calculus.hpp"

// #include "academics/tectonics.hpp"

using namespace many;
using namespace rasters;

std::shared_ptr<Grid> tetrahedron = 
    std::make_shared<Grid>(
        vec3s({
                vec3(0,0,0),
                vec3(1,0,0),
                vec3(0,1,0),
                vec3(0,0,1)
            }),
        uvec3s({
                uvec3(0,1,2),
                uvec3(0,1,3),
                uvec3(0,2,3),
                uvec3(1,2,3)
            })
    );
// "diamond" is a 2d grid, it looks like this:
//   2  
//  /|\ 
// 3-0-1
//  \|/ 
//   4   
std::shared_ptr<Grid> diamond = 
    std::make_shared<Grid>(
        vec3s({
                vec3( 0, 0, 0),
                vec3( 1, 0, 0),
                vec3( 0, 1, 0),
                vec3(-1, 0, 0),
                vec3( 0,-1, 0)
            }),
        uvec3s({
                uvec3(0,1,2),
                uvec3(0,1,4),
                uvec3(0,3,2),
                uvec3(0,3,4)
            })
    );

SphereGridVoronoi voronoi_test(
        vec3s({
                normalize(vec3( 1, 0, 0)),
                normalize(vec3( 0, 1, 0)),
                normalize(vec3( 0, 0, 1)),
                normalize(vec3(-1, 0, 0)),
                normalize(vec3( 0,-1, 0)),
                normalize(vec3( 0, 0,-1)),
                normalize(vec3(-1,-1,-1)),
                normalize(vec3( 1,-1,-1)),
                normalize(vec3(-1, 1,-1)),
                normalize(vec3( 1, 1,-1)),
                normalize(vec3(-1,-1, 1)),
                normalize(vec3( 1,-1, 1)),
                normalize(vec3(-1, 1, 1)),
                normalize(vec3( 1, 1, 1)),
                normalize(vec3( 1, 1, 1))
            }),
        1./100.
    );

int main(int argc, char const *argv[])
{
    //    0   
    //  / | \ 
    // 0- 1- 1
    //  \ | / 
    //    0    
    bool_raster  plate_mask = bool_raster (diamond, {1,1,0,0,0});
    //    0  
    //  / | \ 
    // 0--1- 0
    //  \ | / 
    //    0   
    float_raster buoyancy  = float_raster(diamond, {0,-1,0,0,0});
    float        mantle_viscosity = 1.57e20;
    vec3_raster  result = vec3_raster(diamond);
    //    0   
    //  / | \ 
    // 0- < -0
    //  \ | / 
    //    0    
    // gradient(plate_mask, tetrahedron, result);
    // academics::tectonics::guess_plate_velocity(plate_mask, buoyancy, mantle_viscosity, result);
    std::cout << result << std::endl;

    // std::cout << diamond->voronoi->nearest_id(vec3(-1, 0, 0))        << std::endl;

    // std::cout << "voronoi test:" << std::endl;

    // std::cout << voronoi_test.nearest_id(vec3(1))        << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3(-1))       << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3( 1, 0, 0)) << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3( 0, 1, 0)) << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3( 0, 0, 1)) << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3(-1, 0, 0)) << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3( 0,-1, 0)) << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3( 0, 0,-1)) << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3(-1,-1,-1)) << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3( 1,-1,-1)) << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3(-1, 1,-1)) << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3( 1, 1,-1)) << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3(-1,-1, 1)) << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3( 1,-1, 1)) << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3(-1, 1, 1)) << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3( 1, 1, 1)) << std::endl;
    // std::cout << voronoi_test.nearest_id(vec3( 1, 1, 1)) << std::endl;


    return 0;
}


