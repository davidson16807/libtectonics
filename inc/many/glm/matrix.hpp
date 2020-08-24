#pragma once

#include "../types.hpp"

namespace many{
	template<glm::length_t R, glm::length_t C, typename T, glm::qualifier Q>
	void mult(const series<glm::mat<R,C,T,Q>>& A, const series<glm::vec<R,T,Q>>& b, series<glm::vec<C,T,Q>>& out)
	{
		out.store([](glm::mat<R,C,T,Q>Ai, glm::vec<R,T,Q> bi){ return Ai * bi; }, A, b);
	}
	template<glm::length_t R, glm::length_t C, typename T, glm::qualifier Q>
	void mult(const glm::mat<R,C,T,Q>& A, const series<glm::vec<R,T,Q>>& b, series<glm::vec<C,T,Q>>& out)
	{
		out.store([](glm::mat<R,C,T,Q>Ai, glm::vec<R,T,Q> bi){ return Ai * bi; }, A, b);
	}
	template<glm::length_t R, glm::length_t C, typename T, glm::qualifier Q>
	void mult(const glm::mat<R,C,T,Q>& A, const glm::vec<R,T,Q>& b, series<glm::vec<C,T,Q>>& out)
	{
		out.store([](glm::mat<R,C,T,Q>Ai, glm::vec<R,T,Q> bi){ return Ai * bi; }, A, b);
	}


	template<typename T, glm::qualifier Q>
	void mult(const glm::mat<4,4,T,Q>& A, const series<glm::vec<3,T,Q>>& b, series<glm::vec<3,T,Q>>& out)
	{
		constexpr T one = T(1.);
		for (unsigned int i = 0; i < b.size(); ++i)
		{
			out[i] = A * glm::vec<4,T,Q>(b[i], one);
		}
	}
	template<typename T, glm::qualifier Q>
	void mult(const glm::mat<4,3,T,Q>& A, const series<glm::vec<3,T,Q>>& b, series<glm::vec<3,T,Q>>& out)
	{
		constexpr T one = T(1.);
		for (unsigned int i = 0; i < b.size(); ++i)
		{
			out[i] = A * glm::vec<4,T,Q>(b[i], one);
		}
	}
}