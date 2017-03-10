#ifndef __SELECT_STATE_HPP__
#define __SELECT_STATE_HPP__

namespace linq
{
	template <typename IN, typename OUT>
	class SelectState : public IState<OUT>
	{
		private:
			IEnumerable<IN> source;
			std::function<OUT(const IN&)> transformer;
		
		public:
			SelectState(const IEnumerable<IN>& in, const std::function<OUT(const IN&)>& transformer) 
				: source(in), transformer(transformer)
			{
			}
		
			void Init() override 
			{
				source.Init();
			}
			
			std::pair<bool, OUT> Next() override 
			{
				auto result = source.Next();
				if(result.first == false)
					return std::make_pair(false, OUT{});
						
				return std::make_pair(true, transformer(result.second));
			}
	};

	template <typename IN>
	template <typename F>
	auto IEnumerable<IN>::Select(const F& f)
	{
		using OUT = decltype(f(IN{}));
		return IEnumerable<OUT>(new SelectState<IN, OUT>(*this, f));
	}
}

#endif /* end of include guard: __SELECT_STATE_HPP__ */
