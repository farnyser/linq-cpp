#ifndef __ACCUMULATOR_SUM_HPP__
#define __ACCUMULATOR_SUM_HPP__

namespace linq
{
	template <typename S, typename F>
	auto Sum(S&& source, const F& fct)
	{
		source.Init();
		if(!source.Valid())
			throw std::out_of_range("this");

		auto result = fct(source.Current());

		while(true)
		{
			source.Advance();
			if(!source.Valid())
				return result;

			result += fct(source.Current());
		}
	}
}

#endif /* end of include guard: __ACCUMULATOR_SUM_HPP__ */
