#ifndef __SETBUILDER_CONCAT_HPP__
#define __SETBUILDER_CONCAT_HPP__

namespace linq
{
	template <typename S1, typename S2, typename T>
	class ConcatState : public IState<T>
	{
	private:
		bool s1;

	public: // unsafe
		S1 source1;
		S2 source2;

	public:
		ConcatState(S1&& in1, S2&& in2)
		: source1(in1), source2(in2)
		{
		}

		void Init() override final
		{
			source1.Init();
			source2.Init();
			s1 = source1.Valid();
		}

		bool Valid() const noexcept override final
		{
			return s1 || !s1&&source2.Valid();
		}

		void Advance() override final
		{
			if(s1){
				source1.Advance();
				if(!source1.Valid())
					s1 = false;
			}
			else
				source2.Advance();
		};

		T Current() const override final
		{
			return s1 ? source1.Current() : source2.Current();
		};
	};

	template <typename S1, typename S2,typename T, typename F>
	auto Sum(ConcatState<S1, S2, T>&& source, const F& fct)
	{
		return Sum(std::move(source.source1), fct) + Sum(std::move(source.source2), fct);
	}
}

#endif /* end of include guard: __SETBUILDER_CONCAT_HPP__ */
