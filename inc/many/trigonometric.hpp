/// Function parameters specified as angle are assumed to be in units of radians.
/// In no case will any of these functions result in a divide by zero error. If
/// the divisor of a ratio is 0, then results will be undefined.
///
/// These all operate component-wise. The description is per component.

#pragma once

#include <cmath>

#include "types.hpp"

namespace many
{

	/// Converts degrees to radians and returns the result.
	template <typename T>
	void radians(const series<T>& degrees, series<T>& out)
	{
		T conversion_factor(M_PI/180.);
		return transform(degrees, [conversion_factor](T degreesi){ return conversion_factor * degreesi; }, out);
	}

	/// Converts degrees to radians and returns the result.
	template <typename T>
	void degrees(const series<T>& radians, series<T>& out)
	{
		T conversion_factor(180./M_PI);
		return transform(radians, [conversion_factor](T radiansi){ return conversion_factor * radiansi; }, out);
	}

	/// The standard trigonometric sine function.
	/// The values returned by this function will range from [-1, 1].
	template <typename T>
	void sin(const series<T>& radians, series<T>& out)
	{
		return transform(radians, std::sin, out);
	}

	/// The standard trigonometric cosine function.
	/// The values returned by this function will range from [-1, 1].
	template <typename T>
	void cos(const series<T>& radians, series<T>& out)
	{
		return transform(radians, std::cos, out);
	}

	/// The standard trigonometric tangent function.
	template <typename T>
	void tan(const series<T>& radians, series<T>& out)
	{
		return transform(radians, std::tan, out);
	}

	/// Arc sine. Returns an angle whose sine is x.
	/// The range of values returned by this function is [-PI/2, PI/2].
	/// Results are undefined if |x| > 1.
	template <typename T>
	void asin(const series<T>& x, series<T>& out)
	{
		return transform(x, std::asin, out);
	}

	/// Arc cosine. Returns an angle whose sine is x.
	/// The range of values returned by this function is [0, PI].
	/// Results are undefined if |x| > 1.
	template <typename T>
	void acos(const series<T>& x, series<T>& out)
	{
		return transform(x, std::acos, out);
	}

	/// Arc tangent. Returns an angle whose tangent is y_over_x.
	/// The signs of x and y are used to determine what
	/// quadrant the angle is in. The range of values returned
	/// by this function is [-PI, PI]. Results are undefined
	/// if x and y are both 0.
	template <typename T>
	void atan(const series<T>& y_over_x, series<T>& out)
	{
		return transform(y_over_x, std::atan, out);
	}


	/// Arc tangent. Returns an angle whose tangent is y/x.
	/// The signs of x and y are used to determine what
	/// quadrant the angle is in. The range of values returned
	/// by this function is [-PI, PI]. Results are undefined
	/// if x and y are both 0.
	template <typename T>
	void atan(const series<T>& x, const series<T>& y, series<T>& out)
	{
		return transform(x, y, std::atan2, out);
	}


	/// Returns the hyperbolic sine function, (exp(x) - exp(-x)) / 2
	template <typename T>
	void sinh(const series<T>& radians, series<T>& out)
	{
		return transform(radians, std::sinh, out);
	}

	/// Returns the hyperbolic cosine function, (exp(x) + exp(-x)) / 2
	template <typename T>
	void cosh(const series<T>& radians, series<T>& out)
	{
		return transform(radians, std::cosh, out);
	}

	/// Returns the hyperbolic tangent function, sinh(angle) / cosh(angle)
	template <typename T>
	void tanh(const series<T>& radians, series<T>& out)
	{
		return transform(radians, std::tanh, out);
	}

	/// Arc hyperbolic sine; returns the inverse of sinh.
	template <typename T>
	void asinh(const series<T>& x, series<T>& out)
	{
		return transform(x, std::asinh, out);
	}

	/// Arc hyperbolic cosine; returns the non-negative inverse
	/// of cosh. Results are undefined if x < 1.
	template <typename T>
	void acosh(const series<T>& x, series<T>& out)
	{
		return transform(x, std::acosh, out);
	}

	/// Arc hyperbolic tangent; returns the inverse of tanh.
	/// Results are undefined if abs(x) >= 1.
	template <typename T>
	void atanh(const series<T>& x, series<T>& out)
	{
		return transform(x, std::atanh, out);
	}

}//namespace many

