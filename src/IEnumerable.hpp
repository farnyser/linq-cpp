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
			IEnumerable<T>(std::shared_ptr<IState<T>> state) : state(state) {}
		
			std::pair<bool, T> Next() { return state->Next(); }
			void Init() { state->Init(); }
		
			static IEnumerable<T>& Empty()
			{
				static IEnumerable<T> empty(new IState<T>());
				return empty;
			}
		
			class iterator : public std::iterator<std::input_iterator_tag, T, T, const T*, T>
			{
			private:
				std::shared_ptr<T> current;
				IEnumerable<T> source;
				bool valid { false };

			public:
				iterator(IEnumerable<T> src) : source(src) {
					source.Init();		
					operator++();
				}
				iterator() : source(IEnumerable<T>::Empty()), valid(false) {}
			
				bool operator==(iterator other) const { return !valid && !other.valid; }
				bool operator!=(iterator other) const { return !(*this == other); }
				iterator& operator++() {					
					auto result = source.Next();
					valid = result.first;
					current.reset(new T{result.second}); 
					return *this;
				}
				iterator operator++(int) {iterator retval = *this; ++(*this); return retval;}
				const T& operator*() const { return *current; }
			}; 	
			
			iterator begin() { return iterator(*this); }
			iterator end() { return iterator(); }
			
			static IEnumerable<T> Range(T from, T to);
			IEnumerable<T> Where(std::function<bool(const T&)> where);
			IEnumerable<T> Take(size_t count);
			IEnumerable<T> TakeWhile(const std::function<bool(const T&)>& filter);
			IEnumerable<T> Skip(size_t count);
			IEnumerable<T> SkipWhile(const std::function<bool(const T&)>& filter);
			template <typename F> auto Select(const F& f);
			template <typename F> auto GroupBy(const F& f);
			T First();
			T Last();
			auto Sum();
			size_t Count();
	};
	
	template <typename T> 
	size_t IEnumerable<T>::Count() 
	{
		size_t count = 0; 
		
		for(auto& _ : *this) 
			count++; 
		
		return count;
	}	
	
	template <typename T> 
	auto IEnumerable<T>::Sum() 
	{
		decltype(T{}+T{}) result{}; 
		
		for(auto& _ : *this) 
			result += _; 
		
		return result;
	}
	
	template <typename T> 
	T IEnumerable<T>::First() 
	{
		auto it = begin();
		if(it != end())
			return *it;
		
		throw std::out_of_range("this");
	}
	
	template <typename T> 
	T IEnumerable<T>::Last() 
	{
		auto it = begin();
		while(it != end()) 
		{
			auto result = *it;
			if(++it == end())
				return result;
		}
		
		throw std::out_of_range("this");
	}
}

#include "RangeState.hpp"
#include "WhereState.hpp"
#include "TakeState.hpp"
#include "TakeWhileState.hpp"
#include "SkipWhileState.hpp"
#include "SkipState.hpp"
#include "AdapterState.hpp"
#include "SelectState.hpp"
#include "GroupByState.hpp"

#endif /* end of include guard: __IENUMERABLE_HPP__ */
