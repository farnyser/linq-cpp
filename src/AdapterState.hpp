#ifndef __ADAPTER_STATE_HPP__
#define __ADAPTER_STATE_HPP__

namespace linq
{
	template <typename T, typename X>
	struct AdapterState : IState<T>
	{
		X source;
		typename X::iterator current;
		
		AdapterState(X source) : source(source) {}
		
		void Init() override { current = source.begin(); }
		
		bool Next(T& out) override 
		{ 
			if(current == source.end()) 
				return false;
			
			out = *current;
			++current;
			
			return true;
		}
	};

	template <typename X>
	IEnumerable<typename std::iterator_traits<typename X::iterator>::value_type> Adapt(X source) 
	{
		IEnumerable<typename std::iterator_traits<typename X::iterator>::value_type> result(
			new AdapterState<typename std::iterator_traits<typename X::iterator>::value_type, X>(source)
		);
		
		return result;
	};
}

#endif /* end of include guard: __ADAPTER_STATE_HPP__ */
