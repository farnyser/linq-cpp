#ifndef __TAKE_STATE_HPP__
#define __TAKE_STATE_HPP__

namespace linq
{
	template <typename S, typename T>
	class TakeState : public IState<T>
	{
		private:
			S source;
			size_t current;
			const size_t count;

		public:
			TakeState(S&& source, const size_t count) 
				: source(source), count(count) { }
			
			void Init() override final
			{
				current = 0;
				source.Init(); 
			}
				
			bool Valid() const noexcept override final { return current < count && source.Valid(); }

			void Advance() override final 
			{ 
				source.Advance(); 
				current++;
			};
			
			T Current() const override final { return source.Current(); };
	};
}

#endif /* end of include guard: __TAKE_STATE_HPP__ */
