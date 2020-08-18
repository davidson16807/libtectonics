#pragma once

#include <glm/geometric.hpp>
#include <glm/vector_relational.hpp>

#include "../types.hpp"
#include "../relational.hpp"

namespace many
{






	template <glm::length_t L, class T, glm::qualifier Q>
	bool equal(const series<glm::vec<L,T,Q>>& a, const series<glm::vec<L,T,Q>>& b, T cosine_threshold, T length_threshold)
	{
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= glm::dot(glm::normalize(a[i]),glm::normalize(b[i])) > cosine_threshold && !(glm::length(b[i])/glm::length(a[i]) < length_threshold || glm::length(a[i])/glm::length(b[i]) < length_threshold);
		}
		return out;
	}
	template <glm::length_t L, class T, glm::qualifier Q>
	bool equal(const series<glm::vec<L,T,Q>>& a, const glm::vec<L,T,Q> b, T cosine_threshold, T length_threshold)
	{
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= glm::dot(glm::normalize(a[i]),glm::normalize(b)) > cosine_threshold && !(glm::length(b)/glm::length(a[i]) < length_threshold || glm::length(a[i])/glm::length(b) < length_threshold);
		}
		return out;
	}

	template<glm::length_t L, glm::qualifier Q>
	bool equal(const series<glm::vec<L,unsigned int,Q>>& a, const glm::vec<L,unsigned int,Q> b)
	{
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= a[i] - b == glm::vec<L,unsigned int, Q>(0);
		}
		return out;
	}
	template<glm::length_t L, glm::qualifier Q>
	bool notEqual(const series<glm::vec<L,unsigned int,Q>>& a, const glm::vec<L,unsigned int,Q> b)
	{
		bool out(false);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i] - b != glm::vec<L,unsigned int, Q>(0);
		}
		return out;
	}
	template<glm::length_t L, glm::qualifier Q>
	bool equal(const series<glm::vec<L,unsigned int,Q>>& a, const series<glm::vec<L,unsigned int,Q>>& b)
	{
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= a[i] - b[i] == glm::vec<L,unsigned int, Q>(0);
		}
		return out;
	}
	template<glm::length_t L, glm::qualifier Q>
	bool notEqual(const series<glm::vec<L,unsigned int,Q>>& a, const series<glm::vec<L,unsigned int,Q>>& b)
	{
		bool out(false);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i] - b[i] != glm::vec<L,unsigned int, Q>(0);
		}
		return out;
	}





	template<glm::length_t L, glm::qualifier Q>
	void equal(const series<glm::vec<L,unsigned int,Q>>& a, const glm::vec<L,unsigned int,Q> b, series<bool>& out)
	{
		many::transform(a, b, [](const glm::vec<L,unsigned int,Q>& ai, const glm::vec<L,unsigned int,Q>& bi){ return ai == bi; }, out);
	}
	template<glm::length_t L, glm::qualifier Q>
	void notEqual(const series<glm::vec<L,unsigned int,Q>>& a, const glm::vec<L,unsigned int,Q> b, series<bool>& out)
	{
		many::transform(a, b, [](const glm::vec<L,unsigned int,Q>& ai, const glm::vec<L,unsigned int,Q>& bi){ return ai != bi; }, out);
	}
	template<glm::length_t L, glm::qualifier Q>
	void equal(const series<glm::vec<L,unsigned int,Q>>& a, const series<glm::vec<L,unsigned int,Q>>& b, series<bool>& out)
	{
		many::transform(a, b, [](const glm::vec<L,unsigned int,Q>& ai, const glm::vec<L,unsigned int,Q>& bi){ return ai == bi; }, out);
	}
	template<glm::length_t L, glm::qualifier Q>
	void notEqual(const series<glm::vec<L,unsigned int,Q>>& a, const series<glm::vec<L,unsigned int,Q>>& b, series<bool>& out)
	{
		many::transform(a, b, [](const glm::vec<L,unsigned int,Q>& ai, const glm::vec<L,unsigned int,Q>& bi){ return ai != bi; }, out);
	}







	template<glm::length_t L, glm::qualifier Q>
	bool equal(const series<glm::vec<L,int,Q>>& a, const glm::vec<L,int,Q> b)
	{
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= a[i] - b == glm::vec<L,int, Q>(0);
		}
		return out;
	}
	template<glm::length_t L, glm::qualifier Q>
	bool notEqual(const series<glm::vec<L,int,Q>>& a, const glm::vec<L,int,Q> b)
	{
		bool out(false);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i] - b != glm::vec<L,int, Q>(0);
		}
		return out;
	}
	template<glm::length_t L, glm::qualifier Q>
	bool equal(const series<glm::vec<L,int,Q>>& a, const series<glm::vec<L,int,Q>>& b)
	{
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= a[i] - b[i] == glm::vec<L,int, Q>(0);
		}
		return out;
	}
	template<glm::length_t L, glm::qualifier Q>
	bool notEqual(const series<glm::vec<L,int,Q>>& a, const series<glm::vec<L,int,Q>>& b)
	{
		bool out(false);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i] - b[i] != glm::vec<L,int, Q>(0);
		}
		return out;
	}





	template<glm::length_t L, glm::qualifier Q>
	void equal(const series<glm::vec<L,int,Q>>& a, const glm::vec<L,int,Q> b, series<bool>& out)
	{
		many::transform(a, b, [](const glm::vec<L,int,Q>& ai, const glm::vec<L,int,Q>& bi){ return ai == bi; }, out);
	}
	template<glm::length_t L, glm::qualifier Q>
	void notEqual(const series<glm::vec<L,int,Q>>& a, const glm::vec<L,int,Q> b, series<bool>& out)
	{
		many::transform(a, b, [](const glm::vec<L,int,Q>& ai, const glm::vec<L,int,Q>& bi){ return ai != bi; }, out);
	}
	template<glm::length_t L, glm::qualifier Q>
	void equal(const series<glm::vec<L,int,Q>>& a, const series<glm::vec<L,int,Q>>& b, series<bool>& out)
	{
		many::transform(a, b, [](const glm::vec<L,int,Q>& ai, const glm::vec<L,int,Q>& bi){ return ai == bi; }, out);
	}
	template<glm::length_t L, glm::qualifier Q>
	void notEqual(const series<glm::vec<L,int,Q>>& a, const series<glm::vec<L,int,Q>>& b, series<bool>& out)
	{
		many::transform(a, b, [](const glm::vec<L,int,Q>& ai, const glm::vec<L,int,Q>& bi){ return ai != bi; }, out);
	}








	template<glm::length_t L, glm::qualifier Q>
	bool equal(const series<glm::vec<L,bool,Q>>& a, const glm::vec<L,bool,Q> b)
	{
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= a[i] - b == glm::vec<L,bool, Q>(0);
		}
		return out;
	}
	template<glm::length_t L, glm::qualifier Q>
	bool notEqual(const series<glm::vec<L,bool,Q>>& a, const glm::vec<L,bool,Q> b)
	{
		bool out(false);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i] - b != glm::vec<L,bool, Q>(0);
		}
		return out;
	}
	template<glm::length_t L, glm::qualifier Q>
	bool equal(const series<glm::vec<L,bool,Q>>& a, const series<glm::vec<L,bool,Q>>& b)
	{
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= a[i] - b[i] == glm::vec<L,bool, Q>(0);
		}
		return out;
	}
	template<glm::length_t L, glm::qualifier Q>
	bool notEqual(const series<glm::vec<L,bool,Q>>& a, const series<glm::vec<L,bool,Q>>& b)
	{
		bool out(false);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i] - b[i] != glm::vec<L,bool, Q>(0);
		}
		return out;
	}





	template<glm::length_t L, glm::qualifier Q>
	void equal(const series<glm::vec<L,bool,Q>>& a, const glm::vec<L,bool,Q> b, series<bool>& out)
	{
		many::transform(a, b, [](const glm::vec<L,bool,Q>& ai, const glm::vec<L,bool,Q>& bi){ return ai == bi; }, out);
	}
	template<glm::length_t L, glm::qualifier Q>
	void notEqual(const series<glm::vec<L,bool,Q>>& a, const glm::vec<L,bool,Q> b, series<bool>& out)
	{
		many::transform(a, b, [](const glm::vec<L,bool,Q>& ai, const glm::vec<L,bool,Q>& bi){ return ai != bi; }, out);
	}
	template<glm::length_t L, glm::qualifier Q>
	void equal(const series<glm::vec<L,bool,Q>>& a, const series<glm::vec<L,bool,Q>>& b, series<bool>& out)
	{
		many::transform(a, b, [](const glm::vec<L,bool,Q>& ai, const glm::vec<L,bool,Q>& bi){ return ai == bi; }, out);
	}
	template<glm::length_t L, glm::qualifier Q>
	void notEqual(const series<glm::vec<L,bool,Q>>& a, const series<glm::vec<L,bool,Q>>& b, series<bool>& out)
	{
		many::transform(a, b, [](const glm::vec<L,bool,Q>& ai, const glm::vec<L,bool,Q>& bi){ return ai != bi; }, out);
	}




	template<glm::length_t L, typename T, glm::qualifier Q>
	bool equal(const series<glm::vec<L,T,Q>>& a, const glm::vec<L,T,Q> b, T threshold = T(MANY_EPSILON))
	{
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= glm::distance(a[i], b) <= threshold;
		}
		return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	bool notEqual(const series<glm::vec<L,T,Q>>& a, const glm::vec<L,T,Q> b, T threshold = T(MANY_EPSILON))
	{
		bool out(false);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= glm::distance(a[i], b) > threshold;
		}
		return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	bool equal(const series<glm::vec<L,T,Q>>& a, const series<glm::vec<L,T,Q>>& b, T threshold = T(MANY_EPSILON))
	{
		bool out(true);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= glm::distance(a[i], b[i]) <= threshold;
		}
		return out;
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	bool notEqual(const series<glm::vec<L,T,Q>>& a, const series<glm::vec<L,T,Q>>& b, T threshold = T(MANY_EPSILON))
	{
		bool out(false);
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= glm::distance(a[i], b[i]) > threshold;
		}
		return out;
	}



	template<glm::length_t L, typename T, glm::qualifier Q>
	void equal(const series<glm::vec<L,T,Q>>& a, const glm::vec<L,T,Q> b, series<bool>& out, T threshold = T(MANY_EPSILON))
	{
		many::transform(a, b, [threshold](const glm::vec<L,bool,Q> ai, const glm::vec<L,bool,Q> bi){ return glm::distance(ai,bi) <= threshold; }, out);
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	void notEqual(const series<glm::vec<L,T,Q>>& a, const glm::vec<L,T,Q> b, series<bool>& out, T threshold = T(MANY_EPSILON))
	{
		many::transform(a, b, [threshold](const glm::vec<L,bool,Q> ai, const glm::vec<L,bool,Q> bi){ return glm::distance(ai,bi) <= threshold; }, out);
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	void equal(const series<glm::vec<L,T,Q>>& a, const series<glm::vec<L,T,Q>>& b, series<bool>& out, T threshold = T(MANY_EPSILON))
	{
		many::transform(a, b, [threshold](const glm::vec<L,bool,Q> ai, const glm::vec<L,bool,Q> bi){ return glm::distance(ai,bi) <= threshold; }, out);
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	void notEqual(const series<glm::vec<L,T,Q>>& a, const series<glm::vec<L,T,Q>>& b, series<bool>& out, T threshold = T(MANY_EPSILON))
	{
		many::transform(a, b, [threshold](const glm::vec<L,bool,Q> ai, const glm::vec<L,bool,Q> bi){ return glm::distance(ai,bi) <= threshold; }, out);
	}

	template<glm::length_t L, typename T, glm::qualifier Q>
	void greaterThan(const series<glm::vec<L,T,Q>>& a, const glm::vec<L,T,Q> b, series<glm::vec<L,bool,glm::defaultp>>& out)
	{
		many::transform(a, b, [](const glm::vec<L,bool,Q>& ai, const glm::vec<L,bool,Q>& bi){ return glm::greaterThan(ai,bi); }, out); 
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	void greaterThanEqual(const series<glm::vec<L,T,Q>>& a, const glm::vec<L,T,Q> b, series<glm::vec<L,bool,glm::defaultp>>& out)
	{
		many::transform(a, b, [](const glm::vec<L,bool,Q>& ai, const glm::vec<L,bool,Q>& bi){ return glm::greaterThanEqual(ai,bi); }, out); 
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	void lessThan(const series<glm::vec<L,T,Q>>& a, const glm::vec<L,T,Q> b, series<glm::vec<L,bool,glm::defaultp>>& out)
	{
		many::transform(a, b, [](const glm::vec<L,bool,Q>& ai, const glm::vec<L,bool,Q>& bi){ return glm::lessThan(ai,bi); }, out); 
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	void lessThanEqual(const series<glm::vec<L,T,Q>>& a, const glm::vec<L,T,Q> b, series<glm::vec<L,bool,glm::defaultp>>& out)
	{
		many::transform(a, b, [](const glm::vec<L,bool,Q>& ai, const glm::vec<L,bool,Q>& bi){ return glm::lessThanEqual(ai,bi); }, out); 
	}





	template<glm::length_t L, typename T, glm::qualifier Q>
	void greaterThan(const series<glm::vec<L,T,Q>>& a, const series<glm::vec<L,T,Q>>& b, series<glm::vec<L,bool,glm::defaultp>>& out)
	{
		many::transform(a, b, [](const glm::vec<L,bool,Q>& ai, const glm::vec<L,bool,Q>& bi){ return glm::greaterThan(ai,bi); }, out); 
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	void greaterThanEqual(const series<glm::vec<L,T,Q>>& a, const series<glm::vec<L,T,Q>>& b, series<glm::vec<L,bool,glm::defaultp>>& out)
	{
		many::transform(a, b, [](const glm::vec<L,bool,Q>& ai, const glm::vec<L,bool,Q>& bi){ return glm::greaterThanEqual(ai,bi); }, out); 
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	void lessThan(const series<glm::vec<L,T,Q>>& a, const series<glm::vec<L,T,Q>>& b, series<glm::vec<L,bool,glm::defaultp>>& out)
	{
		many::transform(a, b, [](const glm::vec<L,bool,Q>& ai, const glm::vec<L,bool,Q>& bi){ return glm::lessThan(ai,bi); }, out); 
	}
	template<glm::length_t L, typename T, glm::qualifier Q>
	void lessThanEqual(const series<glm::vec<L,T,Q>>& a, const series<glm::vec<L,T,Q>>& b, series<glm::vec<L,bool,glm::defaultp>>& out)
	{
		many::transform(a, b, [](const glm::vec<L,bool,Q>& ai, const glm::vec<L,bool,Q>& bi){ return glm::lessThanEqual(ai,bi); }, out); 
	}

}