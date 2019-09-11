#pragma once

#include <cmath>

#include "types.hpp"

/*
"convenience.hpp" contains functions that pass output as return values rather than using using output parameters
This provides convenience at the expense of performance, since now we have to call constructors for the new objects. 
See https://codeyarns.com/2010/10/21/c-return-value-versus-output-parameter/ for more info.
It is important to keep these functions separate from the rest of the library for two reasons:
 1.) It encourages good practice, since you have to explicitly opt-in to less performant convenience functions.
 2.) It provides a nice itemization of functions that will have to be created if you subclass tmany<T> (as we do within the rasters library)
*/

namespace many
{
	template <class T>
	tmany<T> get(const tmany<T>& a, const tmany<unsigned int>& ids)
	{
		tmany<T> out(ids.size());
		get(a, ids, out);
		return out;
	}
	template <class T>
	tmany<T> copy(const tmany<T>& a )
	{
		return tmany<T>(a);
	}
	

	template <class T1, typename F>
	inline tmany<T1> transform(const tmany<T1>& a, F f)
	{
		tmany<T1> out = tmany<T1>(a.size());
		transform(a, f, out); 
		return out;
	}


	template <class T1, class T2, typename F>
	inline tmany<T1> transform(const tmany<T1>& a, const tmany<T2>& b, F f)
	{
		tmany<T1> out = tmany<T1>(a.size());
		transform(a, b, f, out); 
		return out;
	}
	template <class T1, class T2, typename F>
	inline tmany<T1> transform(const tmany<T1>& a, const T2 b, F f)
	{
		tmany<T1> out = tmany<T1>(a.size());
		transform(a, b, f, out); 
		return out;
	}
	template <class T1, class T2, typename F>
	inline tmany<T1> transform(const T1 a, const tmany<T2>& b, F f)
	{
		tmany<T1> out = tmany<T1>(b.size());
		transform(a, b, f, out); 
		return out;
	}




	template <class T1, class T2, class T3, typename F>
	inline tmany<T1> transform(const tmany<T1>& a, const tmany<T2>& b, const tmany<T3>& c, F f)
	{
		tmany<T1> out = tmany<T1>(a.size());
		transform(a, b, c, f, out); 
		return out;
	}
	template <class T1, class T2, class T3, typename F>
	inline tmany<T1> transform(const tmany<T1>& a, const tmany<T2>& b, const T3 c, F f)
	{
		tmany<T1> out = tmany<T1>(a.size());
		transform(a, b, c, f, out); 
		return out;
	}
	template <class T1, class T2, class T3, typename F>
	inline tmany<T1> transform(const tmany<T1>& a, const T2 b, const tmany<T3>& c, F f)
	{
		tmany<T1> out = tmany<T1>(a.size());
		transform(a, b, c, f, out); 
		return out;
	}
	template <class T1, class T2, class T3, typename F>
	inline tmany<T1> transform(const tmany<T1>& a, const T2 b, const T3 c, F f)
	{
		tmany<T1> out = tmany<T1>(a.size());
		transform(a, b, c, f, out); 
		return out;
	}
	template <class T1, class T2, class T3, typename F>
	inline tmany<T1> transform(const T1 a, const tmany<T2>& b, const tmany<T3>& c, F f)
	{
		tmany<T1> out = tmany<T1>(b.size());
		transform(a, b, c, f, out); 
		return out;
	}
	template <class T1, class T2, class T3, typename F>
	inline tmany<T1> transform(const T1 a, const tmany<T2>& b, const T3 c, F f)
	{
		tmany<T1> out = tmany<T1>(b.size());
		transform(a, b, c, f, out); 
		return out;
	}
	template <class T1, class T2, class T3, typename F>
	inline tmany<T1> transform(const T1 a, const T2 b, const tmany<T3>& c, F f)
	{
		tmany<T1> out = tmany<T1>(c.size());
		transform(a, b, c, f, out); 
		return out;
	}





	template<class T, typename Taggregator>
	tmany<T> aggregate(const tmany<T>& a, const tmany<unsigned int>& group_ids, Taggregator aggregator)
	{
		tmany<T> group_out = tmany<T>(max(group_ids));
		for (unsigned int i = 0; i < group_ids.size(); ++i)
		{
			group_out[group_ids[i]] = aggregator(group_out[group_ids[i]], a[i]);
		}
		return group_out;
	}

	template<class T, typename Taggregator>
	tmany<T> aggregate(const tmany<unsigned int>& group_ids, Taggregator aggregator)
	{
		tmany<T> group_out = tmany<T>(max(group_ids));
		for (unsigned int i = 0; i < group_ids.size(); ++i)
		{
			group_out[group_ids[i]] = aggregator(group_out[group_ids[i]]);
		}
		return group_out;
	}


