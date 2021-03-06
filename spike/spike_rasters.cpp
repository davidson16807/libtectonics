
// C libraries
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <signal.h>     // signal
#include <execinfo.h>   // backtrace
#include <unistd.h>     // STDERR_FILENO

// glm libraries
#define GLM_FORCE_PURE      // disable anonymous structs so we can build with ISO C++
#include <glm/vec3.hpp>               // *vec3

#include <series/series.hpp>  
#include <series/string_cast.hpp>  
#include <series/morphologic.hpp>  
#include <series/glm/glm.hpp>         // *vec*s
#include <series/glm/string_cast.hpp>  
#include <series/glm/random.hpp>  
#include <series/glm/convenience.hpp> //  operators, etc.

#include <meshes/mesh.hpp>
#include <grids/MeshCache/morphologic.hpp>
#include <grids/MeshCache/vector_calculus.hpp>
#include <grids/SpheroidGrid/string_cast.hpp>  

// #include "academics/tectonics.hpp"

using namespace glm;
using namespace series;
using namespace rasters;

void handler(int sig) {
      void *array[10];
      size_t size;

      // get void*'s for all entries on the stack
      size = backtrace(array, 10);

      // print out all the frames to stderr
      fprintf(stderr, "Error: signal %d:\n", sig);
      backtrace_symbols_fd(array, size, STDERR_FILENO);
      exit(1);
}

