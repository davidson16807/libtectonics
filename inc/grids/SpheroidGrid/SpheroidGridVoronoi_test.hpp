
// 3rd party libraries
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch/catch.hpp"

#define GLM_FORCE_PURE      // disable anonymous structs so we can build with ISO C++
#include <glm/vec3.hpp>             // *vec3

// in-house libraries
#include <many/many.hpp>  
#include <many/convenience.hpp>  
#include <many/glm/glm.hpp>         // *vec*s
#include <many/glm/random.hpp>      // get_elias_noise
#include <many/glm/convenience.hpp> //  operators, etc.

#include <meshes/mesh.hpp>
#include <grids/Grid/morphologic.hpp>  
#include <grids/Grid/vector_calculus.hpp>
#include <grids/SpheroidGrid/string_cast.hpp>  

using namespace glm;
using namespace many;
using namespace rasters;

SpheroidGridVoronoi voronoi(
        normalize(vec3s({
                        vec3( 1, 0, 0),
                        vec3( 0, 1, 0),
                        vec3( 0, 0, 1),
                        vec3(-1, 0, 0),
                        vec3( 0,-1, 0),
                        vec3( 0, 0,-1),
                        vec3(-1,-1,-1),
                        vec3( 1,-1,-1),
                        vec3(-1, 1,-1),
                        vec3( 1, 1,-1),
                        vec3(-1,-1, 1),
                        vec3( 1,-1, 1),
                        vec3(-1, 1, 1),
                        vec3( 1, 1, 1),
                        vec3( 1, 1, 1)
                    })),
        1./100.,
        10./100.
    );
TEST_CASE( "SpheroidGridVoronoi.get_value() purity", "[rasters]" ) {
    SECTION("SpheroidGridVoronoi.get_value() must be called repeatedly without changing the output"){
        CHECK(voronoi.get_value(vec3(1,0,0)) == voronoi.get_value(vec3(1,0,0)));
    }
}
TEST_CASE( "SpheroidGridVoronoi.get_value() happy path", "[rasters]" ) {
    SECTION("SpheroidGridVoronoi.get_value() must return the appropriate id when answer is obvious"){
        CHECK(  voronoi.get_value(normalize(vec3( 1, 0, 0))) == 0  );
        CHECK(  voronoi.get_value(normalize(vec3( 0, 1, 0))) == 1  );
        CHECK(  voronoi.get_value(normalize(vec3( 0, 0, 1))) == 2  );
        CHECK(  voronoi.get_value(normalize(vec3(-1, 0, 0))) == 3  );
        CHECK(  voronoi.get_value(normalize(vec3( 0,-1, 0))) == 4  );
        CHECK(  voronoi.get_value(normalize(vec3( 0, 0,-1))) == 5  );
        CHECK(  voronoi.get_value(normalize(vec3(-1,-1,-1))) == 6  );
        CHECK(  voronoi.get_value(normalize(vec3( 1,-1,-1))) == 7  );
        CHECK(  voronoi.get_value(normalize(vec3(-1, 1,-1))) == 8  );
        CHECK(  voronoi.get_value(normalize(vec3( 1, 1,-1))) == 9  );
        CHECK(  voronoi.get_value(normalize(vec3(-1,-1, 1))) == 10 );
        CHECK(  voronoi.get_value(normalize(vec3( 1,-1, 1))) == 11 );
        CHECK(  voronoi.get_value(normalize(vec3(-1, 1, 1))) == 12 );
        CHECK(  voronoi.get_value(normalize(vec3( 1, 1, 1))) == 13 );
    }
}