#ifndef __IENUMERABLE_HPP__
#define __IENUMERABLE_HPP__

#include <memory>
#include <algorithm>
#include "IState.hpp"

namespace linq 
{
	template <typename T>
	class IEnumerable
	{
		public:
			std::shared_ptr<IState<T>> state;
		
			IEnumerable<T>(IState<T>* state) : state(state) {}
		
			bool Next(T& t) { return state->Next(t); }
			void Init() { state->Init(); }
		
			static IEnumerable<T>& Empty()
			{
				static IEnumerable<T> empty(new IState<T>());
				return empty;
			}
		
			class iterator : public std::iterator<std::input_iterator_tag, T, T, const T*, T>
			{
			private:
				T current;
				IEnumerable<T> source;
				bool valid { false };

			public:
				iterator(IEnumerable<T> src) : source(src) {
					source.Init();
					valid = source.Next(current);
				}
				iterator() : source(IEnumerable<T>::Empty()), valid(false) {}
			
				bool operator==(iterator other) const { return !valid && !other.valid; }
				bool operator!=(iterator other) const { return !(*this == other); }
				iterator& operator++() {valid = source.Next(current); return *this;}
				iterator operator++(int) {iterator retval = *this; ++(*this); return retval;}
				const T& operator*() const { return current; }
			}; 	
			
			iterator begin() { return iterator(*this); }
			iterator end() { return iterator(); }
			
			static IEnumerable<T> Range(T from, T to);
			IEnumerable<T> Where(std::function<bool(const T&)> where);
			IEnumerable<T> Take(size_t count);
			IEnumerable<T> Skip(size_t count);
	};	
}

#include "RangeState.hpp"
#include "WhereState.hpp"
#include "TakeState.hpp"
#include "SkipState.hpp"

#endif /* end of include guard: __IENUMERABLE_HPP__ */
