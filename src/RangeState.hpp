#ifndef __RANGE_STATE_HPP__
#define __RANGE_STATE_HPP__

namespace linq
{
	template<typename T>
	class RangeState : public IState<T>
	{
		public:
			RangeState(const T& from, const T& to) : from(from), to(to) 
			{
			}
			
			bool Next(T& n) override
			{
				if(current == to)
					return false;
				
				n = ++current;
				return true;
			};
				
			void Init() override 
			{
				current = from;
			};

		protected:
			const T from;
			const T to;
			T current;
	};
		
	template <typename T>
	IEnumerable<T> IEnumerable<T>::Range(T from, T to)
	{
		return IEnumerable<T>(new RangeState<T>(from, to));
	}
}

#endif /* end of include guard: __RANGE_STATE_HPP__ */
