#ifndef __SELECT_STATE_HPP__
#define __SELECT_STATE_HPP__

namespace linq
{	
	template <typename S, typename F, typename T>
	class SelectState : public IState<T>
	{
		private:
			S source;
			F transformer;
		
		public:
			SelectState(S&& in, const F& transformer) 
				: source(in), transformer(transformer)
			{
			}
		
			void Init() override final
			{
				source.Init();
			}
			
			bool Valid() const noexcept override final
			{ 
				return source.Valid(); 
			}

			void Advance() override final
			{ 
				source.Advance(); 
			};
			
			T Current() const override final
			{ 
				return transformer(source.Current()); 
			};
	};
}

#endif /* end of include guard: __SELECT_STATE_HPP__ */
