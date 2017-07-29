#ifndef __LOGIC_ANY_HPP__
#define __LOGIC_ANY_HPP__

namespace linq
{
	template <typename S>
	bool Any(S&& source)
	{
		source.Init();
		return source.Valid();
	};
}

#endif /* end of include guard: __LOGIC_ANY_HPP__ */
