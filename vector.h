#pragma once
#include <iostream>
#include <assert.h>
using namespace std;
namespace wg
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
	public:
		vector()
			:start(nullptr)
			,finish(nullptr)
			,endofstorage(nullptr)
		{}
		vector(int n, const T& data)
		{
			start = new T[n];
			for (int i = 0; i < n; ++i) {
				start[i] = data;
			}
			finish = start + n;
			endofstorage = start + n;
		}
		vector(const vector<T>& v)
		{
			size_t n = v.size();
			start = new T[n];
			for (int i = 0; i < n; ++i)
				start[i] = v[i];
			finish = start + n;
			endofstorage = start + n;
		}

		template<class Iterator>
		vector(Iterator first, Iterator last)
		{
			//求[first,last)中元素的个数
			Iterator it = first;
			size_t n = 0;
			while (it != last)
			{
				n++;
				++it;
			}

			start = new T[n];
			finish = start;
			while (first != last)
			{
				*finish = *first;
				++first;
				++finish;
			}
			endofstorage = finish;
		}

		~vector()
		{
			if (start)
			{
				delete[] start;
				start = finish = endofstorage = nullptr;
			}
		}

		/////////////////////////////////////////////////////
		//iterator-->指针
		iterator begin()
		{
			return start;
		}
		iterator end()
		{
			return finish;
		}

		//////////////////////////////////////////////////////
		//capacity
		size_t size()const
		{
			return finish - start;
		}
		size_t capacity()const
		{
			return endofstorage - start;
		}
		bool empty()const
		{
			return finish == start;
		}

		void resize(size_t newSize, const T& data = T())
		{
			size_t oldSize = size();
			if (newSize <= oldsize)
			{
				finish = start + newSize;
			}
			else
			{
				if (newSize > capacity())
					reserve(newSize);
				size_t n = newSize - oldSize;
				for (size_t i=oldSize;i<newSize;++i)
				{
					start[i] = data;
				}
				finish = start + newSize;
			}
		}
		void reserve(size_t newCapacity)
		{
			size_t oldCapacity = capacity();
			if (newCapacity > oldCapacity)
			{
				T* temp = new T[newCapacity];
				size_t n = size();
				//拷贝元素
				if (start)
				{
					for (size_t i = 0; i < n; ++i)
						temp[i] = start[i];
					delete[] start;
				}
				start = temp;
				finish = start + n;
				endofstorage = start + newCapacity;
			}
		}

		////////////////////////////////////////////////////
		//access
		T& operator[](size_t index)
		{
			assert(index < size());
			return start[index];
		}
		const T& operator[](size_t index)const
		{
			assert(index < size());
			return start[index];
		}

		T& front()
		{
			return start[0];
		}
		const T& front()const
		{
			return start[0];
		}
		T& back()
		{
			return *(finish - 1);
		}
		const T& back()const
		{
			return *(finish - 1);
		}
		
		///////////////////////////////////////////////
		//modify
		void push_back(const T& data)
		{
			Expand();
			*finish = data;
			++finish;
		}
		void pop_back()
		{
			--finish;
		}
		iterator insert(iterator pos, const T& data)
		{
			Expand();
			iterator it = end();
			while (it != pos)
			{
				*it = *(it - 1);
				--it;
			}
			*pos = data;
			++finish;
			return pos;
		}

		iterator erase(iterator pos)
		{
			iterator it = pos;
			while (it != finish)
			{
				*it = *(it + 1);
				++it;
			}
			--finish;
			return pos;
		}

		void clear()
		{
			finish = start;
		}

		void swap(vector<T>& v)
		{
			swap(start, v.start);
			swap(finish, v.finish);
			swap(endofstorage, v.endofstorage);
		}

	private:
		void Expand()
		{
			if (size() == capacity())
			{
				reserve(capacity() * 2 + 3);
			}
		}

	private:
		T* start;
		T* finish;
		T* endofstorage;
	};
}