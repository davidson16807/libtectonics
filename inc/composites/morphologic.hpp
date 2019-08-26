#pragma once

#include "many.hpp"

namespace composites
{

	void unite(const many<bool>& a, const bool b, many<bool>& out)
	{
		transform(a, b, [](bool ai, bool bi){ return ai || bi; }, out);
	}

	void unite(const many<bool>& a, const many<bool>& b, many<bool>& out)
	{
		transform(a, b, [](bool ai, bool bi){ return ai || bi; }, out);
	}

	void intersect(const many<bool>& a, const bool b, many<bool>& out)
	{
		transform(a, b, [](bool ai, bool bi){ return ai && bi; }, out);
	}

	void intersect(const many<bool>& a, const many<bool>& b, many<bool>& out)
	{
		transform(a, b, [](bool ai, bool bi){ return ai && bi; }, out);
	}

	void differ(const many<bool>& a, const bool b, many<bool>& out)
	{
		transform(a, b, [](bool ai, bool bi){ return ai && !bi; }, out);
	}

	void differ(const many<bool>& a, const many<bool>& b, many<bool>& out)
	{
		transform(a, b, [](bool ai, bool bi){ return ai && !bi; }, out);
	}

	void negate(const many<bool>& a, many<bool>& out)
	{
		transform(a, [](bool ai){ return !ai; }, out);
	}

	bool all(const many<bool>& a)
	{
		bool out = true;
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out &= a[i];
		}
		return out;
	}
	bool any(const many<bool>& a)
	{
		bool out = false;
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i];
		}
		return out;
	}
	bool none(const many<bool>& a)
	{
		bool out = false;
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			out |= a[i];
		}
		return !out;
	}





}