#ifndef __SETBUILDER_EXCEPT_HPP__
#define __SETBUILDER_EXCEPT_HPP__

namespace linq
{
	template <typename S1, typename S2, typename F, typename T>
	class ExceptState : public IState<T>
	{
	private:
		F transformer;
		S1 source1;
		S2 source2;
		std::set<decltype(transformer(source2.Current()))> filter;

	public:
		ExceptState(S1&& in1, S2&& in2, const F& transformer)
		: source1(in1), source2(in2), transformer(transformer)
		{
		}

		void Init() override final
		{
			for(source2.Init() ; source2.Valid() ; source2.Advance())
				filter.insert(transformer(source2.Current()));
			for(source1.Init() ; source1.Valid() ; source1.Advance())
				if(filter.find(transformer(source1.Current())) == filter.end())
					break;
		}

		bool Valid() const noexcept override final
		{
			return source1.Valid();
		}

		void Advance() override final
		{
			for(source1.Advance() ; source1.Valid() ; source1.Advance())
			{
				auto it = filter.find(transformer(source1.Current()));
				if(it == filter.end())
					return;
			}
		};

		T Current() const override final
		{
			return source1.Current();
		};
	};
}

#endif /* end of include guard: __SETBUILDER_EXCEPT_HPP__ */
