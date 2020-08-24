#pragma once

#include "types.hpp"
#include "morphologic.hpp"

namespace many
{

	const float MANY_EPSILON = 1e-4;

	template <typename T>
	bool equal(const series<T>& a, const T b, T threshold = T(MANY_EPSILON))
	{
		bool out(true);
		T diff(0);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			diff = a[i] - b;
			out &= diff*diff <= threshold;
		}
		return out;
	}
	template <typename T>
	bool notEqual(const series<T>& a, const T b, T threshold = T(MANY_EPSILON))
	{
		bool out(false);
		T diff(0);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			diff = a[i] - b;
			out |= diff*diff > threshold;
		}
		return out;
	}
	template <typename T>
	bool equal(const series<T>& a, const series<T>& b, T threshold = T(MANY_EPSILON))
	{
		if (a.size() != b.size())
		{
			return false;
		}
		bool out(true);
		T diff(0);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			diff = a[i] - b[i];
			out &= diff*diff <= threshold;
		}
		return out;
	}
	template <typename T>
	bool notEqual(const series<T>& a, const series<T>& b, T threshold = T(MANY_EPSILON))
	{
		if (a.size() != b.size())
		{
			return true;
		}
		bool out(false);
		T diff(0);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			diff = a[i] - b[i];
			out |= diff*diff > threshold;
		}
		return out;
	}



	template <typename T>
	void equal(const series<T>& a, const T b, series<bool>& out, T threshold = T(MANY_EPSILON))
	{
		T diff(0);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			diff = a[i] - b;
			out[i] = diff*diff <= threshold;
		}
	}
	template <typename T>
	void notEqual(const series<T>& a, const T b, series<bool>& out, T threshold = T(MANY_EPSILON))
	{
		T diff(0);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			diff = a[i] - b;
			out[i] = diff*diff > threshold;
		}
	}
	template <typename T>
	void equal(const series<T>& a, const series<T>& b, series<bool>& out, T threshold = T(MANY_EPSILON))
	{
		T diff(0);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			diff = a[i] - b[i];
			out[i] = diff*diff <= threshold;
		}
	}
	template <typename T>
	void notEqual(const series<T>& a, const series<T>& b, series<bool>& out, T threshold = T(MANY_EPSILON))
	{
		T diff(0);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			diff = a[i] - b[i];
			out[i] = diff*diff > threshold;
		}
	}






	bool equal(const series<bool>& a, const bool b)
	{
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= a[i] == b;
		}
		return out;
	}
	bool notEqual(const series<bool>& a, const bool b)
	{
		bool out(false);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i] != b;
		}
		return out;
	}
	bool equal(const series<bool>& a, const series<bool>& b)
	{
		if (a.size() != b.size())
		{
			return false;
		}
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= a[i] == b[i];
		}
		return out;
	}
	bool notEqual(const series<bool>& a, const series<bool>& b)
	{
		if (a.size() != b.size())
		{
			return true;
		}
		bool out(false);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i] != b[i];
		}
		return out;
	}



	void equal(const series<bool>& a, const bool b, series<bool>& out)
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out[i] = a[i] == b;
		}
	}
	void notEqual(const series<bool>& a, const bool b, series<bool>& out)
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out[i] = a[i] != b;
		}
	}
	void equal(const series<bool>& a, const series<bool>& b, series<bool>& out)
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out[i] = a[i] == b[i];
		}
	}
	void notEqual(const series<bool>& a, const series<bool>& b, series<bool>& out)
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out[i] = a[i] != b[i];
		}
	}






	bool equal(const series<int>& a, const int b)
	{
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= a[i] == b;
		}
		return out;
	}
	bool notEqual(const series<int>& a, const int b)
	{
		bool out(false);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i] != b;
		}
		return out;
	}
	bool equal(const series<int>& a, const series<int>& b)
	{
		if (a.size() != b.size())
		{
			return false;
		}
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= a[i] == b[i];
		}
		return out;
	}
	bool notEqual(const series<int>& a, const series<int>& b)
	{
		if (a.size() != b.size())
		{
			return true;
		}
		bool out(false);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i] != b[i];
		}
		return out;
	}



	void equal(const series<int>& a, const int b, series<bool>& out)
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out[i] = a[i] == b;
		}
	}
	void notEqual(const series<int>& a, const int b, series<bool>& out)
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out[i] = a[i] != b;
		}
	}
	void equal(const series<int>& a, const series<int>& b, series<bool>& out)
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out[i] = a[i] == b[i];
		}
	}
	void notEqual(const series<int>& a, const series<int>& b, series<bool>& out)
	{
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out[i] = a[i] != b[i];
		}
	}






	bool equal(const series<unsigned int>& a, const unsigned int b)
	{
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= a[i] == b;
		}
		return out;
	}
	bool notEqual(const series<unsigned int>& a, const unsigned int b)
	{
		bool out(false);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i] != b;
		}
		return out;
	}
	bool equal(const series<unsigned int>& a, const series<unsigned int>& b)
	{
		if (a.size() != b.size())
		{
			return false;
		}
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= a[i] == b[i];
		}
		return out;
	}
	bool notEqual(const series<unsigned int>& a, const series<unsigned int>& b)
	{
		if (a.size() != b.size())
		{
			return true;
		}
		bool out(false);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i] != b[i];
		}
		return out;
	}



	void equal(const series<unsigned int>& a, const unsigned int b, series<bool>& out)
	{
		out.store([](unsigned int ai, unsigned int bi){ return ai == bi; }, a, b);
	}
	void notEqual(const series<unsigned int>& a, const unsigned int b, series<bool>& out)
	{
		out.store([](unsigned int ai, unsigned int bi){ return ai != bi; }, a, b);
	}
	void equal(const series<unsigned int>& a, const series<unsigned int>& b, series<bool>& out)
	{
		out.store([](unsigned int ai, unsigned int bi){ return ai == bi; }, a, b);
	}
	void notEqual(const series<unsigned int>& a, const series<unsigned int>& b, series<bool>& out)
	{
		out.store([](unsigned int ai, unsigned int bi){ return ai != bi; }, a, b);
	}





	template <typename T, typename T2, std::enable_if_t<!std::is_base_of<AbstractSeries, T2>::value, int> = 0>
	void greaterThan(const series<T>& a, const T2 b, series<bool>& out)
	{
		out.store([](T ai, T2 bi){ return ai > bi; }, a, b); 
	}
	template <typename T, typename T2, std::enable_if_t<!std::is_base_of<AbstractSeries, T2>::value, int> = 0>
	void greaterThanEqual(const series<T>& a, const T2 b, series<bool>& out)
	{
		out.store([](T ai, T2 bi){ return ai >= bi; }, a, b); 
	}
	template <typename T, typename T2, std::enable_if_t<!std::is_base_of<AbstractSeries, T2>::value, int> = 0>
	void lessThan(const series<T>& a, const T2 b, series<bool>& out)
	{
		out.store([](T ai, T2 bi){ return ai < bi; }, a, b); 
	}
	template <typename T, typename T2, std::enable_if_t<!std::is_base_of<AbstractSeries, T2>::value, int> = 0>
	void lessThanEqual(const series<T>& a, const T2 b, series<bool>& out)
	{
		out.store([](T ai, T2 bi){ return ai <= bi; }, a, b); 
	}



	template <typename T, typename T2>
	void greaterThan(const series<T>& a, const series<T2>& b, series<bool>& out)
	{
		out.store([](T ai, T2 bi){ return ai > bi; }, a, b); 
	}
	template <typename T, typename T2>
	void greaterThanEqual(const series<T>& a, const series<T2>& b, series<bool>& out)
	{
		out.store([](T ai, T2 bi){ return ai >= bi; }, a, b); 
	}
	template <typename T, typename T2>
	void lessThan(const series<T>& a, const series<T2>& b, series<bool>& out)
	{
		out.store([](T ai, T2 bi){ return ai <= bi; }, a, b); 
	}
	template <typename T, typename T2>
	void lessThanEqual(const series<T>& a, const series<T2>& b, series<bool>& out)
	{
		out.store([](T ai, T2 bi){ return ai < bi; }, a, b); 
	}

	
	bool all(const series<bool>& a)
	{
		bool out = true;
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= a[i];
		}
		return out;
	}
	bool any(const series<bool>& a)
	{
		bool out = false;
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i];
		}
		return out;
	}
	bool none(const series<bool>& a)
	{
		bool out = false;
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i];
		}
		return !out;
	}

}
