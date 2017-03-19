#ifndef __GROUPBY_STATE_HPP__
#define __GROUPBY_STATE_HPP__

#include <map>

namespace linq
{
	template <typename KEY, typename VALUE>
	struct IGrouping : IEnumerable<VALUE>
	{
		KEY Key;
		
		IGrouping(KEY key, IState<VALUE>* state) : Key(key), IEnumerable<VALUE>(state) {};
		IGrouping(KEY key, std::shared_ptr<IState<VALUE>> state) : Key(key), IEnumerable<VALUE>(state) {};
		IGrouping() : IEnumerable<VALUE>(nullptr) {};
	};
	
	template <typename S, typename KEY, typename VALUE>
	class GroupByState : public IState<IGrouping<KEY, VALUE&>>
	{
		private:
			using OUT = IGrouping<KEY, VALUE&>;
			S source;
			std::function<KEY(const VALUE&)> transformer;
			std::map<KEY, std::vector<VALUE>> result;
			typename std::map<KEY, std::vector<VALUE>>::iterator current;
		
		public:
			GroupByState(S&& in, const std::function<KEY(const VALUE&)>& transformer) 
				: source(in), transformer(transformer)
			{
			}
		
			void Init() override 
			{
				source.Init();
				result.clear();
				
				for(const auto& x : source)
					result[transformer(x)].push_back(x);
				
				current = result.begin();
			}
			
			bool Valid() const noexcept override 
			{ 
				return current != result.end(); 
			}
			
			void Advance() override 
			{ 
				++current; 
			};
			
			OUT Current() const override 
			{ 
				decltype(auto) adapted = Adapt(current->second);
				decltype(auto) enumerable = (IEnumerable<VALUE&>)(adapted);
				return OUT{current->first, enumerable.state}; 
			};
	};
}

#endif /* end of include guard: __GROUPBY_STATE_HPP__ */
