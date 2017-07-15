#ifndef __ELEMENT_ACCESSOR_LAST_HPP__
#define __ELEMENT_ACCESSOR_LAST_HPP__

namespace linq
{
	template <typename S>
	auto Last(S&& source)
	{
		source.Init();
		if(!source.Valid())
			throw std::out_of_range("this");

		while(true)
		{
			auto result = source.Current();
			source.Advance();

			if(!source.Valid())
				return result;
		}
	}
}

#endif /* end of include guard: __ELEMENT_ACCESSOR_LAST_HPP__ */
