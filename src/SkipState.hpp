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
				
			bool Next(T& out) override
			{ 
				bool valid = false;
				
				while(current < count) 
					valid = source.Next(out), current++; 
				
				valid = source.Next(out); 
				return valid;
			}
	};
	
	template <typename T>
	IEnumerable<T> IEnumerable<T>::Skip(size_t count)
	{
		return IEnumerable<T>(new SkipState<T>(*this, count));
	}
}

#endif /* end of include guard: __SKIP_STATE_HPP__ */
