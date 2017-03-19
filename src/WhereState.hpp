#ifndef __WHERE_STATE_HPP__
#define __WHERE_STATE_HPP__

namespace linq
{	
	template <typename S, typename F, typename T>
	class WhereState : public IState<T>
	{
		private:
			S source;
			F filter;

		public:
			WhereState(S&& source, const F& filter) 
				: source(source), filter(filter) 
			{
			}
			
			void Init() final override 
			{ 
				source.Init(); 
				
				while(source.Valid() && !filter(source.Current()))
					source.Advance();
			}
				
			bool Valid() const noexcept final override 
			{ 
				return source.Valid(); 
			}

			void Advance() final override 
			{
				source.Advance();

				while(source.Valid() && !filter(source.Current()))
					source.Advance();
			};
			
			T Current() const final override 
			{ 
				return source.Current(); 
			};
	};
}

#endif /* end of include guard: __WHERE_STATE_HPP__ */
