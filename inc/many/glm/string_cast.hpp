#pragma once

#include <string>
#include <cmath>

#include <glm/common.hpp>	// all the GLSL common functions: abs, floor, etc.

#include "../types.hpp"

namespace many
{
	namespace 
	{
		const std::array<const std::string,16> weak 
		{
			"←","↙","↙","↓","↓","↘","↘","→","→","↗","↗","↑","↑","↖","↖","←"
		};
		const std::array<const std::string,16> strong 
		{
			"⬅","⬋","⬋","⬇","⬇","⬊","⬊","➡","➡","⬈","⬈","⬆","⬆","⬉","⬉","⬅"
		};
	} 

	template <typename T, glm::qualifier Q>
	std::string to_string(const tmany<glm::vec<2,T,Q>>& a, const int line_char_width = 80)
	{
		tmany<T> length_a(a.size());
		length(a, length_a);
		T max_length_a = max(length_a);

		std::string out("");
		for (unsigned int i = 0; i < a.size(); ++i)
		{
		    if (i % line_char_width == 0)
		    {
		    	out += "\n";
		    }

			if (std::isnan(a[i].x) || std::isnan(a[i].y))
			{
				out += "N";
			}
			else if (std::isinf(a[i].x) || std::isinf(a[i].y))
			{
				out += "∞";
			}
			else if (glm::length(a[i]) < max_length_a * T(1./3.))
			{
				out += " ";
			}
			else if (glm::length(a[i]) < max_length_a * T(2./3.))
			{
				T turn = (std::atan2(a[i].y, a[i].x)+M_PI)/(2.*M_PI);
				int i  = std::clamp(int(weak.size()*turn), 0, int(weak.size()-1));
				out   += weak[i];
			}
			else
			{
				T turn = (std::atan2(a[i].y, a[i].x)+M_PI)/(2.*M_PI);
				int i  = std::clamp(int(strong.size()*turn), 0, int(strong.size()-1));
				out   += strong[i];
			}
		}
		out += "\n";
		out += "→ > ";
		out += std::to_string(max_length_a * T(1./3.));
		out += "\n";
		out += "➡ > ";
		out += std::to_string(max_length_a * T(2./3.));
		out += "\n";
		return out;
	}

	template <typename T, glm::qualifier Q>
	std::string to_string(const tmany<glm::vec<3,T,Q>>& a, const glm::mat<3,2,T,Q>& basis, const int line_char_width = 80)
	{
		tmany<glm::vec<2,T,Q>> a2d = tmany<glm::vec<2,T,Q>>(a.size());
		mult(basis, a, a2d);
		return to_string(a2d, line_char_width);
	}

}//namespace many



