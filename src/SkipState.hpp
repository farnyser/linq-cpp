#ifndef __SKIP_STATE_HPP__
#define __SKIP_STATE_HPP__

namespace linq
{
	template <typename S, typename T>
	class SkipState : public IState<T>
	{
		private:
			S source;
			size_t current;
			const size_t count;

		public:
			SkipState(S&& source, size_t count) 
				: source(source), count(count) { }
			
			void Init() override final
			{
				current = 0;
				source.Init(); 
				
				while(current < count && source.Valid()) {
					source.Advance();
					current++;
				}
			}
			
			bool Valid() const noexcept override final { return source.Valid(); }

			void Advance() override final
			{ 
				source.Advance(); 
			};
			
			T Current() const override final { return source.Current(); };
	};
}

#endif /* end of include guard: __SKIP_STATE_HPP__ */
