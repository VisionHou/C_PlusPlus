#pragma once
#include<iostream>
using namespace std;
enum Color
{
	RED,
	BLACK,
};

template<class K,class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	
	K _key;
	V _value;

	Color _color;

	RBTreeNode(const K& key,const V& value)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_key(key)
		,_value(value)
	{}
};



template<class K,class V>
class RBTree
{
public:
	typedef RBTreeNode<K, V> Node;
	RBTree()
	{}

	~RBTree()
	{}

	bool insert(const K& key, const V& value)
	{
		//搜索树方式插入
		if (_root == nullptr)
		{
			_root = new Node(key, value);
			_root->_color = BLACK;
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;

		}

		cur = new Node(key, value);
		cur->_color = RED;
		if (key < parent->_key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		//调整
		while (parent&&parent->_color == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				//情况一叔叔存在且为红
				if (uncle&&uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}

				//情况二:叔叔不存在或为黑
				else
				{
					
					//是右孩子双旋左孩子单旋
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(parent, cur);
					}
					parent->_color = BLACK;
					grandfather->_color = RED;
					RotateR(grandfather);
					break;
				}
			}
			else//(parent == grandfather->_right)
			{
				Node* uncle = grandfather->_left;
				if (uncle&&uncle->_color == RED)
				{
					//叔叔存在且为红
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else//不存在或为黑
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(parent, cur);
					}
					parent->_color = BLACK;
					grandfather->_color = RED;
					RotateL(grandfather);
					break;
				}
			}
		}
		_root->_color = BLACK;
		return true;
	}

	//右单旋
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* SubRL = subL->_right;

		parent->_left = SubRL;
		if (SubRL)
			SubRL->_parent = parent;

		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		if (parent == _root)

		{
			_root = subL;
		}
		else
		{
			if (parent == ppNode->_left)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
		}
		subL->_parent = ppNode;
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		if (parent == _root)
		{
			_root = subR;
			_root->_parent = nullptr;
		}
		else
		{
			if (parent == ppNode->_left)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;
			subR->_parent = ppNode;
		}

	}

	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}
	void _Inorder(Node* root)
	{
		if (root == nullptr)
			return;
		_Inorder(root->_left);
		cout << root->_key << " ";
		_Inorder(root->_right);
	}
private:
	Node* _root;
};

void Test()
{
	int a[] = { 4,2,6,1,3,5,15,7,16,14 };
	RBTree<int, int> t;
	for (auto e : a)
	{
		t.insert(e, e);
	}

	t.Inorder();

}













