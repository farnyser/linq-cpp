#ifndef __IENUMERABLE_CORE_HPP__
#define __IENUMERABLE_CORE_HPP__

#include <memory>
#include <algorithm>
#include "Accumulator/Sum.hpp"
#include "ElementAccessor/Single.hpp"
#include "ElementAccessor/First.hpp"
#include "ElementAccessor/Last.hpp"
#include "ElementAccessor/MinMax.hpp"
#include "IState.hpp"

namespace linq 
{
	template <typename S>
	struct IEnumerableCore
	{
		S source;

		IEnumerableCore(S&& source) 
			: source(source) 
		{ }
		
		decltype(auto) Current() const { return source.Current(); }
		decltype(auto) Advance() { return source.Advance(); }
		decltype(auto) Valid() const { return source.Valid(); }
		decltype(auto) Init() { return source.Init(); }
		
		using T = decltype(source.Current());
		
		class iterator : public std::iterator<std::input_iterator_tag, void, typename std::remove_reference<T>::type, const typename std::remove_reference<T>::type*, T>
		{
		private:
			mutable S source;
			bool valid { false };

		public:
			iterator(S src, bool v = true) : source(src) {
				valid = v;
				
				if(v) { 
					source.Init();	
					valid = source.Valid();
				}
			}
		
			bool operator==(iterator other) const { return !valid && !other.valid; }
			bool operator!=(iterator other) const { return !(*this == other); }
			iterator& operator++() {					
				source.Advance();
				valid = source.Valid();
				return *this;
			}
			iterator operator++(int) {iterator retval = *this; ++(*this); return retval;}
			decltype(auto) operator*() const { return source.Current(); }
		}; 	
		
		iterator begin() { return iterator(source); }
		iterator end() { return iterator(source, false); }
		
		auto Take(size_t count) 
		{ 
			return IEnumerableCore<TakeState<S, T>>(
				TakeState<S, T>(std::move(source), count)
			);
		}
		
		template <typename F> 
		decltype(auto) TakeWhile(const F& f)
		{
			return IEnumerableCore<TakeWhileState<S, F, T>>(TakeWhileState<S, F, T>(std::move(source), f));
		}

		auto Skip(size_t count) 
		{ 
			return IEnumerableCore<SkipState<S, T>>(
				SkipState<S, T>(std::move(source), count)
			);
		}
		
		template <typename F> 
		decltype(auto) SkipWhile(const F& f)
		{
			return IEnumerableCore<SkipWhileState<S, F, T>>(SkipWhileState<S, F, T>(std::move(source), f));
		}

		template <typename F> 
		decltype(auto) Select(const F& f)
		{
			using VALUE_IN = typename std::remove_reference<T>::type;
			using OUT = decltype(f(VALUE_IN{}));
			return IEnumerableCore<SelectState<S, F, OUT>>(SelectState<S, F, OUT>(std::move(source), f));
		}
		
		template <typename F> 
		auto GroupBy(const F& f)  
		{ 
			using VALUE = typename std::remove_reference<T>::type;
			using KEY = decltype(f(VALUE{}));
			return IEnumerableCore<GroupByState<IEnumerableCore<S>, KEY, VALUE>>(GroupByState<IEnumerableCore<S>, KEY, VALUE>(std::move(*this), f));
		};

		template <typename F> 
		decltype(auto) Where(const F& f)
		{
			return IEnumerableCore<WhereState<S, F, T>>(WhereState<S, F, T>(std::move(source), f));
		}

		size_t Count() 
		{
			size_t count = 0; 
			
			for(const auto& _ : *this) 
				count++; 
			
			return count;
		}

		auto Single() { return linq::Single(std::move(source)); }
		auto First()  { return linq::First(std::move(*this)); }
		auto Last()   { return linq::Last(std::move(*this)); }
		auto Min()    { return linq::Min(std::move(*this), [](const auto& x) { return x; }); }
		auto Max()    { return linq::Max(std::move(*this), [](const auto& x) { return x; }); }
		auto Sum()    { return linq::Sum(std::move(*this), [](const auto& x) { return x; }); }

		template <typename F> auto Single (const F& where)     { return linq::Single(std::move(Where(where))); }
		template <typename F> auto First  (const F& where)     { return linq::First(std::move(Where(where))); }
		template <typename F> auto Last   (const F& where)     { return linq::Last(std::move(Where(where))); }
		template <typename F> auto Min    (const F& transform) { return linq::Min(std::move(*this), transform); }
		template <typename F> auto Max    (const F& transform) { return linq::Max(std::move(*this), transform); }
		template <typename F> auto Sum    (const F& transform) { return linq::Sum(std::move(*this), transform); }

		operator IEnumerable<T>() { return IEnumerable<T>(new S(source)); }
		operator const IEnumerable<T>() const { return IEnumerable<T>(new S(source)); }
		IEnumerable<T> ToEnumerable() { return IEnumerable<T>(new S(source)); } 
	};

	template <typename T>
	size_t IEnumerable<T>::Count() { return IEnumerableCore<IEnumerable<T>>(std::move(*this)).Count(); }

	template <typename T>
	IEnumerableCore<TakeState<IEnumerable<T>, T>> IEnumerable<T>::Take(size_t count) { return IEnumerableCore<IEnumerable<T>>(std::move(*this)).Take(count); }
	
	template <typename T>
	template <typename F>
	IEnumerableCore<TakeWhileState<IEnumerable<T>, F, T>> IEnumerable<T>::TakeWhile(const F& f) 
	{ 
		return IEnumerableCore<IEnumerable<T>>(std::move(*this)).TakeWhile(f); 
	}

	template <typename T>
	IEnumerableCore<SkipState<IEnumerable<T>, T>> IEnumerable<T>::Skip(size_t count) { return IEnumerableCore<IEnumerable<T>>(std::move(*this)).Skip(count); }
	
	template <typename T>
	template <typename F>
	IEnumerableCore<SkipWhileState<IEnumerable<T>, F, T>> IEnumerable<T>::SkipWhile(const F& f) 
	{ 
		return IEnumerableCore<IEnumerable<T>>(std::move(*this)).SkipWhile(f); 
	}
	
	template <typename T>
	template <typename F>
	IEnumerableCore<WhereState<IEnumerable<T>, F, T>> IEnumerable<T>::Where(const F& f) 
	{ 
		return IEnumerableCore<IEnumerable<T>>(std::move(*this)).Where(f); 
	}
	
	template <typename T>
	template <typename F>
	auto IEnumerable<T>::Select(const F& f) { return IEnumerableCore<IEnumerable<T>>(std::move(*this)).Select(f); }
}

#endif /* end of include guard: __IENUMERABLE_CORE_HPP__ */
