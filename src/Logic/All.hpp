#ifndef __LOGIC_ALL_HPP__
#define __LOGIC_ALL_HPP__

namespace linq
{
	template <typename S, typename F>
	bool All(S&& source, const F& f)
	{
		for(source.Init() ; source.Valid() ; source.Advance())
			if(!f(source.Current()))
				return false;

		return true;
	};

	template <typename S>
	bool All(S&& source) noexcept
	{
		return true;
	};
}

#endif /* end of include guard: __LOGIC_ALL_HPP__ */
