#ifndef __WHERE_STATE_HPP__
#define __WHERE_STATE_HPP__

namespace linq
{
	template <typename T>
	class WhereState : public IState<T>
	{
		private:
			IEnumerable<T> source;
			std::function<bool(const T&)> filter;

		public:
			WhereState(IEnumerable<T> source, std::function<bool(const T&)> filter) : source(source), filter(filter) 
			{
			}
			
			void Init() override 
			{ 
				source.Init(); 
			}
				
			bool Next(T& current) override
			{ 
				bool valid = false;
				
				do { 
					valid = source.Next(current); 
					if(valid && filter(current)) 
						break; 
				} while(valid);
				
				return valid;
			}
	};
	
	template <typename T>
	IEnumerable<T> IEnumerable<T>::Where(std::function<bool(const T&)> where)
	{
		return IEnumerable<T>(new WhereState<T>(*this, where));
	}
}

#endif /* end of include guard: __WHERE_STATE_HPP__ */
