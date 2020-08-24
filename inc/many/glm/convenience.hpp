#pragma once

#include <cmath>

#include "../types.hpp"
#include "../convenience.hpp"
#include "geometric.hpp"

/*
"convenience.hpp" contains functions that pass output as return values rather than using output parameters
This provides convenience at the expense of performance, since now we have to call constructors for the new objects. 
See https://codeyarns.com/2010/10/21/c-return-value-versus-output-parameter/ for more info.
It is important to keep these functions separate from the rest of the library for two reasons:
 1.) It encourages good practice, since you have to explicitly opt-in to less performant convenience functions.
 2.) It provides a nice itemization of functions that will have to be created if you subclass series<T> (as we do within the rasters library)
*/

namespace many
{
	// NOTE: Here we have convenience functions that are stand-ins for operators
	//  we do this because there are no operators that can express them succinctly

	// NOTE: all operators and convenience functions are marked inline,
	//  because they are thin wrappers of static functions



	template <glm::length_t L, typename T, glm::qualifier Q>
	inline series<T> get_x(const series<glm::vec<L,T,Q>>& a)
	{
		series<T> out(a.size());
		out.store([](glm::vec<L,T,Q> ai){ return ai.x; }, a);
		return out;
	}

	template <glm::length_t L, typename T, glm::qualifier Q>
	inline series<T> get_y(const series<glm::vec<L,T,Q>>& a)
	{
		series<T> out(a.size());
		out.store([](glm::vec<L,T,Q> ai){ return ai.y; }, a);
		return out;
	}

	template <glm::length_t L, typename T, glm::qualifier Q>
	inline series<T> get_z(const series<glm::vec<L,T,Q>>& a)
	{
		series<T> out(a.size());
		out.store([](glm::vec<L,T,Q> ai){ return ai.z; }, a);
		return out;
	}

	
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline series<T> dot (const series<glm::vec<L,T,Q>>& u, const glm::vec<L,T,Q> v ) 
	{
		series<T> out(u.size());
		many::dot(u, v, out);
		return out;
	}
	template<typename T, glm::qualifier Q>
	inline series<glm::vec<3,T,Q>> cross (const series<glm::vec<3,T,Q>>& u, const glm::vec<3,T,Q> v ) 
	{
		series<glm::vec<3,T,Q>> out(u.size());
		many::cross(u, v, out);
		return out;
	}
	template<typename T, glm::qualifier Q>
	inline series<float> cross (const series<glm::vec<2,T,Q>>& u, const glm::vec<2,T,Q> v ) 
	{
		series<float> out(u.size());
		many::cross(u, v, out);
		return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline series<T> distance(const series<glm::vec<L,T,Q>>& u, const glm::vec<L,T,Q> v ) 
	{
		series<T> out(u.size());
		many::distance(u, v, out);
		return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline series<T> dot (const series<glm::vec<L,T,Q>>& u, const series<glm::vec<L,T,Q>>& v ) 
	{
		series<T> out(u.size());
		many::dot(u, v, out);
		return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline series<glm::vec<L,T,Q>> cross (const series<glm::vec<L,T,Q>>& u, const series<glm::vec<L,T,Q>>& v ) 
	{
		series<glm::vec<L,T,Q>> out(u.size());
		many::cross(u, v, out);
		return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline series<T> distance(const series<glm::vec<L,T,Q>>& u, const series<glm::vec<L,T,Q>>& v ) 
	{
		series<T> out(u.size());
		many::distance(u, v, out);
		return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline series<glm::vec<L,T,Q>> normalize(const series<glm::vec<L,T,Q>>& u) 
	{
		series<glm::vec<L,T,Q>> out(u.size());
		many::normalize(u, out);
		return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline series<T> length(const series<glm::vec<L,T,Q>>& u) 
	{
		series<T> out(u.size());
		many::length(u, out);
		return out;
	}

} // end namespace