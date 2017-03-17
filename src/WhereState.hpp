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
				
				while(source.Valid())
				{
					if(filter(source.Current()))
						break;
					source.Advance();
				}
			}
				
			bool Valid() const noexcept override 
			{ 
				return source.Valid(); 
			}

			void Advance() override 
			{
				source.Advance();
				
				while(source.Valid())
				{
					if(filter(source.Current()))
						break;
					
					source.Advance();
				}
			};
			
			T Current() override 
			{ 
				return source.Current(); 
			};
	};
	
	template <typename T>
	IEnumerable<T> IEnumerable<T>::Where(std::function<bool(const T&)> where)
	{
		return IEnumerable<T>(new WhereState<T>(*this, where));
	}
}

#endif /* end of include guard: __WHERE_STATE_HPP__ */
