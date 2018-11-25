#pragma once
#include <iostream>
#include <stdio.h>
#include<assert.h>
#include <algorithm>

using namespace std;

namespace vc
{
	template<class T>
	class Vector
	{
	public:
		typedef T* Iterator;
		typedef const T* ConstIterator;

		Iterator begin() const
		{
			return _start;
		}

		Iterator end() const
		{
			return _finish;
		}

		ConstIterator Cbegin() const
		{
			return _start;
		}

		ConstIterator Cend() const
		{
			return _finish;
		}

		size_t Size() const
		{
			return _finish - _start;
		}

		size_t Capacity() const
		{
			return _endofstorage - _start;
		}

		T& operator[](size_t pos)
		{

			return _start[pos];
		}

		const T& operator[](size_t pos) const
		{
			return _start[pos];
		}

		//����
		Vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{}
			
		//����n��val
		Vector(size_t n, const T& val = T())
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			Reserve(n);
			while (n--)
			{
				PushBack(val);
			}
		}

		//���������乹��
		//template<class InputIterator>
		Vector(Iterator first, Iterator last)
		{
			Reserve(last - first);
			Iterator begin = first;
			while (begin != last)
			{
				PushBack(*begin);
				++begin;
			}
		}

		//��������
		Vector(const Vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			Reserve(v.Capacity());
			Iterator it = begin();
			ConstIterator vit = v.Cbegin();//this
			while (vit != v.Cend())
			{
				*it++ = *vit++;
			}

			_finish = _start + v.Size();
			_endofstorage = _start + v.Capacity();
		}

		~Vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _endofstorage = nullptr;
			}
		}

		void Reserve(size_t n)
		{
			if (n > Capacity())
			{
				size_t size = Size();
				T* tmp = new T[n];
				if (_start)
				{
					for (size_t i = 0; i < size; ++i)
					{
						tmp[i] = _start[i];
					}
				}

				_start = tmp;
				_finish = _start + size;
				_endofstorage = _start + n;

			}
		}

		void Resize(size_t n, const T& val = T())
		{
			//nС��size������_finish
			if (n < Size())
			{	_finish = _start + n;
				return;
			}

			//�ռ䲻������
			if (n > Capacity())
			{
				Reserve(n);
			}

			//����size
			Iterator begin = _finish;
			_finish = _start + n;

			while (begin != _finish)
			{
				*begin = val;
				begin++;
			}
		}

		Vector<T>& operator=(Vector<T> v)
		{
			Swap(v);
			return *this;
		}
		void Swap(Vector<T>& v)
		{
			swap(_start, v._start);
			swap(_finish, v._finish);
			swap(_endofstorage, v._endofstorage);
		}

		void PushBack(const T& x)
		{
			Insert(end(), x);
		}

		void PopBack()
		{
			Erase(end()-1);
		}

		Iterator Insert(Iterator pos, const T& x)
		{
			assert(pos <= _finish);
			//�Ƿ�Ҫ����
			if (_finish == _endofstorage)
			{
				size_t size = Size();
				size_t newCapacity = 0 == Capacity() ? 1 : 2 * Capacity();
				Reserve(newCapacity);
				//����pos
				pos = _start + size;
			}

			Iterator begin = _finish - 1;
			while (begin >= pos)
			{
				*(begin+1) = *begin;
				--begin;
			}
			*pos = x;
			++_finish;
			return pos;
		}

		Iterator Erase(Iterator pos)
		{
			assert(pos < _finish);
			//����ɾ��
			Iterator begin = pos+1;
			while (begin<_finish)
			{
				*(begin - 1) = *begin;
				++begin;
			}
			--_finish;

			//����ɾ�����ݵ���һ��λ��
			//��ֹ������ʧЧ
			return pos;
		}

	private:
		Iterator _start;//��Ч���ݿ�ʼ
		Iterator _finish;//��Ч���ݽ�β
		Iterator _endofstorage;//������β
	};
}