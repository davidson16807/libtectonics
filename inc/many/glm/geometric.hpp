#pragma once

#include <cmath>    	    // isnan

#include <glm/geometric.hpp>// all the GLSL geometry functions: dot, cross, reflect, etc.

#include "../types.hpp"

namespace many
{

	template<typename T, glm::qualifier Q>
	float cross(const glm::vec<2,T,Q>& a, const glm::vec<2,T,Q>& b)
	{
		return a.x*b.y - b.x*a.y;
	}





	template<glm::length_t L, typename T, glm::qualifier Q>
	void dot (const series<glm::vec<L,T,Q>>& u, const glm::vec<L,T,Q> v, series<T>& out) {
		for (unsigned int i = 0; i < u.size(); ++i)
		{
			out[i] = dot(u[i], v);
		}
	}
	template<typename T, glm::qualifier Q>
	void cross (const series<glm::vec<3,T,Q>>& u, const glm::vec<3,T,Q> v, series<glm::vec<3,T,Q>>& out) 
	{
		for (unsigned int i = 0; i < u.size(); ++i)
		{
			out[i] = cross(u[i], v);
		}
	}
	template<typename T, glm::qualifier Q>
	void cross (const series<glm::vec<2,T,Q>>& u, const glm::vec<2,T,Q> v, series<float>& out) 
	{
		for (unsigned int i = 0; i < u.size(); ++i)
		{
			out[i] = cross(u[i], v);
		}
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	void mult (const series<glm::vec<L,T,Q>>& u, const glm::vec<L,T,Q> v, series<glm::vec<L,T,Q>>& out) {
		for (unsigned int i = 0; i < u.size(); ++i)
		{
			out[i] = u[i] * v;
		}
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	void distance(const series<glm::vec<L,T,Q>>& u, const glm::vec<L,T,Q> v, series<T>& out) 
	{
		for (unsigned int i = 0; i < u.size(); ++i)
		{
			out[i] = distance(u[i], v);
		}
	}


	template<glm::length_t L, typename T, glm::qualifier Q>
	void dot (const series<glm::vec<L,T,Q>>& u, const series<glm::vec<L,T,Q>>& v, series<T>& out) 
	{
		for (unsigned int i = 0; i < u.size(); ++i)
		{
			out[i] = dot(u[i], v[i]);
		}
	}
	template<typename T, glm::qualifier Q>
	void cross (const series<glm::vec<3,T,Q>>& u, const series<glm::vec<3,T,Q>>& v, series<glm::vec<3,T,Q>>& out) 
	{
		for (unsigned int i = 0; i < u.size(); ++i)
		{
			out[i] = cross(u[i], v[i]);
		}
	}
	template<typename T, glm::qualifier Q>
	void cross (const series<glm::vec<2,T,Q>>& u, const series<glm::vec<2,T,Q>>& v, series<float>& out) 
	{
		for (unsigned int i = 0; i < u.size(); ++i)
		{
			out[i] = cross(u[i], v[i]);
		}
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	void mult (const series<glm::vec<L,T,Q>>& u, const series<glm::vec<L,T,Q>>& v, series<glm::vec<L,T,Q>>& out) 
	{
		for (unsigned int i = 0; i < u.size(); ++i)
		{
			out[i] = u[i] * v[i];
		}
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	void distance(const series<glm::vec<L,T,Q>>& u, const series<glm::vec<L,T,Q>>& v, series<T>& out) 
	{
		for (unsigned int i = 0; i < u.size(); ++i)
		{
			out[i] = distance(u[i], v[i]);
		}
	}


	template<glm::length_t L, typename T, glm::qualifier Q>
	void length(const series<glm::vec<L,T,Q>>& u, series<T>& out) 
	{
		for (unsigned int i = 0; i < u.size(); ++i)
		{
			out[i] = length(u[i]);
		}
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	void normalize(const series<glm::vec<L,T,Q>>& u, series<glm::vec<L,T,Q>>& out) 
	{
		float u_length(0);
		for (unsigned int i = 0; i < u.size(); ++i)
		{
			u_length = length(u[i]);
			out[i] = u[i] / (u_length < T(1e-5)? T(1) : u_length);
		}
	}


}
