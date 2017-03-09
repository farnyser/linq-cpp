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
			}
				
			std::pair<bool, T> Next() override
			{
				while(current < count) 
					source.Next(), current++;
				
				return source.Next(); 
			}
	};
	
	template <typename T>
	IEnumerable<T> IEnumerable<T>::Skip(size_t count)
	{
		return IEnumerable<T>(new SkipState<T>(*this, count));
	}
}

#endif /* end of include guard: __SKIP_STATE_HPP__ */
