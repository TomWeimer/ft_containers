#ifndef BLACK_RED_ITERATOR_HPP
#define BLACK_RED_ITERATOR_HPP

#include <cstddef>
#include "../map/tree.hpp"
#include "const_black_red_iterator.hpp"

#define TREE_ITER ft::tree_iterator<T>

namespace ft
{
	template <class T>
	class tree_iterator
	{

	public:
		typedef T value_type;
		typedef value_type *node_pointer;
		typedef ptrdiff_t difference_type;
		typedef typename value_type::pointer pointer;
		typedef typename value_type::reference reference;
		typedef std::bidirectional_iterator_tag iterator_category;

	protected:
		node_pointer _current;

	private:
		node_pointer _minimum(node_pointer node) const;
		node_pointer _maximum(node_pointer node) const;

	public:
		// Constructors,
		tree_iterator(void);
		tree_iterator(const node_pointer other);
		tree_iterator(const tree_iterator &other);
		template <class U>
		tree_iterator(const tree_iterator<U> &other);

		// operator=, destructor
		tree_iterator &operator=(const tree_iterator &other);
		~tree_iterator(void);

		// Accessor
		node_pointer base(void) const;
		reference operator*() const;
		pointer operator->(void) const;

		// Modifier
		tree_iterator &operator++();
		tree_iterator operator++(int);
		tree_iterator &operator--(void);
		tree_iterator operator--(int);

		template<class Iterator>
		operator const_tree_iterator<Iterator>()
		{
			return (const_tree_iterator<Iterator>(this->base()));
		}
	};

	// advance the underlying node to the smallest element of the branch of the bst
	template <class T>
	typename TREE_ITER::node_pointer TREE_ITER::_minimum(node_pointer node) const
	{
		while (node->left->NIL != true)
			node = node->left;
		return node;
	}

	// advance the underlying node to the biggest element of the branch of the bst
	template <class T>
	typename TREE_ITER::node_pointer TREE_ITER::_maximum(node_pointer node) const
	{
		while (node->right->NIL != true)
			node = node->right;
		return node;
	}

	// Default constructor
	template <class T>
	TREE_ITER::tree_iterator(void) : _current() {}

	// Constructor, create an iterator from a node
	template <class T>
	TREE_ITER::tree_iterator(const node_pointer other) : _current(other) {}


	template <class T>
	TREE_ITER::tree_iterator(const tree_iterator& other) : _current(other.base()) {}

	// Copy constructor
	template <class T>
	template <class U>
	TREE_ITER::tree_iterator(const tree_iterator<U> &other) : _current(other.base()) {}

	// Assignement operator
	template <class T>
	ft::tree_iterator<T>  &TREE_ITER::operator=(const tree_iterator &other)
	{
		if (*this == other)
			return (*this);
		_current = other.base();
		return (*this);
	}

	// Destructor
	template <class T>
	TREE_ITER::~tree_iterator(void) {}

	// Return the underlying node
	template <class T>
	typename TREE_ITER::node_pointer TREE_ITER::base(void) const
	{
		return (_current);
	}

	// Return a reference on the pair within the underlying node
	template <class T>
	typename TREE_ITER::reference TREE_ITER::operator*() const
	{
		return (_current->data);
	}

	// Return a pointer on the pair within the underlying node
	template <class T>
	typename TREE_ITER::pointer TREE_ITER::operator->(void) const
	{
		pointer tmp = &_current->data;
		return (tmp);
	}

	// Increment the iterator
	template <class T>
	TREE_ITER  &TREE_ITER::operator++()
	{
		if (_current == ft_nullptr)
			return (*this);
		if (_current->right && _current->right->NIL == false)
			_current = this->_minimum(_current->right);
		else
		{
			node_pointer y = _current->parent;
			while (y != ft_nullptr && _current == y->right)
			{
				_current = y;
				y = y->parent;
			}
			if (y == ft_nullptr)
			{
				while (_current->left->NIL == false)
				{
					_current = _current->left;
				}
				_current = _current->left;
			}
			else
				_current = y;
		}
		return (*this);
	}

	// Increment the iterator
	template <class T>
	TREE_ITER  TREE_ITER::operator++(int)
	{
		tree_iterator tmp(*this);
		if (_current == ft_nullptr)
			return (tmp);
		if (_current->right && _current->right->NIL == false)
			_current = this->_minimum(_current->right);
		else
		{
			node_pointer y = _current->parent;
			while (y != ft_nullptr && _current == y->right)
			{
				_current = y;
				y = y->parent;
			}
			if (y == ft_nullptr)
			{
				while (_current->left->NIL == false)
				{
					_current = _current->left;
				}
				_current = _current->left;
			}
			else
				_current = y;
		}
		return (tmp);
	}

	// Decrement the iterator
	template <class T>
	TREE_ITER  &TREE_ITER::operator--(void)
	{
		if (_current == ft_nullptr)
			return (*this);
		else if (_current->NIL == true && _current->root != ft_nullptr)
		{
			_current = this->_maximum(_current->root);
			return (*this);
		}
		if (_current->left && _current->left->NIL == false)
			_current = this->_maximum(_current->left);
		else
		{
			node_pointer y = _current->parent;
			while (y != ft_nullptr && _current == y->left)
			{
				_current = y;
				y = y->parent;
			}
			if (y != ft_nullptr)
				_current = y;
		}
		return (*this);
	}

	// Decrement the iterator
	template <class T>
	TREE_ITER  TREE_ITER::operator--(int)
	{
		tree_iterator tmp(*this);
		if (_current == ft_nullptr)
			return (tmp);
		else if (_current->NIL == true && _current->root != ft_nullptr)
		{
			_current = this->_maximum(_current->root);
			return (tmp);
		}
		if (_current->left && _current->left->NIL == false)
			_current = this->_maximum(_current->left);
		else
		{
			node_pointer y = _current->parent;
			while (y != ft_nullptr && _current == y->left)
			{
				_current = y;
				y = y->parent;
			}
			if (y != ft_nullptr)
				_current = y;
		}
		return (tmp);
	}

	// Non member function, comparison operator
	template <class Iterator1, class Iterator2>
	bool operator==(const tree_iterator<Iterator1> &lhs,
					const const_tree_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	// Non member function, comparison operator
	template <class Iterator1, class Iterator2>
	bool operator==(const const_tree_iterator<Iterator1> &lhs,
					const tree_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	// Non member function, comparison operator
	template <class Iterator1, class Iterator2>
	bool operator==(const tree_iterator<Iterator1> &lhs,
					const tree_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	// Non member function, comparison operator
	template <class Iterator1, class Iterator2>
	bool operator!=(const tree_iterator<Iterator1> &lhs,
					const tree_iterator<Iterator2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	// Non member function, comparison operator
	template <class Iterator1, class Iterator2>
	bool operator!=(const const_tree_iterator<Iterator1> &lhs,
					const tree_iterator<Iterator2> &rhs)
	{
		return !(lhs.base() == rhs.base());
	}

	// Non member function, comparison operator
	template <class Iterator1, class Iterator2>
	bool operator!=(const tree_iterator<Iterator1> &lhs,
					const const_tree_iterator<Iterator2> &rhs)
	{
		return !(lhs.base() == rhs.base());
	}
}
#endif // BLACK_RED_ITERATOR