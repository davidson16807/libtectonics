#pragma once

#include <string>

#include "types.hpp"
#include "common.hpp"

namespace many
{
	namespace 
	{
		#if defined(__clang__)
			const std::vector<const std::string> 
		#else
			const std::array<const std::string, 6>
		#endif
		shades {" ", "░", "▒", "▓", "█" };
	} 

	template <typename T>
	std::string to_string(const tmany<T>& a, const T lo, const T hi, const int line_char_width = 80)
	{
		std::string out("");
		for (unsigned int i = 0; i < a.size(); ++i)
		{
		    if (i % line_char_width == 0)
		    {
		    	out += "\n";
		    }
		    
			if (std::isnan(a[i]))
			{
				out += "N";
			}
			else if (std::isinf(a[i]))
			{
				out += "∞";
			}
			else 
			{
				float shade_fraction = linearstep(lo, hi, a[i]);
				int shade_id = int(std::min(float(shades.size()-1), (shades.size() * shade_fraction) ));
			    out += shades[shade_id];
			}
		}
		out += "\n";
		for (unsigned int i = 0; i < shades.size(); ++i)
		{
			out += shades[i];
			out += " ≥ ";
			out += std::to_string(mix(float(lo), float(hi), float(i)/float(shades.size())));
			out += "\n";
			// out += ", ";
		}
		return out;
	}

	template <typename T>
	std::string to_string(const tmany<T>& a, const int line_char_width = 80)
	{
		return to_string(a, min(a), max(a), line_char_width);
	}
}//namespace many



