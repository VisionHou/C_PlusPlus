#include<iostream>

using namespace std;
namespace vc
{
	//List节点类
	template<class T>
	struct  ListNode
	{
		T _data;
		ListNode<T>* _pNext;
		ListNode<T>* _pPre;

		ListNode(const T& data = T())
			:_data(data)
			, _pNext(nullptr)
			, _pPre(nullptr)
		{}
	};

	//List迭代器类封装
	template<class T,class Ref,class Ptr>
	struct __ListIterator
	{
		typedef ListNode<T> Node;
		typedef __ListIterator<T,Ref,Ptr> Self;
		Node* _node;

		//构造
		__ListIterator(Node* node)
			:_node(node)
		{}

		//重载解引用
		Ref operator*()
		{
			return _node->_data;//返回数据的引用
		}

		//重载->
		Ptr operator->()
		{
			return &_node->_data;
		}

		//重载前置++ 
		//++it it.operator++()&it
		Self operator++()
		{
			_node = _node->_pNext;
			return *this;
		}

		//重载后置++
		//it++ it.operator++(&it,0)
		Self operator++(int)
		{
			Self tmp(*this);
			_node = _node->_pNext;
			return tmp;
		}

		Self operator--()
		{
			_node = _node->_pPre;
			return *this;
		}

		Self  operator--(int)
		{
			Self tmp(*this);
			_node= _node->_pPre;
			return tmp;
		}
		
		//重载!=
		bool operator!=(const Self& it)
		{
			return _node != it._node;
		}

		//重载==(!=判定)
		bool operator==(const Self& it)
		{
			return _node != it._node;
		}
	};

	template<class T>
	class List
	{
		typedef ListNode<T> Node;
	public:

		typedef __ListIterator<T,T&,T*> iterator;
		typedef __ListIterator<T,const T&,const T*> const_iterator;


		iterator begin()
		{
			return iterator(_head->_pNext);
		}

		iterator end()
		{
			return iterator(_head->_pPre);
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_pNext);
		}

		const_iterator end() const
		{
			return const_iterator(_head->_pPre);
		}

		List()
			:_head(new Node)
		{
			_head->_pNext = _head;
			_head->_pPre = _head;
		}

		List(const List<T>& l)
		{
			_head = new Node;
			_head->_pNext = _head;
			_head->_pPre = _head;

			const iterator it = begin();
			while (it != end())
			{
				this->PushBack(*it);
				++it;
			}
		}

		List operator=(const List<T>& l)
		{
			swap(this->_head, l->_head);
			return *this;
		}

		~List()
		{
			Clear();
			delete _head;
			_head = nullptr;
		}

		void Clear()
		{
			iterator it = begin();
			while (it!=end())
			{
				iterator del = it;
				it++;
				delete del._node;
			}
			delete(it._node);

			_head->_pNext = _head;
			_head->_pPre = _head;
		}

		void PushBack(const T& x)
		{
			Node* tail = _head->_pPre;
			Node* NewNode = new Node(x);

			tail->_pNext = NewNode;
			NewNode->_pPre = tail;
			_head->_pPre = NewNode;
			NewNode->_pNext = _head;

		//	Insert(end(), x);
		}

		void PopBack()
		{
			Erase(end());
		}

		void PushFront(const T& x)
		{
			Insert(begin(), x);
		}

		void PopFront()
		{
			Erase(begin());
		}

		void Insert(iterator pos, const T& x)
		{
			 Node* prev = pos._node->_pPre;
			 Node* cur = pos._node;
			 Node* newnode = new Node(x);

			 prev->_pNext = newnode;
			 newnode->_pPre = prev;
			 newnode->_pNext = cur;
			 cur->_pPre = newnode;
		}

		iterator Erase(iterator pos)
		{
			Node* prev = pos._node->_pPre;
			Node* next = pos._node->_pNext;

			prev->_pNext = next;
			next->_pPre = prev;
			delete pos._node;

			//pos = iterator(prev);
			return iterator(next);
		}


		size_t Size()
		{
			size_t n = 0;
			iterator it = begin();
			while (it!=end())
			{
				++n;
				++it;
			}
			
			return n;
		}
		
		bool Empty()
		{
			return _head = _head->_pNext;
		}

		void PrintList(const List<int>& l)
		{
			List<int>::const_iterator it = l.begin();
			while (it != l.end())
			{
				cout << *it << " ";
				++it;
			}
			cout << *l.end() << endl;
		}
	private:
		Node* _head;
	};


	void TestList1()
	{
		List<int> l;
		l.PushBack(1);
		l.PushBack(2);
		l.PushBack(3);
		l.PushBack(4);
		l.PopBack();
		l.PrintList(l);

		List<int> l1;
		l1.PushFront(1);
		l1.PushFront(2);
		l1.PushFront(3);
		l1.PushFront(4);
		l1.PopFront();
		l1.PrintList(l1);

	}

	void TestList2()
	{
		List<int> l;
		l.PushBack(1);
		l.PushBack(2);
		l.PushBack(3);
		l.PushBack(4);
		auto pos = l.begin();
		pos++;
		l.Insert(pos, 3);
		l.PrintList(l);


		l.Erase(pos);
		l.PrintList(l);
	}
	void TestList3()
	{
		List<int> l;
		l.PushBack(1);
		l.PushBack(2);
		l.PushBack(3);
		l.PushBack(4);
		size_t size = l.Size();
		cout << size << endl;
		List<int> l1;
		l1.PushBack(1);
		l1.PushBack(2);
		l1.PushBack(3);
		l1.PushBack(4);
		l1.Clear();
		cout << l1.Size() << endl;
	}
}