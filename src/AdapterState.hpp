#ifndef __ADAPTER_STATE_HPP__
#define __ADAPTER_STATE_HPP__

#include <utility>

namespace linq
{
	template <typename T, typename INPUT>
	struct AdapterState : IState<T>
	{
		INPUT source;
		typename std::remove_reference<INPUT>::type::iterator current;
		
		AdapterState(INPUT&& source) 
			: source(source) 
		{
		}
		
		void Init() override 
		{ 
			current = source.begin(); 
		}
				
		bool Valid() const noexcept override 
		{ 
			return current != source.end(); 
		}
		
		void Advance() override 
		{ 
			++current; 
		};
		
		T Current() override 
		{ 
			return *current; 
		};
	};

	template <typename INPUT>
	auto Adapt(INPUT&& source) 
	{
		using OUT = typename std::iterator_traits<typename std::remove_reference<INPUT>::type::iterator>::reference;
		return IEnumerable<OUT>(new AdapterState<OUT, INPUT>(std::forward<INPUT&&>(source)));
	};
}

#endif /* end of include guard: __ADAPTER_STATE_HPP__ */
