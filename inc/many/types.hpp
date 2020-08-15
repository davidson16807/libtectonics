#pragma once

// C libraries
#include <cmath>     /* assert */
#include <assert.h>     /* assert */

// std libraries
#include <initializer_list>	// initializer_list
#include <iterator>			// std::distance
#include <vector>			// std::distance

namespace many
{
	// This template represents a statically-sized contiguous block of heap memory occupied by primitive data of the same arbitrary type
	// See README.md for more details
	template <class T>
	class series
	{
	protected:
		std::vector<T> values;

	public:

		virtual ~series()
		{
		}

		// initializer list constructor
		series(std::initializer_list<T> list) : values(list.begin(), list.end())
		{
		}
		// std container style constructor
		template<class TIterator>
		series(TIterator first, TIterator last) : values(std::distance(first, last))
		{
			unsigned int id = 0;
			while (first!=last) 
			{
				this->values[id] = *first;
				++first;
				++id;
			}
		}

		// copy constructor
		series(const series<T>& a)  : values(a.values) {}

		// convenience constructor for vectors
		explicit series(std::vector<T> vector) : values(vector)
		{
		}

		explicit series(const unsigned int N) : values(N) {}

		explicit series(const unsigned int N, const T a)  : values(N, a) {}

		template <class T2>
		explicit series(const series<T2>& a)  : values(a.size())
		{
			for (unsigned int i = 0; i < a.size(); ++i)
			{
				values[i] = a[i];
			}
		}

		inline unsigned int size() const
		{
			return values.size();
		}

		inline std::vector<T>& vector()
		{
			return values;
		}

	    inline typename std::vector<T>::const_iterator begin() const { return values.begin(); }
	    inline typename std::vector<T>::const_iterator end()   const { return values.end();   }

	    inline typename std::vector<T>::iterator begin() { return values.begin(); }
	    inline typename std::vector<T>::iterator end()   { return values.end();   }

		// NOTE: all operators should to be inline because they are thin wrappers of functions
		inline typename std::vector<T>::const_reference operator[](const unsigned int id ) const
		{
		   return values.operator[](id);
		}
		inline typename std::vector<T>::reference operator[](const unsigned int id )
		{
		   return values[id]; // reference return 
		}
	
		inline series<T> operator[](const series<bool>& mask )
		{
			series<T> out = series<T>(mask.size());
			get(*this, mask, out);
			return out;
		}
		inline series<T> operator[](const series<unsigned int>& ids )
		{
			series<T> out = series<T>(ids.size());
			get(*this, ids, out);
			return out;
		}

		inline series<T>& operator=(const series<T>& other )
		{
			values.resize(other.size());
			copy(*this, other);
			return *this;
		}
		inline series<T>& operator=(const T& other )
		{
			values.resize(other.size());
			fill(*this, other);
			return *this;
		}
	};


