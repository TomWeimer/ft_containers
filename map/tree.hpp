#ifndef BLACK_RED_TREE_HPP
#define BLACK_RED_TREE_HPP

#include "node.hpp"
#include "../utils/utility.hpp"
#include "../utils/ft_nullptr.hpp"
#include "node.hpp"
#include <memory>
#include <iostream>

#define BLACKREDCLASS BlackRed_Tree<T, Compare, Allocator>

#define RED 1
#define BLACK 0

namespace ft
{

	template <class T, class Compare, class Allocator = std::allocator<Node<T> > >
	class BlackRed_Tree
	{
	public:
		typedef T pair_type;
		typedef typename pair_type::first_type key_type;
		typedef typename pair_type::second_type value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef Compare compare_type;
		typedef Node<pair_type> node_type;
		typedef node_type *node_pointer;
		typedef node_type &node_reference;

	private:
		node_pointer _root;
		node_pointer _TNULL;
		compare_type _comp;
		size_type _size;
		allocator_type _alloc;

	public:
		// Constructors, operator=, destructor
		BlackRed_Tree();
		BlackRed_Tree(const BlackRed_Tree &other);
		BlackRed_Tree &operator=(const BlackRed_Tree &other);
		~BlackRed_Tree();

		// modifiers
		void insert(const pair_type &);
		void insert(const pair_type &newData, node_pointer pos);
		void clear(void);
		void erase(key_type key);
		void swap(BlackRed_Tree &other);

		// Setter
		void set_root(node_pointer data);

		// Capacity
		bool is_empty() const;
		size_type get_size() const;
		size_type get_max_size() const;

		// Lookups
		node_pointer find(const pair_type value) const;
		node_pointer find(key_type key) const;
		node_pointer minimum(node_pointer node) const;
		node_pointer maximum(node_pointer node) const;
		node_pointer successor(node_pointer x) const;
		node_pointer predecessor(node_pointer x) const;
		node_pointer get_root(void) const;
		node_pointer get_last(void) const;

		// printer
		void printTree() const;
		void inorder() const;
		void postorder() const;
		void preorder() const;

	private:
		node_pointer _create_node(void);
		node_pointer _create_node(const pair_type &newData);
		node_pointer _create_node(const node_pointer node);
		node_pointer _find(node_pointer node, key_type key) const;
		node_pointer _copyNode(node_pointer node, node_pointer parent);
		void _insertFix(node_pointer node);
		void _deleteFix(node_pointer x);
		void _deleteNode(node_pointer node, key_type key);
		void _deleteTree(node_pointer node);
		void _print(node_pointer _root, std::string indent, bool last) const;
		void _inorder(node_pointer node) const;
		void _preorder(node_pointer node) const;
		void _postorder(node_pointer node) const;
		void _left_rotation(node_pointer x);
		void _right_rotation(node_pointer x);
		void _rbTransplant(node_pointer u, node_pointer v);
		void _copyTree(const BlackRed_Tree &other);
	};

	// Allocate memory for a new Node
	template <class T, class Compare, class Allocator>
	typename BLACKREDCLASS::node_pointer BLACKREDCLASS::_create_node(void)
	{
		node_pointer newNode = _alloc.allocate(1);
		return (newNode);
	}

	// Allocate memory for a new Node
	template <class T, class Compare, class Allocator>
	typename BLACKREDCLASS::node_pointer BLACKREDCLASS::_create_node(const node_pointer node)
	{
		node_pointer newNode = _alloc.allocate(1);
		this->_alloc.construct(newNode, node);
		return (newNode);
	}

	// Allocate memory for a new Node
	template <class T, class Compare, class Allocator>
	typename BLACKREDCLASS::node_pointer BLACKREDCLASS::_create_node(const pair_type &newData)
	{
		node_pointer newNode = _alloc.allocate(1);
		this->_alloc.construct(newNode, newData);
		return (newNode);
	}

	// Constructor
	template <class T, class Compare, class Allocator>
	BLACKREDCLASS::BlackRed_Tree() : _size(0)
	{
		this->_TNULL = _create_node();
		this->_TNULL->color = BLACK;
		this->_TNULL->NIL = true;
		this->_root = this->_TNULL;
	}

	// Constructor
	template <class T, class Compare, class Allocator>
	BLACKREDCLASS::BlackRed_Tree(const BlackRed_Tree &other)
	{
		this->clear();
		this->_size = other.get_size();
		this->_comp = other._comp;
		this->_alloc = other._alloc;
		_copyTree(other);
	}

	// operator =
	template <class T, class Compare, class Allocator>
	BLACKREDCLASS &BLACKREDCLASS::operator=(const BlackRed_Tree &other)
	{
		if (*this == other)
			return *this;
		this->clear();
		this->_copyTree(other);
		this->_size = other.get_size();
		return (*this);
	}

