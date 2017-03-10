#ifndef __TAKEWHILE_STATE_HPP__
#define __TAKEWHILE_STATE_HPP__

namespace linq
{
	template <typename T>
	class TakeWhileState : public IState<T>
	{
		private:
			IEnumerable<T> source;
			std::function<bool(const T&)> filter;
			bool done;

		public:
			TakeWhileState(IEnumerable<T> source, const std::function<bool(const T&)>& filter) 
				: source(source), filter(filter) 
			{
			}
			
			void Init() override 
			{
				source.Init(); 
				done = false;
			}
				
			std::pair<bool, T> Next() override
			{
				if(done)
					return std::make_pair(false, T{});
				
				auto result = source.Next();
				done = !filter(result.second);
				return std::make_pair(result.first && !done, result.second);
			}
	};
	
	template <typename T>
	IEnumerable<T> IEnumerable<T>::TakeWhile(const std::function<bool(const T&)>& filter)
	{
		return IEnumerable<T>(new TakeWhileState<T>(*this, filter));
	}
}

#endif /* end of include guard: __TAKEWHILE_STATE_HPP__ */
