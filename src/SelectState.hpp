#ifndef __SELECT_STATE_HPP__
#define __SELECT_STATE_HPP__

namespace linq
{
	template <typename IN, typename OUT>
	class SelectState : public IState<OUT>
	{
		private:
			IEnumerable<IN> source;
			std::function<OUT(const typename std::remove_reference<IN>::type&)> transformer;
		
		public:
			SelectState(const IEnumerable<IN>& in, const std::function<OUT(const typename std::remove_reference<IN>::type&)>& transformer) 
				: source(in), transformer(transformer)
			{
			}
		
			void Init() override 
			{
				source.Init();
			}
			
			bool Valid() const noexcept override 
			{ 
				return source.Valid(); 
			}

			void Advance() override 
			{ 
				source.Advance(); 
			};
			
			OUT Current() override 
			{ 
				return transformer(source.Current()); 
			};
	};

	template <typename IN>
	template <typename F>
	auto IEnumerable<IN>::Select(const F& f)
	{
		using VALUE_IN = typename std::remove_reference<IN>::type;
		using OUT = decltype(f(VALUE_IN{}));
		return IEnumerable<OUT>(new SelectState<IN, OUT>(*this, f));
	}
}

#endif /* end of include guard: __SELECT_STATE_HPP__ */
