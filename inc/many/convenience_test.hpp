
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/catch.hpp>

#include <many/many.hpp>  
#include <many/convenience.hpp>  

using namespace many;


TEST_CASE( "many<T> arithmetic consistency", "[many]" ) {
    floats a1 = floats({1,2,3,4,5});
    floats a2 = floats({1,2,3,4,5});
    floats a3 = floats({1,2,3,4,5});
    floats b = floats({-1,1,-2,2,3});

    SECTION("a+=b, a=a+b, and add(a,b,a) must all work the same"){
        a1 += b;
        a2 = a2+b;
        add(a3,b,a3);
        
        CHECK(a1 == a2);
        CHECK(a2 == a3);
    }

    SECTION("a*=b, a=a*b, and add(a,b,a) must all work the same"){
        a1 *= b;
        a2 = a2*b;
        mult(a3,b,a3);
        
        CHECK(a1 == a2);
        CHECK(a2 == a3);
    }

    SECTION("a-=b, a=a-b, and add(a,b,a) must all work the same"){
        a1 -= b;
        a2 = a2-b;
        sub(a3,b,a3);
        
        CHECK(a1 == a2);
        CHECK(a2 == a3);
    }

    SECTION("a/=b, a=a/b, and add(a,b,a) must all work the same"){
        a1 /= b;
        a2 = a2/b;
        div(a3,b,a3);
        
        CHECK(a1 == a2);
        CHECK(a2 == a3);
    }
}

