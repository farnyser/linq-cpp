#ifndef __LOGIC_CONTAINS_HPP__
#define __LOGIC_CONTAINS_HPP__

namespace linq
{
	template <typename S, typename T>
	bool Contains(S&& source, const T& item)
	{
		for(source.Init() ; source.Valid() ; source.Advance())
			if(source.Current() == item)
				return true;

		return false;
	};
}

#endif /* end of include guard: __LOGIC_CONTAINS_HPP__ */
