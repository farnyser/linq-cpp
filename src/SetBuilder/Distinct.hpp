#ifndef __SETBUILDER_DISTINCT_HPP__
#define __SETBUILDER_DISTINCT_HPP__

#include <set>

namespace linq
{
	template <typename S, typename F, typename T>
	class DistinctState : public IState<T>
	{
	private:
		S source;
		F transformer;
		std::set<decltype(transformer(source.Current()))> previous;

	public:
		DistinctState(S&& source, const F& transformer)
		: source(source), transformer(transformer)
		{
		}

		void Init() override final
		{
			source.Init();
			previous.clear();
			previous.insert(transformer(source.Current()));
		}

		bool Valid() const noexcept override final
		{
			return source.Valid();
		}

		void Advance() override final
		{
			while(true)
			{
				source.Advance();
				if(!source.Valid())
					break;

				if(previous.insert(transformer(source.Current())).second == true)
					break;
			}
		};

		T Current() const override final
		{
			return source.Current();
		};
	};
}

#endif /* end of include guard: __SETBUILDER_DISTINCT_HPP__ */
