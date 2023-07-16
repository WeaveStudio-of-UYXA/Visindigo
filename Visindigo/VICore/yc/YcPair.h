#pragma once
namespace Yc
{
	template<class VIAPI T1,class VIAPI T2>class VIAPI pair
	{
	public:
		T1 first;
		T2 second;
		pair() = default;
		pair(const T1& a, T2& b):first(a),second(b)
		{
		}
	};
	template<class VIAPI T1, class VIAPI T2>pair<T1,T2> make_pair(T1& a, T2& b)
	{
		return (a, b);
	}
}