#ifndef __TAKE_STATE_HPP__
#define __TAKE_STATE_HPP__

namespace linq
{
	template <typename T>
	class TakeState : public IState<T>
	{
		private:
			IEnumerable<T> source;
			size_t current;
			size_t count;

		public:
			TakeState(IEnumerable<T> source, size_t count) : source(source), count(count) 
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
				
				if(current < count) 
					valid = source.Next(out), current++; 
				
				return valid;
			}
	};
	
	template <typename T>
	IEnumerable<T> IEnumerable<T>::Take(size_t count)
	{
		return IEnumerable<T>(new TakeState<T>(*this, count));
	}
}

#endif /* end of include guard: __TAKE_STATE_HPP__ */
