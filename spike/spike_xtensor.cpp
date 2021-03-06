

#define GLM_FORCE_PURE  // disable anonymous structs so we can build with ISO C++
#include <glm/vec3.hpp> // *vec3

#include <xtensor/xarray.hpp>
#include <iostream>

int main(int argc, char const *argv[])
{
	auto a = xt::xarray<glm::vec3> { glm::vec3(1,2,3) };
	auto b = xt::xarray<glm::vec3> { glm::vec3(1,1,3) };
	auto c = a + b;
	std::cout << c[0].x << " " << c[0].y << " " << c[0].z << std::endl;
}
