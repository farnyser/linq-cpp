#ifndef __ISTATE_HPP__
#define __ISTATE_HPP__

namespace linq
{
	template <typename T>
	struct IState
	{
		virtual void Init() {};
		virtual bool Valid() const noexcept { return false; }
		virtual void Advance() { throw std::out_of_range("Advance"); };
		virtual T Current() { throw std::out_of_range("Current"); };
	};
}

#endif /* end of include guard: __ISTATE_HPP__ */
