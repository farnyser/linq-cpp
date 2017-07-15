#ifndef __SINGLE_HPP__
#define __SINGLE_HPP__

namespace linq
{
	template <typename S>
	auto Single(S&& source)
	{
		source.Init();

		if(!source.Valid())
			throw std::out_of_range("this");

		auto it = source.Current();
		source.Advance();

		if(source.Valid())
			throw std::out_of_range("this");

		return it;
	}
}

#endif /* end of include guard: __SINGLE_HPP__ */
