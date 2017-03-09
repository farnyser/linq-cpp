#ifndef __ISTATE_HPP__
#define __ISTATE_HPP__

namespace linq
{
	template <typename T>
	struct IState
	{
		virtual void Init() {};
		virtual bool Next(T&) { return false; };
	};
}

#endif /* end of include guard: __ISTATE_HPP__ */
