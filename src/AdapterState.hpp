#ifndef __ADAPTER_STATE_HPP__
#define __ADAPTER_STATE_HPP__

namespace linq
{
	template <typename T, typename INPUT>
	struct AdapterState : IState<T>
	{
		INPUT source;
		typename std::remove_reference<INPUT>::type::iterator current;
		
		AdapterState(INPUT source) 
			: source(source) 
		{
		}
		
		void Init() override 
		{ 
			current = source.begin(); 
		}
		
		std::pair<bool, T> Next() override 
		{ 
			if(current == source.end()) 
				return std::make_pair(false, T{});
			
			auto result = std::make_pair(true, *current);
			++current;
			
			return result;
		}
	};

	template <typename INPUT>
	auto Adapt(INPUT&& source) 
	{
		using OUT = typename std::iterator_traits<typename std::remove_reference<INPUT>::type::iterator>::value_type;
		return IEnumerable<OUT>(new AdapterState<OUT, INPUT>(source));
	};
}

#endif /* end of include guard: __ADAPTER_STATE_HPP__ */
