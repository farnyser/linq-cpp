#ifndef __SKIPWHILE_STATE_HPP__
#define __SKIPWHILE_STATE_HPP__

#include "IState.hpp"

namespace linq
{
	template <typename S, typename F, typename T>
	class SkipWhileState : public IState<T>
	{
		private:
			S source;
			F filter;

		public:
			SkipWhileState(S&& source, const F& filter) 
				: source(source), filter(filter) { }
			
			void Init() override final 
			{ 
				source.Init();
				while(source.Valid() && filter(source.Current()))
					source.Advance();
			}
				
			bool Valid() const noexcept override final
			{ 
				return source.Valid();
			}
			
			void Advance() override final
			{
				source.Advance();
			}
			
			T Current() const override final { return source.Current(); }
	};
}

#endif /* end of include guard: __SKIPWHILE_STATE_HPP__ */
