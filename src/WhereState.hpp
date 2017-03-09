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
				
			std::pair<bool, T> Next() override
			{ 
				while(true) 
				{ 
					auto result = source.Next(); 
					if(result.first && filter(result.second)) 
						return result; 
					if(!result.first)
						break;
				}
				
				return std::make_pair(false, T{});
			}
	};
	
	template <typename T>
	IEnumerable<T> IEnumerable<T>::Where(std::function<bool(const T&)> where)
	{
		return IEnumerable<T>(new WhereState<T>(*this, where));
	}
}

#endif /* end of include guard: __WHERE_STATE_HPP__ */
