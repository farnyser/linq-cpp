#ifndef __ELEMENT_ACCESSOR_FIRST_HPP__
#define __ELEMENT_ACCESSOR_FIRST_HPP__

namespace linq
{
	template <typename S>
	auto First(S&& source)
	{
		source.Init();

		if(!source.Valid())
			throw std::out_of_range("this");

		return source.Current();
	}
}

#endif /* end of include guard: __ELEMENT_ACCESSOR_FIRST_HPP__ */
