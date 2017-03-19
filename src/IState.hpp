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
		virtual T Current() const { throw std::out_of_range("Current"); };
		
		IState* operator->() { return this; }
		const IState* operator->() const { return this; }
	};
}

#endif /* end of include guard: __ISTATE_HPP__ */