	// destructor
	template <class T, class Compare, class Allocator>
	BLACKREDCLASS::~BlackRed_Tree()
	{
		clear();
		this->_alloc.deallocate(_TNULL, 1);
	}

	// swap contents
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::swap(BlackRed_Tree &other)
	{

		std::swap(this->_root, other._root);
		std::swap(this->_TNULL, other._TNULL);
		std::swap(this->_comp, other._comp);
		std::swap(this->_size, other._size);
		std::swap(this->_alloc, other._alloc);
	}

	// copy a node
	template <class T, class Compare, class Allocator>
	typename BLACKREDCLASS::node_pointer BLACKREDCLASS::_copyNode(node_pointer node, node_pointer parent)
	{
		if (node == ft_nullptr)
			return (_TNULL);
		node_pointer nodeCopy = _create_node(node);
		nodeCopy->parent = parent;
		nodeCopy->left = _copyNode(node->left, nodeCopy);
		nodeCopy->right = _copyNode(node->right, nodeCopy);
		return (nodeCopy);
	}

	// copy a tree
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::_copyTree(const BlackRed_Tree &other)
	{
		_TNULL = other._TNULL;
		_size = other._size;
		this->_root = _copyNode(other._root, ft_nullptr);
	}

	// delete a tree
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::_deleteTree(node_pointer node)
	{
		if (node == ft_nullptr || node == this->_TNULL)
			return;
		if (node->left != ft_nullptr && node->left != this->_TNULL)
			_deleteTree(node->left);
		if (node->right != ft_nullptr && node->right != this->_TNULL)
			_deleteTree(node->right);
		this->_alloc.deallocate(node, 1);
		return;
	}

	// deallocate memory from the tree
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::clear(void)
	{
		_deleteTree(this->_root);
		this->_size = 0;
	}

