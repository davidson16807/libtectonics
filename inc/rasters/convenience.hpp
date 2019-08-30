#pragma once

#include <cmath>

#include "types.hpp"

/*
"convenience.hpp" contains functions that pass output as return values rather than using using output parameters
This provides convenience at the expense of performance, since now we have to call constructors for the new objects. 
See https://codeyarns.com/2010/10/21/c-return-value-versus-output-parameter/ for more info.
It is important to keep these functions separate from the rest of the library for two reasons:
 1.) It encourages good practice, since you have to explicitly opt-in to less performant convenience functions.
 2.) It provides a nice itemization of functions that will have to be created if you subclass traster<T> (as we do within the rasters library)
*/

namespace many
{
	template <class T>
	traster<T> get(const traster<T>& a, const traster<unsigned int>& ids)
	{
		traster<T> out(ids.size());
		get(a, ids, out);
		return out;
	}
	template <class T>
	traster<T> copy(const traster<T>& a )
	{
		return traster<T>(a);
	}
	

	template <class T1, typename F>
	inline traster<T1> transform(const traster<T1>& a, F f)
	{
		traster<T1> out = traster<T1>(a.size());
		transform(a, f, out); 
		return out;
	}


	template <class T1, class T2, typename F>
	inline traster<T1> transform(const traster<T1>& a, const traster<T2>& b, F f)
	{
		traster<T1> out = traster<T1>(a.size());
		transform(a, b, f, out); 
		return out;
	}
	template <class T1, class T2, typename F>
	inline traster<T1> transform(const traster<T1>& a, const T2 b, F f)
	{
		traster<T1> out = traster<T1>(a.size());
		transform(a, b, f, out); 
		return out;
	}
	template <class T1, class T2, typename F>
	inline traster<T1> transform(const T1 a, const traster<T2>& b, F f)
	{
		traster<T1> out = traster<T1>(b.size());
		transform(a, b, f, out); 
		return out;
	}




	template <class T1, class T2, class T3, typename F>
	inline traster<T1> transform(const traster<T1>& a, const traster<T2>& b, const traster<T3>& c, F f)
	{
		traster<T1> out = traster<T1>(a.size());
		transform(a, b, c, f, out); 
		return out;
	}
	template <class T1, class T2, class T3, typename F>
	inline traster<T1> transform(const traster<T1>& a, const traster<T2>& b, const T3 c, F f)
	{
		traster<T1> out = traster<T1>(a.size());
		transform(a, b, c, f, out); 
		return out;
	}
	template <class T1, class T2, class T3, typename F>
	inline traster<T1> transform(const traster<T1>& a, const T2 b, const traster<T3>& c, F f)
	{
		traster<T1> out = traster<T1>(a.size());
		transform(a, b, c, f, out); 
		return out;
	}
	template <class T1, class T2, class T3, typename F>
	inline traster<T1> transform(const traster<T1>& a, const T2 b, const T3 c, F f)
	{
		traster<T1> out = traster<T1>(a.size());
		transform(a, b, c, f, out); 
		return out;
	}
	template <class T1, class T2, class T3, typename F>
	inline traster<T1> transform(const T1 a, const traster<T2>& b, const traster<T3>& c, F f)
	{
		traster<T1> out = traster<T1>(b.size());
		transform(a, b, c, f, out); 
		return out;
	}
	template <class T1, class T2, class T3, typename F>
	inline traster<T1> transform(const T1 a, const traster<T2>& b, const T3 c, F f)
	{
		traster<T1> out = traster<T1>(b.size());
		transform(a, b, c, f, out); 
		return out;
	}
	template <class T1, class T2, class T3, typename F>
	inline traster<T1> transform(const T1 a, const T2 b, const traster<T3>& c, F f)
	{
		traster<T1> out = traster<T1>(c.size());
		transform(a, b, c, f, out); 
		return out;
	}





	template<class T, typename Taggregator>
	traster<T> aggregate(const traster<T>& a, const traster<unsigned int>& group_ids, Taggregator aggregator)
	{
		traster<T> group_out = traster<T>(max(group_ids));
		for (unsigned int i = 0; i < group_ids.size(); ++i)
		{
			group_out[group_ids[i]] = aggregator(group_out[group_ids[i]], a[i]);
		}
		return group_out;
	}

	template<class T, typename Taggregator>
	traster<T> aggregate(const traster<unsigned int>& group_ids, Taggregator aggregator)
	{
		traster<T> group_out = traster<T>(max(group_ids));
		for (unsigned int i = 0; i < group_ids.size(); ++i)
		{
			group_out[group_ids[i]] = aggregator(group_out[group_ids[i]]);
		}
		return group_out;
	}




