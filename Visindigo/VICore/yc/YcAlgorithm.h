#pragma once
namespace Yc
{
	template<class T>void swap(T& a, T& b)
	{
		T tmp;
		tmp = a;
		a = b;
		b = tmp;
	}
}