int main(int argc, char const *argv[])
{
    signal(SIGSEGV, handler);   // install our error handler
    signal(SIGABRT, handler);   // install our error handler

    /* 
    "diamond" is a simple 2d grid for testing raster operations 
     that do not require spatial awareness (e.g. arithmetic on scalar fields)
    It looks like this:
         2  
        /|\ 
       3-0-1
        \|/ 
         4   
    */
    MeshCache diamond = 
        MeshCache(
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
    /*
    "tetrahedron" is a simple 3d grid for testing basic raster operations
     that require spatial awareness without requiring a particular shape.
     (e.g. gradient, divergence, laplacian)
    */
    MeshCache tetrahedron = 
        MeshCache(meshes::tetrahedron.vertices, meshes::tetrahedron.faces);
    /*
    "octahedron" is a simple 3d grid for testing raster operations that require 
    something comparable to a unit sphere (e.g. nearest neighbor lookups using SpheroidVoronoi)
    */
    SpheroidGrid octahedron = 
        SpheroidGrid(meshes::octahedron.vertices, meshes::octahedron.faces);

    /*
    "icosahedron" is a simple 3d grid for testing rasters with a large number of vertices
    */
    SpheroidGrid icosahedron = 
        SpheroidGrid(meshes::icosahedron.vertices, meshes::icosahedron.faces);

    SpheroidVoronoi voronoi_test(
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
            1./100.,
            3./100.
        );

    floats a = floats({1,2,3,4,5});
    floats b = floats({1,1,2,3,5});
    floats c = floats({4,8,3,8,2,4,5,9,8,2,3,5,2,1,3,3,3,1,6,1,
                       4,2,5,INFINITY,9,4,6,2,8,1,5,3,7,5,8,5,6,6,7,6,
                       1,2,4,1,4,9,9,8,1,3,7,2,5,5,1,8,9,4,7,6,
                       4,4,4,5,3,1,3,5,8,3,4,1,3,7,5,6,2,9,7,5,
                       4,8,3,8,2,4,5,9,8,2,3,5,2,1,3,3,3,1,6,1,
                       4,2,5,9,9,9,9,9,9,9,9,9,9,9,8,5,6,6,7,6,
                       1,2,4,1,4,9,9,8,1,3,7,2,5,5,1,8,9,4,7,6,
                       4,4,4,5,3,1,3,5,8,3,4,1,3,7,5,6,2,9,7});

    std::string stra = to_string(a);
    std::string strb = to_string(b);
    std::string strc = to_string(c);
    std::cout << strc << std::endl;

    vec2s v2d = vec2s({
        vec2(-1,-1),
        vec2(-1, 1),
        vec2(-1,-0.1),
        vec2(-1, 0.1),
        vec2(-1, 0.0),
    });
    vec3s v3d = vec3s({
        vec3(-1,-1,-1),
        vec3( 0,-1,-1),
        vec3( 1,-1,-1),
        vec3(-1, 0,-1),
        vec3( 0, 0,-1),
        vec3( 1, 0,-1),
        vec3(-1, 1,-1),
        vec3( 0, 1,-1),
        vec3( 1, 1,-1),

        vec3(-1,-1, 0),
        vec3( 0,-1, 0),
        vec3( 1,-1, 0),
        vec3(-1, 0, 0),
        vec3( 0, 0, 0),
        vec3( 1, 0, 0),
        vec3(-1, 1, 0),
        vec3( 0, 1, 0),
        vec3( 1, 1, 0),

        vec3(-1,-1, 1),
        vec3( 0,-1, 1),
        vec3( 1,-1, 1),
        vec3(-1, 0, 1),
        vec3( 0, 0, 1),
        vec3( 1, 0, 1),
        vec3(-1, 1, 1),
        vec3( 0, 1, 1),
        vec3( 1, 1, 1),
    });
    std::string str_v2d = to_string(v2d);
    std::string str_v3d = to_string(v3d, glm::mat3x2(1,1,0, 
                                                     0,1,1));
    std::cout << str_v2d << std::endl;
    std::cout << str_v3d << std::endl;

    floats raster_a = floats({0,1,2,3,4,5});
    std::string str_raster_a = to_string(octahedron, raster_a);
    std::cout << str_raster_a << std::endl;

    vec2s raster_v2 = vec2s({
        vec2( 0,-1),
        vec2( 0, 1),
        vec2(-1, 0),
        vec2( 1, 0),
        vec2(-1,-1),
        vec2( 1, 1),
    });
    vec3s raster_v3 = vec3s({
        vec3( 0, 1, 0),
        vec3( 0, 1, 0),
        vec3( 0, 1, 0),
        vec3( 0, 1, 0),
        vec3( 0, 1, 0),
        vec3( 0, 1, 0),
    });

    std::string str_raster_v2 = rasters::to_string(octahedron, raster_v2);
    std::cout << str_raster_v2 << std::endl;

    std::string str_raster_v3 = rasters::to_string(octahedron, raster_v3);
    std::cout << str_raster_v3 << std::endl;

    std::mt19937 generator(2);
    meshes::mesh icosphere_mesh(meshes::icosahedron.vertices, meshes::icosahedron.faces);
    icosphere_mesh = meshes::subdivide(icosphere_mesh); series::normalize(icosphere_mesh.vertices, icosphere_mesh.vertices);
    icosphere_mesh = meshes::subdivide(icosphere_mesh); series::normalize(icosphere_mesh.vertices, icosphere_mesh.vertices);
    icosphere_mesh = meshes::subdivide(icosphere_mesh); series::normalize(icosphere_mesh.vertices, icosphere_mesh.vertices);
    icosphere_mesh = meshes::subdivide(icosphere_mesh); series::normalize(icosphere_mesh.vertices, icosphere_mesh.vertices);
    icosphere_mesh = meshes::subdivide(icosphere_mesh); series::normalize(icosphere_mesh.vertices, icosphere_mesh.vertices);
    icosphere_mesh = meshes::subdivide(icosphere_mesh); series::normalize(icosphere_mesh.vertices, icosphere_mesh.vertices);
    std::cout << icosphere_mesh.vertices.size() << std::endl;
    SpheroidGrid icosphere(icosphere_mesh.vertices, icosphere_mesh.faces);
    floats raster_b = floats(icosphere_mesh.vertices.size());
    get_elias_noise(icosphere.vertex_positions, generator, raster_b, 10, 0.0001f);
    std::string str_raster_b = to_string(icosphere, raster_b);
    std::cout << str_raster_b << std::endl;

    floats raster_c = floats(icosphere_mesh.vertices.size());
    get_elias_noise(icosphere.vertex_positions, generator, raster_c);
    std::string str_raster_c = to_string(icosphere, raster_c);
    std::cout << str_raster_c << std::endl;

    floats gradient_in = raster_c;
    vec3s gradient_out = rasters::gradient(icosphere, gradient_in);
    std::cout << "calculating gradient" << std::endl;
    std::cout << rasters::to_string(icosphere, gradient_out) << std::endl;

    vec3s divergence_in = gradient_out;
    std::cout << "calculating divergence" << std::endl;
    std::cout << rasters::to_string(icosphere, rasters::divergence(icosphere, divergence_in)) << std::endl;

    vec3s curl_in = gradient_out;
    std::cout << "calculating curl" << std::endl;
    std::cout << rasters::to_string(icosphere, rasters::curl(icosphere, curl_in)) << std::endl;

    floats laplacian_in = raster_c;
    std::cout << "calculating laplacian" << std::endl;
    std::cout << rasters::to_string(icosphere, rasters::laplacian(icosphere, laplacian_in)) << std::endl;

    // std::mt19937 randomizer;
    // std::cout << randomizer() << " " << randomizer() << std::endl;
    // std::cout << randomizer;


}