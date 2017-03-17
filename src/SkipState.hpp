#ifndef __SKIP_STATE_HPP__
#define __SKIP_STATE_HPP__

namespace linq
{
	template <typename T>
	class SkipState : public IState<T>
	{
		private:
			IEnumerable<T> source;
			size_t current;
			size_t count;

		public:
			SkipState(IEnumerable<T> source, size_t count) : source(source), count(count) 
			{
			}
			
			void Init() override 
			{
				current = 0;
				source.Init(); 
				
				while(current < count && source.Valid()) {
					source.Advance();
					current++;
				}
			}
			
			bool Valid() const noexcept override 
			{ 
				return source.Valid(); 
			}

			void Advance() override 
			{ 
				source.Advance(); 
			};
			
			T Current() override 
			{ 
				return source.Current(); 
			};
	};
	
	template <typename T>
	IEnumerable<T> IEnumerable<T>::Skip(size_t count)
	{
		return IEnumerable<T>(new SkipState<T>(*this, count));
	}
}

#endif /* end of include guard: __SKIP_STATE_HPP__ */
