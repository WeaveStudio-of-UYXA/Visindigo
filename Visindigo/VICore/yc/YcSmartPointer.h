#pragma once
#include<type_traits>
#include"YcAllocator.h"
#include"YcPair.h"
#include"YcAlgorithm.h"
namespace Yc
{
	template<class T>class shared_ptr;
	template<class T>requires std::is_trivial_v<T>
	class shared_ptr<T>
	{
		template<class U,class ...args>friend  shared_ptr<U> make_shared<U,args...>(args&...);
		pair<int, T>* ptr = nullptr;
	public:
		shared_ptr() = default;
		shared_ptr(const shared_ptr<T>& res)
		{
			ptr = res.ptr;
			if (ptr == nullptr)
			{
				return;
			}
			ptr->first++;
		}
		shared_ptr(shared_ptr<T>&& res)
		{
			ptr = res.ptr;
			res.ptr = nullptr;
		}
		~shared_ptr()
		{
			if (ptr != nullptr)
			{
				ptr->first--;
				if (ptr->first == 0)
				{
					allocator.YcDelete(ptr);
				}
			}
		}
		void operator=(const shared_ptr<T>& res)
		{
			if (ptr != nullptr)
			{
				ptr->first--;
				if (ptr->first == 0)
				{
					allocator.YcDelete(ptr);
				}
			}
			ptr = res.ptr;
			ptr->first++;
		}
		void operator=(shared_ptr<T>&& res)
		{
			if (ptr != nullptr)
			{
				ptr->first--;
				if (ptr->first == 0)
				{
					allocator.YcDelete(ptr);
				}
			}
			ptr = res.ptr;
			res.ptr = nullptr;
		}
		void reset(const shared_ptr<T>& res)
		{
			if (ptr != nullptr)
			{
				ptr->first--;
				if (ptr->first == 0)
				{
					allocator.YcDelete(ptr);
				}
			}
			ptr = res.ptr;
			ptr->first++;
		}
		void reset(shared_ptr<T>&& res)
		{
			if (ptr != nullptr)
			{
				ptr->first--;
				if (ptr->first == 0)
				{
					allocator.YcDelete(ptr);
				}
			}
			ptr = res.ptr;
			res.ptr = nullptr;
		}
		bool operator==(const shared_ptr<T>& res)const
		{
			return ptr == res.ptr;
		}
		int use_count()const
		{
			return ptr->first;
		}
		T* operator->()const
		{
			return &(ptr->second);
		}
		T& operator* ()const
		{
			return ptr->second;
		}
		operator T* ()const
		{
			return &(ptr->second);
		}
	};
	template<class T>requires (!std::is_trivial_v<T>)
		class shared_ptr<T>
	{
		class ct :public pair<int, T*>
		{
		public:
			~ct()
			{
				allocator.YcDelete(this->second);
			}
		};
		template<class U, class ...args>friend  shared_ptr<U> make_shared<U, args...>(args&...);
		ct* ptr = nullptr;
	public:
		shared_ptr() = default;
		shared_ptr(const shared_ptr<T>& res)
		{
			ptr = res.ptr;
			if (ptr == nullptr)
			{
				return;
			}
			ptr->first++;
		}
		shared_ptr(shared_ptr<T>&& res)
		{
			ptr = res.ptr;
			res.ptr = nullptr;
		}
		~shared_ptr()
		{
			if (ptr != nullptr)
			{
				ptr->first--;
				if (ptr->first == 0)
				{
					allocator.YcDelete(ptr);
				}
			}
		}
		void operator=(const shared_ptr<T>& res)
		{
			if (ptr != nullptr)
			{
				ptr->first--;
				if (ptr->first == 0)
				{
					allocator.YcDelete(ptr);
				}
			}
			ptr = res.ptr;
			ptr->first++;
		}
		void operator=(shared_ptr<T>&& res)
		{
			if (ptr != nullptr)
			{
				ptr->first--;
				if (ptr->first == 0)
				{
					allocator.YcDelete(ptr);
				}
			}
			ptr = res.ptr;
			res.ptr = nullptr;
		}
		void reset(const shared_ptr<T>& res)
		{
			if (ptr != nullptr)
			{
				ptr->first--;
				if (ptr->first == 0)
				{
					allocator.YcDelete(ptr);
				}
			}
			ptr = res.ptr;
			ptr->first++;
		}
		void reset(shared_ptr<T>&& res)
		{
			if (ptr != nullptr)
			{
				ptr->first--;
				if (ptr->first == 0)
				{
					allocator.YcDelete(ptr);
				}
			}
			ptr = res.ptr;
			res.ptr = nullptr;
		}
		bool operator==(const shared_ptr<T>& res)const
		{
			return ptr == res.ptr;
		}
		int use_count()const
		{
			return ptr->first;
		}
		T* operator->()const
		{
			return &(ptr->second);
		}
		T& operator* ()const
		{
			return ptr->second;
		}
		operator T* ()const
		{
			return &(ptr->second);
		}
	};
	template<class T, class... args>requires std::is_trivial_v<T>
	shared_ptr<T> make_shared(args&... a)
	{
		shared_ptr<T>m;
		m.ptr = allocator.YcNew<pair<int, T>>();
		m.ptr->first = 1;
		new(m.ptr->second)T(a...);
		return m;
	}
	template<class T,class... args>requires (!std::is_trivial_v<T>)
	shared_ptr<T> make_shared(args&... a)
	{
		shared_ptr<T>m;
		m.ptr = allocator.YcNew<typename shared_ptr<T>::ct>();
		m.ptr->first = 1;
		m.ptr->second = allocator.YcNew<T>(a...);
		return m;
	}
	template<class T>class unique_ptr
	{
		T* ptr = nullptr;
		template<class R, class... args>friend unique_ptr<R> make_unique<R, args>(args&...);
		template<class R>friend void swap(unique_ptr<R>& a, unique_ptr<R>& b);
	public:
		T* operator->()
		{
			return ptr;
		}
		T& operator*()
		{
			return *ptr;
		}
		unique_ptr() = default;
		unique_ptr(const unique_ptr<T>&) = delete;
		unique_ptr(unique_ptr<T>&& res)
		{
			ptr = res.ptr;
			res.ptr = nullptr;
		}
		unique_ptr(T* ptr)
		{
			this->ptr = ptr;
		}
		~unique_ptr()
		{
			allocator.YcDelete(ptr);
		}
		void operator=(const unique_ptr<T>&) = delete;
		void operator=(unique_ptr<T>&& res)
		{
			allocator.YcDelete(ptr);
			ptr = res.ptr;
			res.ptr = nullptr;
		}
		T* release()
		{
			T* res = ptr;
			ptr = nullptr;
			return res;
		}
	};
	template<class T, class... args>unique_ptr<T>make_unique(args&... arg)
	{
		return allocator.YcNew<T>(arg...);
	}
	template<class T>void swap(unique_ptr<T>& a, unique_ptr<T>& b)
	{
		swap(a.ptr, b.ptr);
	}
}