	/// Returns x if x >= 0; otherwise, it returns -x.
	template <class T>
	tmany<T> abs(const tmany<T>& a)
	{
		return transform(a, [](T ai){ return ai >= 0? ai : -ai; });
	}

	/// Returns 1.0 if x > 0, 0.0 if x == 0, or -1.0 if x < 0.
	template <class T>
	tmany<T> sign(const tmany<T>& a)
	{
		return transform(a, [](T ai){ return (T(0) < ai) - (ai < T(0)); });
	}

	/// Returns a value equal to the nearest integer that is less then or equal to x.
	template <class T>
	tmany<T> floor(const tmany<T>& a)
	{
		return transform(a, std::floor);
	}

	/// Returns a value equal to the nearest integer to x
	/// whose absolute value is not larger than the absolute value of x.
	template <class T>
	tmany<T> trunc(const tmany<T>& a)
	{
		return transform(a, std::trunc);
	}

	/// Returns a value equal to the nearest integer to x.
	/// The fraction 0.5 will round in a direction chosen by the
	/// implementation, presumably the direction that is fastest.
	/// This includes the possibility that round(x) returns the
	/// same value as roundEven(x) for all values of x.
	template <class T>
	tmany<T> round(const tmany<T>& a)
	{
		return transform(a, std::round);
	}

	/// Returns a value equal to the nearest integer
	/// that is greater than or equal to x.
	template <class T>
	tmany<T> ceil(const tmany<T>& a)
	{
		transform(a, std::ceil);
	}



	template <class T>
	std::ostream &operator<<(std::ostream &os, const tmany<T>& a) { 
		os << "[";
		for (unsigned int i = 0; i < a.size(); ++i)
		{
		    os << a[i] << " ";
		}
		os << "]";
		return os;
	}


	// NOTE: all operators are suggested to be inline because they are thin wrappers of functions
	template <class T>
	inline bool operator==(const tmany<T>& a, const T b)
	{
		return equal(a, b);
	}
	template <class T>
	inline bool operator!=(const tmany<T>& a, const T b)
	{
		return notEqual(a, b);
	}
	template <class T>
	inline bool operator==(const T a, const tmany<T>& b)
	{
		return equal(a, b);
	}
	template <class T>
	inline bool operator!=(const T a, const tmany<T>& b)
	{
		return notEqual(a, b);
	}
	template <class T>
	inline bool operator==(const tmany<T>& a, const tmany<T>& b)
	{
		return equal(a, b);
	}
	template <class T>
	inline bool operator!=(const tmany<T>& a, const tmany<T>& b)
	{
		return notEqual(a, b);
	}
	

