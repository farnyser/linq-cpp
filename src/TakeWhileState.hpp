#ifndef __TAKEWHILE_STATE_HPP__
#define __TAKEWHILE_STATE_HPP__

#include "IState.hpp"

namespace linq
{
	template <typename S, typename F, typename T>
	class TakeWhileState : public IState<T>
	{
		private:
			S source;
			F filter;

		public:
			TakeWhileState(S&& source, const F& filter) 
				: source(source), filter(filter) { }
			
			void Init() override final { source.Init(); }
				
			bool Valid() const noexcept override final
			{ 
				return source.Valid() && filter(source.Current()); 
			}
			
			void Advance() override final
			{
				source.Advance();
			}
			
			T Current() const override final { return source.Current(); }
	};
}

#endif /* end of include guard: __TAKEWHILE_STATE_HPP__ */
