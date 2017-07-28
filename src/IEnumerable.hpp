#ifndef __IENUMERABLE_HPP__
#define __IENUMERABLE_HPP__

#include <memory>
#include <algorithm>
#include "IState.hpp"
#include "TakeState.hpp"
#include "TakeWhileState.hpp"
#include "SkipState.hpp"
#include "SkipWhileState.hpp"
#include "WhereState.hpp"
#include "SelectState.hpp"
#include "Accumulator/Sum.hpp"
#include "ElementAccessor/Single.hpp"
#include "ElementAccessor/First.hpp"
#include "ElementAccessor/Last.hpp"
#include "ElementAccessor/MinMax.hpp"
#include "SetBuilder/Distinct.hpp"

namespace linq 
{
	template <typename T> struct IEnumerableCore;
	
	template <typename T>
	class IEnumerable : public IState<T>
	{
		public:
			std::shared_ptr<IState<T>> state;
		
			IEnumerable<T>() : state() {}
			IEnumerable<T>(IState<T>* state) : state(state) {}
			IEnumerable<T>(std::shared_ptr<IState<T>> state) : state(state) {}
		
			bool Valid() const noexcept override final { return state->Valid(); }
			void Advance() override final { return state->Advance(); }
			T Current() const override final { return state->Current(); }
			void Init() override final { state->Init(); }
		
			static IEnumerable<T>& Empty()
			{
				static IEnumerable<T> empty(new IState<T>());
				return empty;
			}
		
			class iterator : public std::iterator<std::input_iterator_tag, void, typename std::remove_reference<T>::type, const typename std::remove_reference<T>::type*, T>
			{
			private:
				IEnumerable<T> source;
				bool valid { false };

			public:
				iterator(IEnumerable<T> src) : source(src) {
					source.Init();	
					valid = source.Valid();
				}
				iterator() : source(IEnumerable<T>::Empty()), valid(false) {}
			
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
			
			iterator begin() { return iterator(*this); }
			iterator end() { return iterator(); }
			iterator begin() const { return iterator(*this); }
			iterator end() const { return iterator(); }
			
			static IEnumerable<T> Range(T from, T to);
			template <typename F> IEnumerableCore<WhereState<IEnumerable<T>, F, T>> Where(const F& where);
			IEnumerableCore<TakeState<IEnumerable<T>, T>> Take(size_t count);
			template <typename F> IEnumerableCore<TakeWhileState<IEnumerable<T>, F, T>> TakeWhile(const F& f);
			IEnumerableCore<SkipState<IEnumerable<T>, T>> Skip(size_t count);
			template <typename F> IEnumerableCore<SkipWhileState<IEnumerable<T>, F, T>> SkipWhile(const F& f);
			template <typename F> auto Select(const F& f);
			template <typename S2> auto Concat(S2&& s);
			template <typename F> auto GroupBy(const F& f);
			template <typename F> auto Distinct(const F& f);
			auto Distinct();
			template <typename S2, typename F> auto Intersect(S2&& s, const F& f);
			template <typename S2> auto Intersect(S2&& s);
			template <typename S2, typename F> auto Except(S2&& s, const F& f);
			template <typename S2> auto Except(S2&& s);
			template<typename S> auto Union(S&& other);
			size_t Count();

			auto Single() { return linq::Single(std::move(*this)); }
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
	};
}

#include "RangeState.hpp"
#include "AdapterState.hpp"
#include "GroupByState.hpp"
#include "IEnumerableCore.hpp"

#endif /* end of include guard: __IENUMERABLE_HPP__ */