	// In rotation operation, the positions of the nodes of a subtree are interchanged.
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::_left_rotation(node_pointer x)
	{
		node_pointer y = x->right;
		x->right = y->left;
		if (y->left != _TNULL)
			y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == ft_nullptr)
		{
			this->_root = y;
			_TNULL->root = _root;
		}
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	// In rotation operation, the positions of the nodes of a subtree are interchanged.
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::_right_rotation(node_pointer x)
	{
		node_pointer y = x->left;
		x->left = y->right;
		if (y->right != _TNULL)
			y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == ft_nullptr)
		{
			this->_root = y;
			_TNULL->root = _root;
		}
		else if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}

	// insert a new element in the tree and then called _insertFix()
	// to keep the propreties of a red black tree
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::insert(const pair_type &newData)
	{

		node_pointer actual = this->_root;
		node_pointer prev = ft_nullptr;
		node_pointer newNode = _create_node(newData);

		newNode->left = _TNULL;
		newNode->right = _TNULL;
		newNode->color = RED;
		this->_size++;
		while (actual != ft_nullptr && actual != _TNULL)
		{
			prev = actual;
			if (_comp(newNode->data.first, actual->data.first))
				actual = actual->left;
			else
				actual = actual->right;
		}
		newNode->parent = prev;
		if (prev == ft_nullptr)
		{
			this->_root = newNode;
			_TNULL->root = _root;
		}
		else if (_comp(newNode->data.first, prev->data.first))
			prev->left = newNode;
		else
			prev->right = newNode;
		if (newNode->parent == ft_nullptr)
		{
			newNode->color = BLACK;
			return;
		}
		if (newNode->parent->parent == ft_nullptr)
			return;
		_insertFix(newNode);
	}

	// insert a new element in the tree and then called _insertFix()
	// to keep the propreties of a red black tree
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::insert(const pair_type &newData, node_pointer pos)
	{
		node_pointer actual = pos;
		node_pointer prev = ft_nullptr;
		node_pointer newNode = _create_node(newData);

		this->_size++;
		newNode->left = _TNULL;
		newNode->right = _TNULL;
		newNode->color = RED;
		while (actual != _TNULL)
		{
			prev = actual;
			if (_comp(newNode->data.first, actual->data.first))
				actual = actual->left;
			else
				actual = actual->right;
		}
		newNode->parent = prev;
		if (prev == ft_nullptr)
		{
			this->_root = newNode;
			_TNULL->root = _root;
		}
		else if (_comp(newNode->data.first, prev->data.first))
			prev->left = newNode;
		else
			prev->right = newNode;
		if (newNode->parent == ft_nullptr)
		{
			newNode->color = BLACK;
			return;
		}
		if (newNode->parent->parent == ft_nullptr)
			return;
		_insertFix(newNode);
	}

	// Check and modify the position of the element in the tree to respect
	// the propreties of a red black tree
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::_insertFix(node_pointer node)
	{
		node_pointer u;

		while (node->parent->color == RED)
		{
			if (node->parent == node->parent->parent->right)
			{
				u = node->parent->parent->left;
				if (u->color == RED)
				{
					u->color = BLACK;
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					node = node->parent->parent;
				}
				else
				{
					if (node == node->parent->left)
					{
						node = node->parent;
						_right_rotation(node);
					}
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					_left_rotation(node->parent->parent);
				}
			}
			else
			{
				u = node->parent->parent->right;
				if (u->color == RED)
				{
					u->color = BLACK;
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					node = node->parent->parent;
				}
				else
				{
					if (node == node->parent->right)
					{
						node = node->parent;
						_left_rotation(node);
					}
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					_right_rotation(node->parent->parent);
				}
			}
			if (node == this->_root)
				break;
		}
		this->_root->color = BLACK;
	}

	// delete an element of the tree and then call _deleteFix() to
	// keep the propreties of a red black tree
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::_deleteNode(node_pointer node, key_type key)
	{

		node_pointer z = _TNULL;
		node_pointer x;
		node_pointer y;

		this->_size--;
		while (node != _TNULL)
		{

			if (node->data.first == key)
				z = node;
			if (node->data.first <= key)
				node = node->right;
			else
				node = node->left;
		}
		if (z == _TNULL)
		{
			std::cout << "Key not found in the tree" << std::endl;
			return;
		}
		y = z;
		int y_original_color = y->color;
		if (z->left == _TNULL)
		{
			x = z->right;
			_rbTransplant(z, z->right);
		}
		else if (z->right == _TNULL)
		{
			x = z->left;
			_rbTransplant(z, z->left);
		}
		else
		{
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z)
				x->parent = y;
			else
			{
				_rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			_rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		this->_alloc.deallocate(z, 1);
		if (y_original_color == BLACK)
			_deleteFix(x);
	}

	// Check and modify the position of the element in the tree to respect
	// the propreties of a red black tree
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::_deleteFix(node_pointer x)
	{
		node_pointer s;
		while (x != _root && x->color == BLACK)
		{
			if (x == x->parent->left)
			{
				s = x->parent->right;
				if (s->color == RED)
				{
					s->color = BLACK;
					x->parent->color = RED;
					_left_rotation(x->parent);
					s = x->parent->right;
				}
				if (s->left->color == BLACK && s->right->color == BLACK)
				{
					s->color = RED;
					x = x->parent;
				}
				else
				{
					if (s->right->color == BLACK)
					{
						s->left->color = BLACK;
						s->color = RED;
						_right_rotation(s);
						s = x->parent->right;
					}
					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->right->color = BLACK;
					_left_rotation(x->parent);
					x = this->_root;
				}
			}
			else
			{
				s = x->parent->left;
				if (s->color == RED)
				{
					s->color = BLACK;
					x->parent->color = RED;
					_right_rotation(x->parent);
					s = x->parent->left;
				}
				if (s->right->color == BLACK && s->right->color == BLACK)
				{
					s->color = RED;
					x = x->parent;
				}
				else
				{
					if (s->left->color == BLACK)
					{
						s->right->color = BLACK;
						s->color = RED;
						_left_rotation(s);
						s = x->parent->left;
					}
					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->left->color = BLACK;
					_right_rotation(x->parent);
					x = _root;
				}
			}
		}
		x->color = BLACK;
	}

	// transplant two node
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::_rbTransplant(node_pointer u, node_pointer v)
	{
		if (u->parent == ft_nullptr)
		{
			_root = v;
			_TNULL->root = _root;
		}
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

	// advance the node to the smallest element of the branch
	template <class T, class Compare, class Allocator>
	typename BLACKREDCLASS::node_pointer BLACKREDCLASS::minimum(node_pointer node) const
	{
		while (node != ft_nullptr && node->left != _TNULL && node->left != ft_nullptr)
		{
			node = node->left;
		}
		return node;
	}

	// advance the node to the biggest element of the branch
	template <class T, class Compare, class Allocator>
	typename BLACKREDCLASS::node_pointer BLACKREDCLASS::maximum(node_pointer node) const
	{
		while (node != ft_nullptr && node->right != _TNULL && node->right != ft_nullptr)
		{
			node = node->right;
		}
		return node;
	}

	// return the succesor of the node
	template <class T, class Compare, class Allocator>
	typename BLACKREDCLASS::node_pointer BLACKREDCLASS::successor(node_pointer x) const
	{
		if (x != ft_nullptr && x->right != _TNULL)
			return minimum(x->right);
		node_pointer y = x->parent;
		while (y != ft_nullptr && y != _TNULL && x == y->Childright)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	// return the predecessor of the node
	template <class T, class Compare, class Allocator>
	typename BLACKREDCLASS::node_pointer BLACKREDCLASS::predecessor(node_pointer x) const
	{
		if (x->left != _TNULL)
			return maximum(x->left);
		node_pointer y = x->parent;
		while (y != _TNULL && x == y->left)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	// erase an element
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::erase(key_type data)
	{
		_deleteNode(this->_root, data);
	}

	// print the tree
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::_print(node_pointer _root, std::string indent, bool last) const
	{
		if (_root != _TNULL)
		{
			std::cout << indent;
			if (last)
			{
				std::cout << "R----";
				indent += "   ";
			}
			else
			{
				std::cout << "L----";
				indent += "|  ";
			}

			std::string sColor = _root->color ? "RED" : "BLACK";
			std::cout << _root->data.second << "(" << sColor << ")" << std::endl;
			_print(_root->left, indent, false);
			_print(_root->right, indent, true);
		}
	}

	// Visit root node
	// Visit all the nodes in the left subtree
	// Visit all the nodes in the right subtree
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::preorder() const
	{
		_preorder(this->_root);
	}

	//	First, visit all the nodes in the left subtree
	//  Then the root node
	//  Visit all the nodes in the right subtree
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::inorder() const
	{
		_inorder(this->_root);
	}

	// Visit all the nodes in the left subtree
	//  Visit all the nodes in the right subtree
	//  Visit the root node
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::postorder() const
	{
		_postorder(this->_root);
	}

	// research an element in the tree by checking the Key of the element
	template <class T, class Compare, class Allocator>
	typename BLACKREDCLASS::node_pointer BLACKREDCLASS::find(const pair_type value) const
	{
		return _find(this->_root, value.first);
	}

	// research an element in the tree by checking the Key of the element
	template <class T, class Compare, class Allocator>
	typename BLACKREDCLASS::node_pointer BLACKREDCLASS::find(const key_type key) const
	{
		return _find(this->_root, key);
	}

	// display the tree in preorder
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::_preorder(node_pointer node) const
	{
		if (node != _TNULL)
		{
			std::cout << node->data.second << " ";
			_preorder(node->left);
			_preorder(node->right);
		}
	}

	// display the tree in inorder
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::_inorder(node_pointer node) const
	{
		if (node != _TNULL)
		{
			_inorder(node->left);
			std::cout << node->data.second << " ";
			_inorder(node->right);
		}
	}

	// display the tree in postorder
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::_postorder(node_pointer node) const
	{
		if (node != _TNULL)
		{
			_postorder(node->left);
			_postorder(node->right);
			std::cout << node->data.second << " ";
		}
	}

	// research an element in the tree by checking the Key of the element
	template <class T, class Compare, class Allocator>
	typename BLACKREDCLASS::node_pointer BLACKREDCLASS::_find(node_pointer node, key_type key) const
	{
		if (node == ft_nullptr || node == _TNULL)
			return (ft_nullptr);
		if (_comp(key, node->data.first))
			return _find(node->left, key);
		if (_comp(node->data.first, key))
			return _find(node->right, key);
		return node;
	}

	// print the tree
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::printTree() const
	{
		if (_root)
			_print(this->_root, "", true);
	}

	// return the number of element in the tree
	template <class T, class Compare, class Allocator>
	typename BLACKREDCLASS::size_type BLACKREDCLASS::get_size() const
	{
		return (this->_size);
	}

	// return the max size of the tree
	template <class T, class Compare, class Allocator>
	typename BLACKREDCLASS::size_type BLACKREDCLASS::get_max_size() const
	{
		return (this->_alloc.max_size());
	}

	// return the root of the tree
	template <class T, class Compare, class Allocator>
	typename BLACKREDCLASS::node_pointer BLACKREDCLASS::get_root(void) const
	{
		return (this->_root);
	}

	// change the value of the root
	template <class T, class Compare, class Allocator>
	void BLACKREDCLASS::set_root(node_pointer data)
	{
		this->_root = data;
	}

	// return a node _TNULL representing NIL
	template <class T, class Compare, class Allocator>
	typename BLACKREDCLASS::node_pointer BLACKREDCLASS::get_last(void) const
	{
		return (this->_TNULL);
	}

	template <class T, class Compare, class Allocator>
	bool BLACKREDCLASS::is_empty() const
	{
		if (_root == ft_nullptr)
			return (true);
		if (this->_size == 0 || this->_size < 0)
			return (true);
		return (false);
	}

	// swap contents
	template <class T, class Compare, class Allocator>
	void swap(const BLACKREDCLASS &lhs, const BLACKREDCLASS &rhs)
	{
		lhs.swap(rhs);
	}
} // namespace ft
#endif