	template <class T>
	inline T get(const series<T>& a, const unsigned int id )
	{
		return a[id];
	}
	template <class T>
	void get(const series<T>& a, const series<unsigned int>& ids, series<T>& out )
	{
		assert(ids.size() == out.size());
		for (unsigned int i = 0; i < ids.size(); ++i)
		{
			assert(0 <= ids[i]);
			assert(ids[i] < a.size());
			assert(!std::isinf(ids[i]));
			assert(!std::isnan(ids[i]));
			out[i] = a[ids[i]];
		}
	}
	template <class T>
	void get(const series<T>& a, const series<bool>& mask, series<T>& out )
	{
		assert(a.size()  == mask.size());
		int out_i = 0;
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			if (mask[i])
			{
				out[out_i] = a[i];
				out_i++;
			}
		}
	}

	template <class T>
	void fill(series<T>& out, const T a )
	{
		for (unsigned int i = 0; i < out.size(); ++i)
		{
			out[i] = a;
		}
	}
	template <class T>
	void fill(series<T>& out, const series<unsigned int>& ids, const T a )
	{
		for (unsigned int i = 0; i < ids.size(); ++i)
		{
			
			assert(0 <= ids[i]);
			assert(ids[i] < a.size());
			assert(!std::isinf(ids[i]));
			assert(!std::isnan(ids[i]));
			out[ids[i]] = a;
		}
	}
	template <class T>
	void fill(series<T>& out, const series<bool>& mask, const T a )
	{
		assert(out.size() == mask.size());
		for (unsigned int i = 0; i < out.size(); ++i)
		{
			out[i] = mask[i]? a : out[i];
		}
	}

	template<class T, class TIterator>
	void copy_iterators(series<T>& out, TIterator first, TIterator last)
	{
		unsigned int id = 0;
		while (first!=last) 
		{
			out[id] = *first;
			++first;
			++id;
		}
	}
	template <class T>
	void copy(series<T>& out, const series<T>& a )
	{
		for (unsigned int i = 0; i < out.size(); ++i)
		{
			out[i] = a[i];
		}
	}
	template <class T>
	inline void copy(series<T>& out, const unsigned int id, const series<T>& a )
	{
		out[id] = a[id];
	}
	template <class T>
	void copy(series<T>& out, const series<unsigned int>& ids, const series<T>& a )
	{
		assert(ids.size() == a.size());
		for (unsigned int i = 0; i < ids.size(); ++i)
		{
			
			assert(0 <= ids[i]);
			assert(ids[i] < a.size());
			assert(!std::isinf(ids[i]));
			assert(!std::isnan(ids[i]));
			out[ids[i]] = a[ids[i]];
		}
	}
	template <class T>
	void copy(series<T>& out, const series<bool>& mask, const series<T>& a )
	{
		assert(out.size() == mask.size());
		assert(out.size() == a.size());
		for (unsigned int i = 0; i < out.size(); ++i)
		{
			out[i] = mask[i]? a[i] : out[i];
		}
	}


	template <class T>
	inline void set(series<T>& out, const unsigned int id, const T a )
	{
		out[id] = a;
	}
	template <class T>
	void set(series<T>& out, const series<unsigned int>& ids, const series<T>& a )
	{
		assert(ids.size() == a.size());
		for (unsigned int i = 0; i < ids.size(); ++i)
		{
			
			assert(0 <= ids[i]);
			assert(ids[i] < a.size());
			assert(!std::isinf(ids[i]));
			assert(!std::isnan(ids[i]));
			out[ids[i]] = a[i];
		}
	}






	
	// UNARY TRANSFORM
	template <class T1, class Tout, typename F>
	inline void transform(const series<T1>& a, F f, series<Tout>& out)
	{
		assert(a.size() == out.size());
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out[i] = f(a[i]);
		}
	}
	template <class T1, class Tout, typename F>
	inline void transform(const T1 a, F f, series<Tout>& out)
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out[i] = f(a);
		}
	}




	// BINARY TRANSFORM
	template <class T1, class T2, class Tout, typename F>
	inline void transform(const series<T1>& a, const series<T2>& b, F f, series<Tout>& out)
	{
		assert(a.size() == out.size());
		assert(a.size() >= b.size());
		assert(a.size() % b.size() == 0);
		uint N = a.size() / b.size();
		for (unsigned int i = 0; i < b.size(); ++i)
		{
			for (unsigned int j = 0; j < N; ++j)
			{
				out[N*i+j] = f(a[N*i+j], b[i]);
			}
		}
	}
	template <class T1, class T2, class Tout, typename F>
	inline void transform(const series<T1>& a, const T2 b, F f, series<Tout>& out)
	{
		assert(a.size() == out.size());
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out[i] = f(a[i], b);
		}
	}
	template <class T1, class T2, class Tout, typename F>
	inline void transform(const T1 a, const series<T2>& b, F f, series<Tout>& out)
	{
		assert(b.size() == out.size());
		for (unsigned int i = 0; i < b.size(); ++i)
		{
			out[i] = f(a, b[i]);
		}
	}











	// TRINARY TRANSFORM
	template <class T1, class T2, class T3, class Tout, typename F>
	inline void transform(const series<T1>& a, const series<T2>& b, const series<T3>& c, F f, series<Tout>& out)
	{
		assert(a.size() == out.size());
		assert(b.size() == out.size());
		assert(c.size() == out.size());
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out[i] = f(a[i], b[i], c[i]);
		}
	}
	template <class T1, class T2, class T3, class Tout, typename F>
	inline void transform(const series<T1>& a, const series<T2>& b, const T3 c, F f, series<Tout>& out)
	{
		assert(a.size() == out.size());
		assert(b.size() == out.size());
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out[i] = f(a[i], b[i], c);
		}
	}
	template <class T1, class T2, class T3, class Tout, typename F>
	inline void transform(const series<T1>& a, const T2 b, const series<T3>& c, F f, series<Tout>& out)
	{
		assert(a.size() == out.size());
		assert(c.size() == out.size());
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out[i] = f(a[i], b, c[i]);
		}
	}
	template <class T1, class T2, class T3, class Tout, typename F>
	inline void transform(const series<T1>& a, const T2 b, const T3 c, F f, series<Tout>& out)
	{
		assert(a.size() == out.size());
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out[i] = f(a[i], b, c);
		}
	}
	template <class T1, class T2, class T3, class Tout, typename F>
	inline void transform(const T1 a, const series<T2>& b, const series<T3>& c, F f, series<Tout>& out)
	{
		assert(b.size() == out.size());
		assert(c.size() == out.size());
		for (unsigned int i = 0; i < b.size(); ++i)
		{
			out[i] = f(a, b[i], c[i]);
		}
	}
	template <class T1, class T2, class T3, class Tout, typename F>
	inline void transform(const T1 a, const series<T2>& b, const T3 c, F f, series<Tout>& out)
	{
		assert(b.size() == out.size());
		for (unsigned int i = 0; i < b.size(); ++i)
		{
			out[i] = f(a, b[i], c);
		}
	}
	template <class T1, class T2, class T3, class Tout, typename F>
	inline void transform(const T1 a, const T2 b, const series<T3>& c, F f, series<Tout>& out)
	{
		assert(c.size() == out.size());
		for (unsigned int i = 0; i < c.size(); ++i)
		{
			out[i] = f(a, b, c[i]);
		}
	}



	template<class T, typename Taggregator>
	void aggregate_into(const series<T>& a, const series<unsigned int>& group_ids, Taggregator aggregator, series<T>& group_out)
	{
		assert(a.size() == group_ids.size());
		for (unsigned int i = 0; i < group_ids.size(); ++i)
		{
			assert(0 <= group_ids[i]);
			assert(group_ids[i] < group_out.size());
			assert(!std::isinf(group_ids[i]));
			assert(!std::isnan(group_ids[i]));
			group_out[group_ids[i]] = aggregator(group_out[group_ids[i]], a[i]);
		}
	}

	template<class T, typename Taggregator>
	void aggregate_into(const series<unsigned int>& group_ids, Taggregator aggregator, series<T>& group_out)
	{
		for (unsigned int i = 0; i < group_ids.size(); ++i)
		{
			assert(0 <= group_ids[i] && group_ids[i] < group_out.size() && !std::isinf(group_ids[i]) && !std::isnan(group_ids[i]));
			group_out[group_ids[i]] = aggregator(group_out[group_ids[i]]);
		}
	}


















	// NOTE: all wrappers are suggested to be inline because they are thin wrappers of functions



	typedef series<bool>	        bools;
	typedef series<int>	        ints;
	typedef series<unsigned int> uints;
	typedef series<float>	    floats;
	typedef series<double>       doubles;
}
