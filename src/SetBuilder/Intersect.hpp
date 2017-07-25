#ifndef __SETBUILDER_INTERSECT_HPP__
#define __SETBUILDER_INTERSECT_HPP__

namespace linq
{
	template <typename S1, typename S2, typename F, typename T>
	class IntersectState : public IState<T>
	{
	private:
		F transformer;
		S1 source1;
		S2 source2;
		std::set<decltype(transformer(source1.Current()))> filter;

	public:
		IntersectState(S1&& in1, S2&& in2, const F& transformer)
		: source1(in1), source2(in2), transformer(transformer)
		{
		}

		void Init() override final
		{
			for(source1.Init() ; source1.Valid() ; source1.Advance())
				filter.insert(transformer(source1.Current()));
			for(source2.Init() ; source2.Valid() ; source2.Advance())
				if(filter.find(transformer(source2.Current())) != filter.end())
				{
					filter.erase(transformer(source2.Current()));
					break;
				}
		}

		bool Valid() const noexcept override final
		{
			return source2.Valid();
		}

		void Advance() override final
		{
			for(source2.Advance() ; source2.Valid() ; source2.Advance())
			{
				auto it = filter.find(transformer(source2.Current()));
				if(it != filter.end())
				{
					filter.erase(it);
					break;
				}
			}
		};

		T Current() const override final
		{
			return source2.Current();
		};
	};
}

#endif /* end of include guard: __SETBUILDER_INTERSECT_HPP__ */
