#include <xkeycheck.h>
#pragma once
template<class T>concept largeClass = (sizeof(T) > 128);
template<class T>concept smallClass = (sizeof(T) <= 128&&sizeof(T)>0);
namespace Yc
{
	class Allocator
	{
		char* memPoolBeginPtr = nullptr;
		char* memPoolEndPtr = nullptr;
		char** memList[16] = {};
		inline bool poolEmpty()
		{
			return memPoolBeginPtr == memPoolEndPtr;
		}
		inline int poolSize()
		{
			return memPoolEndPtr - memPoolBeginPtr;
		}
		constexpr static int index(size_t n)
		{
			return (n - 1) / 8;
		}
		constexpr static int sizeUp(int n)
		{
			return (index(n) + 1) * 8;
		}
	public:
		Allocator() = default;
		~Allocator() = default;
		template<largeClass T, class... args>T* YcNew(args& ...a)
		{
			T* result=(T*)malloc(sizeUp(sizeof(T)));
			new(result)T(a...);
			return result;
		};
		template<smallClass T, class... args>T* YcNew(args& ...a)
		{
			constexpr int n = index(sizeof(T));
			if (memList[n] != nullptr)
			{
				T* result = (T*)memList[n];
				memList[n] = (char**)*memList[n];
				new(result)T(a...);
				return result;
			}
			constexpr int s = sizeUp(sizeof(T));
			if (poolSize() < s)
			{
				if (!poolEmpty())
				{
					*(char**)memPoolBeginPtr = (char*)memList[index(poolSize())];
					memList[index(poolSize())]=(char**)memPoolBeginPtr;
					memPoolBeginPtr = memPoolEndPtr;
				}
				memPoolBeginPtr = (char*)malloc(s * 40);
				memPoolEndPtr = memPoolBeginPtr + s * 40;
			}
			T* result = (T*)memPoolBeginPtr;
			memPoolBeginPtr += s;
			int c = 0;
			char* tmp = memPoolBeginPtr;
			while (poolSize()>=s&&c<19)
			{
				*(char**)memPoolBeginPtr = memPoolBeginPtr + s;
				memPoolBeginPtr += s;
				c++;
			}
			*(char**)(memPoolBeginPtr-s) = (char*)memList[n];
			memList[n] = (char**)tmp;
			new(result)T(a...);
			return result;
		}
		template<largeClass T>void YcDelete(T* ptr)
		{
			if (ptr == nullptr)
			{
				return;
			}
			ptr->~T();
			if (poolSize() <= 128)
			{
				if (!poolEmpty())
				{
					*(char**)memPoolBeginPtr = memList[index(poolSize())];
					memList[index(poolSize())] = memPoolBeginPtr;
					memPoolBeginPtr = memPoolEndPtr;
				}
				memPoolBeginPtr = ptr;
				memPoolEndPtr = memPoolBeginPtr + sizeUp(sizeof(T));
				return;
			}
			free(ptr);
		}
		template<smallClass T>void YcDelete(T* ptr)
		{
			if (ptr == nullptr)
			{
				return;
			}
			ptr->~T();
			*(char**)ptr = (char*)memList[index(sizeof(T))];
			memList[index(sizeof(T))] = (char**)ptr;
		}
	}allocator;

};