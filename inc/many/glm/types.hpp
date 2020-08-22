#pragma once
#include <assert.h>     /* assert */

#include "../types.hpp"

namespace many
{
	template <glm::length_t L, typename T, glm::qualifier Q>
	void get_x(const series<glm::vec<L,T,Q>>& a, series<T>& output )
	{
		transform(a, [](glm::vec<L,T,Q> ai){ return ai.x; }, output);
	}
	template <glm::length_t L, typename T, glm::qualifier Q>
	void get_y(const series<glm::vec<L,T,Q>>& a, series<T>& output )
	{
		transform(a, [](glm::vec<L,T,Q> ai){ return ai.y; }, output);
	}
	template <glm::length_t L, typename T, glm::qualifier Q>
	void get_z(const series<glm::vec<L,T,Q>>& a, series<T>& output )
	{
		transform(a, [](glm::vec<L,T,Q> ai){ return ai.z; }, output);
	}



	// old method signatures: don't use these, and get rid of them when you have the time
	template <glm::length_t L, typename T, glm::qualifier Q>
	void set_x(series<glm::vec<L,T,Q>>& output, const series<T>& a )
	{
		for (unsigned int i = 0; i < output.size(); ++i)
		{
			output[i].x = a[i];
		}
	}
	template <glm::length_t L, typename T, glm::qualifier Q>
	void set_y(series<glm::vec<L,T,Q>>& output, const series<T>& a )
	{
		for (unsigned int i = 0; i < output.size(); ++i)
		{
			output[i].y = a[i];
		}
	}
	template <glm::length_t L, typename T, glm::qualifier Q>
	void set_z(series<glm::vec<L,T,Q>>& output, const series<T>& a )
	{
		for (unsigned int i = 0; i < output.size(); ++i)
		{
			output[i].z = a[i];
		}
	}

	// better, overloaded method signatures: equivalent performance, but more versatile, 
	// and fits within the definition of a regular function (as defined by Stepanov)
	template <glm::length_t L, typename T, glm::qualifier Q>
	void set_x(const series<glm::vec<L,T,Q>>& a, const series<T>& values, series<glm::vec<L,T,Q>>& output )
	{
		if (&a != &output){ many::copy(output, a); }
		for (unsigned int i = 0; i < output.size(); ++i)
		{
			output[i].x = values[i];
		}
	}
	template <glm::length_t L, typename T, glm::qualifier Q>
	void set_y(const series<glm::vec<L,T,Q>>& a, const series<T>& values, series<glm::vec<L,T,Q>>& output )
	{
		if (&a != &output){ many::copy(output, a); }
		for (unsigned int i = 0; i < output.size(); ++i)
		{
			output[i].y = values[i];
		}
	}
	template <glm::length_t L, typename T, glm::qualifier Q>
	void set_z(const series<glm::vec<L,T,Q>>& a, const series<T>& values, series<glm::vec<L,T,Q>>& output )
	{
		if (&a != &output){ many::copy(output, a); }
		for (unsigned int i = 0; i < output.size(); ++i)
		{
			output[i].z = values[i];
		}
	}


	// Converts from vec3s to flattened floats
	template <glm::length_t L, typename T, glm::qualifier Q>
	void flatten (series<glm::vec<L,T,Q>>& a, series<T>& output) {
		assert(a.size()*L == output.size());
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			output[3*i+0] = a[i].x;
			output[3*i+1] = a[i].y;
			output[3*i+2] = a[i].z;
		}
	}
	// Converts from flattened floats to vec3s
	template <glm::length_t L, typename T, glm::qualifier Q>
	void unflatten (series<T>& a, series<glm::vec<L,T,Q>>& output) {
		assert(output.size()*L == a.size());
	    for (unsigned int i = 0; i < output.size(); ++i)
		{
			output[i].x = a[3*i+0];
			output[i].y = a[3*i+1];
			output[i].z = a[3*i+2];
		}
	}

	
	


	typedef series<glm::vec<1, bool, glm::defaultp>>	bvec1s;
	typedef series<glm::vec<2, bool, glm::defaultp>>	bvec2s;
	typedef series<glm::vec<3, bool, glm::defaultp>>	bvec3s;
	typedef series<glm::vec<4, bool, glm::defaultp>>	bvec4s;

	typedef series<glm::vec<1, int, glm::defaultp>> ivec1s;
	typedef series<glm::vec<2, int, glm::defaultp>> ivec2s;
	typedef series<glm::vec<3, int, glm::defaultp>> ivec3s;
	typedef series<glm::vec<4, int, glm::defaultp>> ivec4s;

	typedef series<glm::vec<1, unsigned int, glm::defaultp>> uvec1s;
	typedef series<glm::vec<2, unsigned int, glm::defaultp>> uvec2s;
	typedef series<glm::vec<3, unsigned int, glm::defaultp>> uvec3s;
	typedef series<glm::vec<4, unsigned int, glm::defaultp>> uvec4s;

	typedef series<glm::vec<1, double, glm::defaultp>> dvec1s;
	typedef series<glm::vec<2, double, glm::defaultp>> dvec2s;
	typedef series<glm::vec<3, double, glm::defaultp>> dvec3s;
	typedef series<glm::vec<4, double, glm::defaultp>> dvec4s;

	typedef series<glm::vec<1, float, glm::defaultp>> vec1s;
	typedef series<glm::vec<2, float, glm::defaultp>> vec2s;
	typedef series<glm::vec<3, float, glm::defaultp>> vec3s;
	typedef series<glm::vec<4, float, glm::defaultp>> vec4s;



	
	

	typedef series<glm::mat<2,2, double, glm::defaultp>> dmat2s;
	typedef series<glm::mat<2,2, double, glm::defaultp>> dmat2x2s;
	typedef series<glm::mat<2,3, double, glm::defaultp>> dmat2x3s;
	typedef series<glm::mat<2,4, double, glm::defaultp>> dmat2x4s;

	typedef series<glm::mat<3,3, double, glm::defaultp>> dmat3s;
	typedef series<glm::mat<3,2, double, glm::defaultp>> dmat3x2s;
	typedef series<glm::mat<3,3, double, glm::defaultp>> dmat3x3s;
	typedef series<glm::mat<3,4, double, glm::defaultp>> dmat3x4s;

	typedef series<glm::mat<4,4, double, glm::defaultp>> dmat4s;
	typedef series<glm::mat<4,2, double, glm::defaultp>> dmat4x2s;
	typedef series<glm::mat<4,3, double, glm::defaultp>> dmat4x3s;
	typedef series<glm::mat<4,4, double, glm::defaultp>> dmat4x4s;
	
	

	typedef series<glm::mat<2,2, float, glm::defaultp>> mat2s;
	typedef series<glm::mat<2,2, float, glm::defaultp>> mat2x2s;
	typedef series<glm::mat<2,3, float, glm::defaultp>> mat2x3s;
	typedef series<glm::mat<2,4, float, glm::defaultp>> mat2x4s;

	typedef series<glm::mat<3,3, float, glm::defaultp>> mat3s;
	typedef series<glm::mat<3,2, float, glm::defaultp>> mat3x2s;
	typedef series<glm::mat<3,3, float, glm::defaultp>> mat3x3s;
	typedef series<glm::mat<3,4, float, glm::defaultp>> mat3x4s;

	typedef series<glm::mat<4,4, float, glm::defaultp>> mat4s;
	typedef series<glm::mat<4,2, float, glm::defaultp>> mat4x2s;
	typedef series<glm::mat<4,3, float, glm::defaultp>> mat4x3s;
	typedef series<glm::mat<4,4, float, glm::defaultp>> mat4x4s;
	
}
