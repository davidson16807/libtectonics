
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <signal.h>     // signal
#include <execinfo.h>   // backtrace
#include <unistd.h>     // STDERR_FILENO
#include <random>       // rngs

#define GLM_FORCE_PURE      // disable anonymous structs so we can build with ISO C++
#include <glm/vec3.hpp>               // *vec3

#include <series/types.hpp>         // *vec*s
#include <series/glm/glm.hpp>         // *vec*s

#include <meshes/mesh.hpp>
#include <grids/LayeredSpheroidGrid/LayeredSpheroidGrid.hpp>
#include <grids/LayeredSpheroidGrid/string_cast.hpp> 
#include <grids/LayeredSpheroidGrid/vector_calculus.hpp>

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
    "octahedron" is a simple 3d grid for testing raster operations that require 
    something comparable to a unit sphere (e.g. nearest neighbor lookups using SpheroidVoronoi)
    */
    LayeredSpheroidGrid octahedron = 
        LayeredSpheroidGrid(meshes::octahedron.vertices, meshes::octahedron.faces, 1.f, 2u);

    floats a = floats({1,2,3,4,5,6,
                       1,1,2,3,5,8});

    std::cout << to_string(octahedron, a) << std::endl;

    vec2s v2d = vec2s({
        vec2(-1,-1),
        vec2(-1, 0),
        vec2(-1, 1),
        vec2( 1,-1),
        vec2( 1, 0),
        vec2( 1, 1),

        vec2( 1,-1),
        vec2( 1, 0),
        vec2( 1, 1),
        vec2(-1,-1),
        vec2(-1, 0),
        vec2(-1, 1),
    });
    std::cout << to_string(octahedron, v2d) << std::endl;

    vec3s v3d = vec3s({
        vec3(-1,-1,-1),
        vec3( 0,-1,-1),
        vec3( 1,-1,-1),
        vec3(-1, 0,-1),
        vec3( 0, 0,-1),
        vec3( 1, 0,-1),

        vec3(-1,-1,-1),
        vec3( 0,-1,-1),
        vec3( 1,-1,-1),
        vec3(-1,-1, 0),
        vec3( 0,-1, 0),
        vec3( 1,-1, 0),
    });
    std::cout << to_string(octahedron, divergence(octahedron, v3d)) << std::endl;

    floats b = floats({2,1,1,1,1,1,
                       1,2,1,1,1,1});
    std::cout << to_string(octahedron, gradient(octahedron, b)) << std::endl;

    // floats raster_c = floats(icosphere_mesh.vertices.size());
    // random(icosphere, generator, raster_c);
    // std::string str_raster_c = to_string(icosphere, raster_c);
    // std::cout << str_raster_c << std::endl;

    // floats gradient_in = raster_c;
    // vec3s gradient_out = vec3s(icosphere_mesh.vertices.size());
    // std::cout << "calculating gradient" << std::endl;
    // rasters::gradient(icosphere, gradient_in, gradient_out);
    // std::cout << rasters::to_string(icosphere, gradient_out) << std::endl;

}