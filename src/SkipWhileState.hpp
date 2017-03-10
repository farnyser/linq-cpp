#ifndef __SKIPWHILE_STATE_HPP__
#define __SKIPWHILE_STATE_HPP__

namespace linq
{
	template <typename T>
	class SkipWhileState : public IState<T>
	{
		private:
			IEnumerable<T> source;
			std::function<bool(const T&)> filter;
			bool done;

		public:
			SkipWhileState(IEnumerable<T> source, const std::function<bool(const T&)>& filter) 
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
				while(!done)
				{
					auto result = source.Next();
					done = !filter(result.second);
					if(done) 
						return result;
				}
				
				return source.Next();
			}
	};
	
	template <typename T>
	IEnumerable<T> IEnumerable<T>::SkipWhile(const std::function<bool(const T&)>& filter)
	{
		return IEnumerable<T>(new SkipWhileState<T>(*this, filter));
	}
}

#endif /* end of include guard: __SKIPWHILE_STATE_HPP__ */
