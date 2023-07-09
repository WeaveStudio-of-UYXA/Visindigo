#pragma once
namespace Yc
{
	template<class T1,class T2>class pair
	{
	public:
		T1 first;
		T2 second;
		pair() = default;
		pair(const T1& a, T2& b):first(a),second(b)
		{
		}
	};
	template<class T1, class T2>pair<T1,T2> make_pair(T1& a, T2& b)
	{
		return (a, b);
	}
}