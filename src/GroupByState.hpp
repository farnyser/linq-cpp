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
	
	template <typename KEY, typename VALUE>
	class GroupByState : public IState<IGrouping<KEY, VALUE>>
	{
		private:
			using OUT = IGrouping<KEY, VALUE>;
			IEnumerable<VALUE> source;
			std::function<KEY(const VALUE&)> transformer;
			std::map<KEY, std::vector<VALUE>> result;
			typename std::map<KEY, std::vector<VALUE>>::iterator current;
		
		public:
			GroupByState(const IEnumerable<VALUE>& in, const std::function<KEY(const VALUE&)>& transformer) 
				: source(in), transformer(transformer)
			{
			}
		
			void Init() override 
			{
				source.Init();
				result.clear();
				
				for(auto& x : source)
					result[transformer(x)].push_back(x);
				
				current = result.begin();
			}
			
			std::pair<bool, OUT> Next() override 
			{
				if(current != result.end()) {
					auto it = current++;
					return std::make_pair(true, OUT{it->first, Adapt(it->second).state});
				}
				
				return std::make_pair(false, OUT{});
			}
	};

	template <typename VALUE>
	template <typename F>
	auto IEnumerable<VALUE>::GroupBy(const F& f)
	{
		using KEY = decltype(f(VALUE{}));
		return IEnumerable<IGrouping<KEY,VALUE>>(new GroupByState<KEY, VALUE>(*this, f));
	}
}

#endif /* end of include guard: __GROUPBY_STATE_HPP__ */