	template <class T>
	std::ostream &operator<<(std::ostream &os, const traster<T>& a) { 
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
	inline bool operator==(const traster<T>& a, const T b)
	{
		return equal(a, b);
	}
	template <class T>
	inline bool operator!=(const traster<T>& a, const T b)
	{
		return notEqual(a, b);
	}
	template <class T>
	inline bool operator==(const T a, const traster<T>& b)
	{
		return equal(a, b);
	}
	template <class T>
	inline bool operator!=(const T a, const traster<T>& b)
	{
		return notEqual(a, b);
	}
	template <class T>
	inline bool operator==(const traster<T>& a, const traster<T>& b)
	{
		return equal(a, b);
	}
	template <class T>
	inline bool operator!=(const traster<T>& a, const traster<T>& b)
	{
		return notEqual(a, b);
	}
	

	template <class T, class T2, class T3>
	inline traster<T3> operator>(const traster<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai > bi; });
	}
	template <class T, class T2, class T3>
	inline traster<T3> operator>=(const traster<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai >= bi; });
	}
	template <class T, class T2, class T3>
	inline traster<T3> operator<(const traster<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai < bi; });
	}
	template <class T, class T2, class T3>
	inline traster<T3> operator<=(const traster<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai <= bi; });
	}
	
	// NOTE: all wrappers are suggested to be inline because they are thin wrappers of functions

	template <class T, class T2, class T3>
	inline traster<T3> operator>(const T2 a, const traster<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai > bi; });
	}
	template <class T, class T2, class T3>
	inline traster<T3> operator>=(const T2 a, const traster<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai >= bi; });
	}
	template <class T, class T2, class T3>
	inline traster<T3> operator<(const T2 a, const traster<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai < bi; });
	}
	template <class T, class T2, class T3>
	inline traster<T3> operator<=(const T2 a, const traster<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai <= bi; });
	}





	template <class T>
	inline traster<T>& operator+=(traster<T>& a, const T b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] += b;
		}
		return a;
	}
	template <class T>
	inline traster<T>& operator-=(traster<T>& a, const T b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] -= b;
		}
		return a;
	}
	template <class T>
	inline traster<T>& operator*=(traster<T>& a, const T b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] *= b;
		}
		return a;
	}
	template <class T>
	inline traster<T>& operator/=(traster<T>& a, const T b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] /= b;
		}
		return a;
	}


	template <class T, class T2>
	inline traster<T>& operator+=(traster<T>& a, const traster<T2>& b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] += b[i];
		}
		return a;
	}
	template <class T, class T2>
	inline traster<T>& operator-=(traster<T>& a, const traster<T2>& b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] -= b[i];
		}
		return a;
	}
	template <class T, class T2>
	inline traster<T>& operator*=(traster<T>& a, const traster<T2>& b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] *= b[i];
		}
		return a;
	}
	template <class T, class T2>
	inline traster<T>& operator/=(traster<T>& a, const traster<T2>& b) 
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i] /= b[i];
		}
		return a;
	}

	// NOTE: prefix increment/decrement
	template <class T>
	inline traster<T>& operator++(traster<T>& a)  
	{  
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i]++;
		}
		return a;
	}  
	template <class T>
	inline traster<T>& operator--(traster<T>& a)  
	{  
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i]--;
		}
		return a;
	}  

	// NOTE: postfix increment/decrement
	template <class T>
	inline traster<T> operator++(traster<T>& a, int)  
	{  
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a[i]++;
		}
		return a;
	}  
	template <class T>
	inline traster<T> operator--(traster<T>& a, int)  
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
	inline traster<T> operator+(const traster<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai + bi; });
	}
	template <class T, class T2>
	inline traster<T> operator-(const traster<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai - bi; });
	}
	template <class T, class T2>
	inline traster<T> operator*(const traster<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai * bi; });
	}
	template <class T, class T2>
	inline traster<T> operator/(const traster<T>& a, const T2 b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai / bi; });
	}
	




	// NOTE: we define operators for multiple classes T and T2 in order to support 
	//  vector/scalar multiplication, matrix/vect multiplication, etc.
	template <class T, class T2>
	inline traster<T> operator+(const T2 a, const traster<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai + bi; });
	}
	template <class T, class T2>
	inline traster<T> operator-(const T2 a, const traster<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai - bi; });
	}
	template <class T, class T2>
	inline traster<T> operator*(const T2 a, const traster<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai * bi; });
	}
	template <class T, class T2>
	inline traster<T> operator/(const T2 a, const traster<T>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai / bi; });
	}


	// NOTE: we define operators for multiple classes T and T2 in order to support 
	//  vector/scalar multiplication, matrix/vect multiplication, etc.
	template <class T, class T2>
	inline traster<T> operator+(const traster<T>& a, const traster<T2>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai + bi; });
	}
	template <class T, class T2>
	inline traster<T> operator-(const traster<T>& a, const traster<T2>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai - bi; });
	}
	template <class T, class T2>
	inline traster<T> operator*(const traster<T>& a, const traster<T2>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai * bi; });
	}
	template <class T, class T2>
	inline traster<T> operator/(const traster<T>& a, const traster<T2>& b)
	{
		return transform(a, b, [](T ai, T2 bi){ return ai / bi; });
	}


	inline traster<bool> operator~(const traster<bool>& a)
	{
		traster<bool> out = traster<bool>(a.size());
		transform(a, [](bool ai){ return !ai; }, out);
		return out;
	}


	inline traster<bool> operator|(const traster<bool>& a, const bool b)
	{
		return transform(a, b, [](bool ai, bool bi){ return ai || bi; });
	}
	inline traster<bool> operator&(const traster<bool>& a, const bool b)
	{
		return transform(a, b, [](bool ai, bool bi){ return ai && bi; });
	}

	inline traster<bool> operator|(const traster<bool>& a, const traster<bool>& b)
	{
		return transform(a, b, [](bool ai, bool bi){ return ai || bi; });
	}
	inline traster<bool> operator&(const traster<bool>& a, const traster<bool>& b)
	{
		return transform(a, b, [](bool ai, bool bi){ return ai && bi; });
	}




	inline traster<bool>& operator|=(traster<bool>& a, const bool b){
		transform(a, b, [](bool ai, bool bi){ return ai || bi; }, a);
		return a;
	}
	inline traster<bool>& operator&=(traster<bool>& a, const bool b){
		transform(a, b, [](bool ai, bool bi){ return ai &&  bi; }, a);
		return a;
	}

	inline traster<bool>& operator|=(traster<bool>& a, const traster<bool>& b){
		transform(a, b, [](bool ai, bool bi){ return ai || bi; }, a);
		return a;
	}
	inline traster<bool>& operator&=(traster<bool>& a, const traster<bool>& b){
		transform(a, b, [](bool ai, bool bi){ return ai &&  bi; }, a);
		return a;
	}
}