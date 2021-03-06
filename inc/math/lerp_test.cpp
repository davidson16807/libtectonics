
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/catch.hpp>

#include "lerp.hpp"

const float a = 1.6180;
const float b = 3.1415;
const float c = 1.6807;
const float f = 0.25;

TEST_CASE( "mix purity", "[math]" ) {
    SECTION("calling mix() multiple times returns the same result"){
		CHECK(math::mix(a,b,f) == math::mix(a,b,f));
	}
}

TEST_CASE( "mix identity", "[math]" ) {
    SECTION("calling mix(a,b,0) produces results equivalent to input, a"){
		CHECK(math::mix(a,b,0.0f) == a);
	}
}

TEST_CASE( "mix distributivity over multiplication", "[math]" ) {
    SECTION("calling c*mix(a,b,f) is equivalent to mix(c*a,c*b,f)"){
		CHECK(c*math::mix(a,b,f) == Approx(math::mix(c*a,c*b,f)).margin(0.01));
	}
}



TEST_CASE( "linearstep purity", "[math]" ) {
    SECTION("calling linearstep() multiple times returns the same result"){
		CHECK(math::linearstep(a,b,c) == math::linearstep(a,b,c));
	}
}

TEST_CASE( "linearstep spatial invariance", "[math]" ) {
    SECTION("calling linearstep(a,b,c) is equivalent to linearstep(f+a,f+b,f+c)"){
		CHECK(math::linearstep(a,b,c) == math::linearstep(f+a,f+b,f+c));
	}
}

TEST_CASE( "mix/linearstep invertibility", "[math]" ) {
    SECTION("calling mix(a,b,linearstep(a,b,c)) will reproduce the value for c for any value a<c<b"){
		CHECK(math::mix(a,b,math::linearstep(a,b,c)) == Approx(c).margin(0.01));
	}
    SECTION("calling linearstep(a,b,mix(a,b,f)) will reproduce the value for f for any value 0<f<1"){
		CHECK(math::linearstep(a,b,math::mix(a,b,f)) == Approx(f).margin(0.01));
	}
}



TEST_CASE( "lerp purity", "[math]" ) {
  	const auto xs = std::array<float,2>{0.0f,1.0f};
  	const auto ys = std::array<float,2>{a,b};
    SECTION("calling lerp multiple times returns the same result"){
		CHECK(math::lerp(xs,ys,f) == math::lerp(xs,ys,f));
	}
}

TEST_CASE( "lerp degeneracy to mix", "[math]" ) {
  	const auto xs = std::array<float,2>{0.0f,1.0f};
  	const auto ys = std::array<float,2>{a,b};
    SECTION("calling lerp({0,1}, {a,b}, f) is equivalent to mix(a,b,f)"){
		CHECK(math::lerp(xs,ys,f) == Approx(math::mix(a,b,f)).margin(0.01));
	}
}

TEST_CASE( "lerp degeneracy to constant", "[math]" ) {
  	const auto xs = std::array<float,1>{0.0f};
  	const auto ys = std::array<float,1>{a};
    SECTION("calling lerp with a single control point is equivalent to a constant"){
		CHECK(math::lerp(xs,ys,f) == Approx(a).margin(0.01));
	}
}

TEST_CASE( "integral_of_lerp purity", "[math]" ) {
  	std::mt19937 generator(2);
  	std::uniform_real_distribution<float> uniform(0.0f, 2.0f);
  	const auto xs = std::array<float,4>{ -0.5f, 0.75f, 1.0f, 1.5f };
  	const auto ys = std::array<float,4>{ uniform(generator), uniform(generator), uniform(generator), uniform(generator) };
    SECTION("calling lerp multiple times returns the same result"){
		CHECK(math::integral_of_lerp(xs,ys,0.0f,1.6807f) == math::integral_of_lerp(xs,ys,0.0f,1.6807f));
	}
}

TEST_CASE( "integral_of_lerp equivalence to numerical integration", "[math]" ) {
  	std::mt19937 generator(2);
  	std::uniform_real_distribution<float> uniform(0.0f, 2.0f);
  	const auto xs = std::array<float,4>{ -0.5f, 0.75f, 1.0f, 1.5f };
  	const auto ys = std::array<float,4>{ uniform(generator), uniform(generator), uniform(generator), uniform(generator) };
	const float dx = 0.003f;
	for (float x0 = -0.6; x0 <= 1.6f; x0+=0.2)
	{
		for (float x1 = x0; x1 <= 1.6f; x1+=0.2)
		{
			float I1 = 0.0f;
			for (float xi = x0; xi < x1; xi+=dx)
			{
				I1 += dx * math::lerp(xs,ys,xi);
			}
			float I2 = math::integral_of_lerp(xs,ys,x0,x1);
			// std::cout << std::abs(I1 - I2) << " " << x0 << " " << x1 << " " << I1 << " " << I2 << std::endl;
    		SECTION("calling integral_of_lerp is equivalent to result from numerical integration"){
				CHECK(I1 == Approx(I2).margin(0.01));
			}
		}	
	}
}

TEST_CASE( "integral_of_lerp degeneracy to linear function", "[math]" ) {
  	const auto xs = std::array<float,1>{ -0.5f };
  	const auto ys = std::array<float,1>{ a };
	const float dx = 0.003f;
	for (float x0 = -0.6; x0 <= 1.6f; x0+=0.2)
	{
		for (float x1 = x0; x1 <= 1.6f; x1+=0.2)
		{
			float I1 = 0.0f;
			for (float xi = x0; xi < x1; xi+=dx)
			{
				I1 += dx * math::lerp(xs,ys,xi);
			}
			float I2 = math::integral_of_lerp(xs,ys,x0,x1);
			// std::cout << std::abs(I1 - I2) << " " << x0 << " " << x1 << " " << I1 << " " << I2 << std::endl;
    		SECTION("calling integral_of_lerp with a single control point is equivalent to result from linear function"){
				CHECK(I1 == Approx(I2).margin(0.01));
			}
		}	
	}
}