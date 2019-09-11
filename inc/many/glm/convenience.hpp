#pragma once

#include <cmath>

#include "../types.hpp"
#include "../convenience.hpp"

/*
"convenience.hpp" contains functions that pass output as return values rather than using output parameters
This provides convenience at the expense of performance, since now we have to call constructors for the new objects. 
See https://codeyarns.com/2010/10/21/c-return-value-versus-output-parameter/ for more info.
It is important to keep these functions separate from the rest of the library for two reasons:
 1.) It encourages good practice, since you have to explicitly opt-in to less performant convenience functions.
 2.) It provides a nice itemization of functions that will have to be created if you subclass tmany<T> (as we do within the rasters library)
*/

namespace many
{
	// NOTE: Here we have convenience functions that are stand-ins for operators
	//  we do this because there are no operators that can express them succinctly

	// NOTE: all operators and convenience functions are marked inline,
	//  because they are thin wrappers of static functions



	template <glm::length_t L, class T, glm::qualifier Q>
	inline tmany<T> get_x(const tmany<glm::vec<L,T,Q>>& a)
	{
		return transform(a, [](glm::vec<L,T,Q> ai){ return ai.x; });
	}

	template <glm::length_t L, class T, glm::qualifier Q>
	inline tmany<T> get_y(const tmany<glm::vec<L,T,Q>>& a)
	{
		return transform(a, [](glm::vec<L,T,Q> ai){ return ai.y; });
	}

	template <glm::length_t L, class T, glm::qualifier Q>
	inline tmany<T> get_z(const tmany<glm::vec<L,T,Q>>& a)
	{
		return transform(a, [](glm::vec<L,T,Q> ai){ return ai.z; });
	}

	
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline tmany<T> dot (const tmany<glm::vec<L,T,Q>>& u, const glm::vec<L,T,Q> v ) 
	{
		tmany<T> out = tmany<T>(u.size());
		dot(u, v, out);
		return out;
	}
	template<typename T, glm::qualifier Q>
	inline tmany<glm::vec<3,T,Q>> cross (const tmany<glm::vec<3,T,Q>>& u, const glm::vec<3,T,Q> v ) 
	{
		tmany<glm::vec<3,T,Q>> out = tmany<glm::vec<3,T,Q>>(u.size());
		cross(u, v, out);
		return out;
	}
	template<typename T, glm::qualifier Q>
	inline tmany<float> cross (const tmany<glm::vec<2,T,Q>>& u, const glm::vec<2,T,Q> v ) 
	{
		tmany<float> out = tmany<float>(u.size());
		cross(u, v, out);
		return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline tmany<T> distance(const tmany<glm::vec<L,T,Q>>& u, const glm::vec<L,T,Q> v ) 
	{
		tmany<T> out = tmany<T>(u.size());
		distance(u, v, out);
		return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline tmany<T> dot (const tmany<glm::vec<L,T,Q>>& u, const tmany<glm::vec<L,T,Q>>& v ) 
	{
		tmany<T> out = tmany<T>(u.size());
		dot(u, v, out);
		return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline tmany<glm::vec<L,T,Q>> cross (const tmany<glm::vec<L,T,Q>>& u, const tmany<glm::vec<L,T,Q>>& v ) 
	{
		tmany<glm::vec<L,T,Q>> out = tmany<glm::vec<L,T,Q>>(u.size());
		cross(u, v, out);
		return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline tmany<T> distance(const tmany<glm::vec<L,T,Q>>& u, const tmany<glm::vec<L,T,Q>>& v ) 
	{
		tmany<T> out = tmany<T>(u.size());
		distance(u, v, out);
		return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline tmany<glm::vec<L,T,Q>> normalize(const tmany<glm::vec<L,T,Q>>& u) 
	{
		tmany<glm::vec<L,T,Q>> out = tmany<glm::vec<L,T,Q>>(u.size());
		normalize(u, out);
		return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline tmany<T> length(const tmany<glm::vec<L,T,Q>>& u) 
	{
		tmany<T> out = tmany<T>(u.size());
		length(u, out);
		return out;
	}



	template<glm::length_t L, typename T, glm::qualifier Q>
	std::ostream &operator<< (std::ostream &out, const glm::vec<L,T,Q> &vec) {
	    out << "[" 
	        << vec.x << "," << vec.y << ","<< vec.z 
	        << "]";

	    return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	std::ostream &operator<<(std::ostream &os, const tmany<glm::vec<L,T,Q>>& a) { 
		os << "[";
		for (unsigned int i = 0; i < a.size(); ++i)
		{
		    os << a[i] << " ";
		}
		os << "]";
		return os;
	}





	template<glm::length_t L, typename T, glm::qualifier Q>
	inline tmany<glm::vec<L,T,Q>>& operator+=(tmany<glm::vec<L,T,Q>>& a, const T b) 
	{
		add(a, b, a);
		return a;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline tmany<glm::vec<L,T,Q>>& operator-=(tmany<glm::vec<L,T,Q>>& a, const T b) 
	{
		sub(a, b, a);
		return a;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline tmany<glm::vec<L,T,Q>>& operator*=(tmany<glm::vec<L,T,Q>>& a, const T b) 
	{
		mult(a, b, a);
		return a;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	inline tmany<glm::vec<L,T,Q>>& operator/=(tmany<glm::vec<L,T,Q>>& a, const T b) 
	{
		div(a, b, a);
		return a;
	}
} // end namespace