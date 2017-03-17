#ifndef __TAKEWHILE_STATE_HPP__
#define __TAKEWHILE_STATE_HPP__

#include "TakeState.hpp"

namespace linq
{
	template <typename T>
	class TakeWhileState : public TakeState<T>
	{
		private:
			IEnumerable<T> source;
			std::function<bool(const T&)> filter;

		public:
			TakeWhileState(IEnumerable<T> source, const std::function<bool(const T&)>& filter) 
				: source(source), filter(filter) 
			{
			}
			
			void Init() override 
			{
				source.Init(); 
			}
				
			bool Valid() const noexcept override 
			{ 
				return source.Valid() && filter(source.Current()); 
			}
	};
	
	template <typename T>
	IEnumerable<T> IEnumerable<T>::TakeWhile(const std::function<bool(const T&)>& filter)
	{
		return IEnumerable<T>(new TakeWhileState<T>(*this, filter));
	}
}

#endif /* end of include guard: __TAKEWHILE_STATE_HPP__ */
