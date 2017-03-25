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

namespace linq 
{
	template <typename T> struct IEnumerableCore;
	
	template <typename T>
	class IEnumerable
	{
		public:
			std::shared_ptr<IState<T>> state;
		
			IEnumerable<T>(IState<T>* state) : state(state) {}
			IEnumerable<T>(std::shared_ptr<IState<T>> state) : state(state) {}
		
			bool Valid() const noexcept { return state->Valid(); }
			void Advance() { return state->Advance(); }
			decltype(auto) Current() const { return state->Current(); }
			void Init() { state->Init(); }
		
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
			template <typename F> auto GroupBy(const F& f);
			T First();
			T Last();
			auto Sum();
			size_t Count();
	};
}

#include "RangeState.hpp"
#include "AdapterState.hpp"
#include "GroupByState.hpp"
#include "IEnumerableCore.hpp"

#endif /* end of include guard: __IENUMERABLE_HPP__ */
