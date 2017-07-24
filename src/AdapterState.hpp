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
		typename std::remove_reference<INPUT>::type::iterator end;

		AdapterState(INPUT&& source) 
			: source(source) 
		{
		}
		
		void Init() override final
		{ 
			current = source.begin();
			end = source.end();
		}
				
		bool Valid() const noexcept override final
		{ 
			return current != end;
		}
		
		void Advance() override final
		{ 
			++current; 
		};
		
		T Current() const override final
		{ 
			return *current; 
		};
	};
	
	template <typename INPUT, class = typename std::enable_if<!std::is_lvalue_reference<INPUT>::value>::type>
	auto Adapt(INPUT&& source) 
	{
		using OUT = typename std::iterator_traits<typename std::remove_reference<INPUT>::type::iterator>::reference;
		return IEnumerableCore<AdapterState<OUT, INPUT>>(AdapterState<OUT, INPUT>(std::move(source)));
	};

	template <typename INPUT>
	auto AdaptView(INPUT&& source)
	{
		using OUT = typename std::iterator_traits<typename std::remove_reference<INPUT>::type::iterator>::reference;
		return IEnumerableCore<AdapterState<OUT, INPUT>>(AdapterState<OUT, INPUT>(std::forward<INPUT&&>(source)));
	};

	template <typename INPUT>
	auto AdaptCopy(INPUT& source)
	{
		using OUT = typename std::iterator_traits<typename std::remove_reference<INPUT>::type::iterator>::reference;
		return IEnumerableCore<AdapterState<OUT, INPUT&>>(AdapterState<OUT, INPUT &>(source));
	};
}

#endif /* end of include guard: __ADAPTER_STATE_HPP__ */