	template <class T, class T2, class T3>
	inline tmany<T3> operator>(const tmany<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai > bi; });
	}
	template <class T, class T2, class T3>
	inline tmany<T3> operator>=(const tmany<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai >= bi; });
	}
	template <class T, class T2, class T3>
	inline tmany<T3> operator<(const tmany<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai < bi; });
	}
	template <class T, class T2, class T3>
	inline tmany<T3> operator<=(const tmany<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai <= bi; });
	}
	
	// NOTE: all wrappers are suggested to be inline because they are thin wrappers of functions

	template <class T, class T2, class T3>
	inline tmany<T3> operator>(const T2 a, const tmany<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai > bi; });
	}
	template <class T, class T2, class T3>
	inline tmany<T3> operator>=(const T2 a, const tmany<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai >= bi; });
	}
	template <class T, class T2, class T3>
	inline tmany<T3> operator<(const T2 a, const tmany<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai < bi; });
	}
	template <class T, class T2, class T3>
	inline tmany<T3> operator<=(const T2 a, const tmany<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai <= bi; });
	}





	template <class T>
	inline tmany<T>& operator+=(tmany<T>& a, const T b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] += b;
		}
		return a;
	}
	template <class T>
	inline tmany<T>& operator-=(tmany<T>& a, const T b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] -= b;
		}
		return a;
	}
	template <class T>
	inline tmany<T>& operator*=(tmany<T>& a, const T b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] *= b;
		}
		return a;
	}
	template <class T>
	inline tmany<T>& operator/=(tmany<T>& a, const T b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] /= b;
		}
		return a;
	}


	template <class T, class T2>
	inline tmany<T>& operator+=(tmany<T>& a, const tmany<T2>& b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] += b[i];
		}
		return a;
	}
	template <class T, class T2>
	inline tmany<T>& operator-=(tmany<T>& a, const tmany<T2>& b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] -= b[i];
		}
		return a;
	}
	template <class T, class T2>
	inline tmany<T>& operator*=(tmany<T>& a, const tmany<T2>& b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] *= b[i];
		}
		return a;
	}
	template <class T, class T2>
	inline tmany<T>& operator/=(tmany<T>& a, const tmany<T2>& b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] /= b[i];
		}
		return a;
	}

	// NOTE: prefix increment/decrement
	template <class T>
	inline tmany<T>& operator++(tmany<T>& a)  
	{  
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i]++;
		}
		return a;
	}  
	template <class T>
	inline tmany<T>& operator--(tmany<T>& a)  
	{  
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i]--;
		}
		return a;
	}  

	// NOTE: postfix increment/decrement
	template <class T>
	inline tmany<T> operator++(tmany<T>& a, int)  
	{  
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i]++;
		}
		return a;
	}  
	template <class T>
	inline tmany<T> operator--(tmany<T>& a, int)  
	{  
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i]--;
		}
		return a;
	}  
	




	// NOTE: we define operators for multiple classes T and T2 in order to support 
	//  vector/scalar multiplication, matrix/vect multiplication, etc.
	template <class T, class T2>
	inline tmany<T> operator+(const tmany<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai + bi; });
	}
	template <class T, class T2>
	inline tmany<T> operator-(const tmany<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai - bi; });
	}
	template <class T, class T2>
	inline tmany<T> operator*(const tmany<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai * bi; });
	}
	template <class T, class T2>
	inline tmany<T> operator/(const tmany<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai / bi; });
	}
	




	// NOTE: we define operators for multiple classes T and T2 in order to support 
	//  vector/scalar multiplication, matrix/vect multiplication, etc.
	template <class T, class T2>
	inline tmany<T> operator+(const T2 a, const tmany<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai + bi; });
	}
	template <class T, class T2>
	inline tmany<T> operator-(const T2 a, const tmany<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai - bi; });
	}
	template <class T, class T2>
	inline tmany<T> operator*(const T2 a, const tmany<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai * bi; });
	}
	template <class T, class T2>
	inline tmany<T> operator/(const T2 a, const tmany<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai / bi; });
	}


	// NOTE: we define operators for multiple classes T and T2 in order to support 
	//  vector/scalar multiplication, matrix/vect multiplication, etc.
	template <class T, class T2>
	inline tmany<T> operator+(const tmany<T>& a, const tmany<T2>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai + bi; });
	}
	template <class T, class T2>
	inline tmany<T> operator-(const tmany<T>& a, const tmany<T2>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai - bi; });
	}
	template <class T, class T2>
	inline tmany<T> operator*(const tmany<T>& a, const tmany<T2>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai * bi; });
	}
	template <class T, class T2>
	inline tmany<T> operator/(const tmany<T>& a, const tmany<T2>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai / bi; });
	}


	inline tmany<bool> operator~(const tmany<bool>& a)
	{
		tmany<bool> out = tmany<bool>(a.size());
		transform(a, [](bool ai){ return !ai; }, out);
		return out;
	}


	inline tmany<bool> operator|(const tmany<bool>& a, const bool b)
	{
		return transform(a, b, [](bool ai, bool bi){ return ai || bi; });
	}
	inline tmany<bool> operator&(const tmany<bool>& a, const bool b)
	{
		return transform(a, b, [](bool ai, bool bi){ return ai && bi; });
	}

	inline tmany<bool> operator|(const tmany<bool>& a, const tmany<bool>& b)
	{
		return transform(a, b, [](bool ai, bool bi){ return ai || bi; });
	}
	inline tmany<bool> operator&(const tmany<bool>& a, const tmany<bool>& b)
	{
		return transform(a, b, [](bool ai, bool bi){ return ai && bi; });
	}




	inline tmany<bool>& operator|=(tmany<bool>& a, const bool b){
		transform(a, b, [](bool ai, bool bi){ return ai || bi; }, a);
		return a;
	}
	inline tmany<bool>& operator&=(tmany<bool>& a, const bool b){
		transform(a, b, [](bool ai, bool bi){ return ai &&  bi; }, a);
		return a;
	}

	inline tmany<bool>& operator|=(tmany<bool>& a, const tmany<bool>& b){
		transform(a, b, [](bool ai, bool bi){ return ai || bi; }, a);
		return a;
	}
	inline tmany<bool>& operator&=(tmany<bool>& a, const tmany<bool>& b){
		transform(a, b, [](bool ai, bool bi){ return ai &&  bi; }, a);
		return a;
	}
}