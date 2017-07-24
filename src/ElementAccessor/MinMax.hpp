#ifndef __ELEMENT_ACCESSOR_MINMAX_HPP__
#define __ELEMENT_ACCESSOR_MINMAX_HPP__

namespace linq
{
	template <typename S, typename F>
	auto Min(S&& source, const F& fct)
	{
		source.Init();
		if(!source.Valid())
			throw std::out_of_range("this");

		auto result = source.Current();
		auto result_score = fct(result);

		while(true)
		{
			source.Advance();
			if(!source.Valid())
				return result;

			decltype(result) current = source.Current();
			auto current_score = fct(current);
			if(current_score < result_score)
				result = current, result_score = current_score;
		}
	}

	template <typename S, typename F>
	auto Max(S&& source, const F& fct)
	{
		source.Init();
		if(!source.Valid())
			throw std::out_of_range("this");

		auto result = source.Current();
		auto result_score = fct(result);

		while(true)
		{
			source.Advance();
			if(!source.Valid())
				return result;

			decltype(result) current = source.Current();
			auto current_score = fct(current);
			if(current_score > result_score)
				result = current, result_score = current_score;
		}
	}
}

#endif /* end of include guard: __ELEMENT_ACCESSOR_MINMAX_HPP__ */
