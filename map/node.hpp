#ifndef NODE_HPP
#define NODE_HPP

#include "../utils/ft_nullptr.hpp"
#include "node.hpp"
#include <memory>
#include <iostream>

#define STRUCT_NODE_TREE ft::Node<T, Allocator>
#define RED 1
#define BLACK 0
namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	struct Node
	{

	public:
		typedef T pair_type;
		typedef Node *node_pointer;
		typedef typename pair_type::second_type value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;

		// Member variables
		pair_type data;
		int color;
		node_pointer right;
		node_pointer left;
		node_pointer parent;
		bool NIL;
		node_pointer root;

		// Constructors, destructor, operator=
		Node();
		Node(const pair_type &newData);
		Node(const Node<T> &other);
		Node &operator=(const Node &other);
		~Node();

		// access functions
		value_type get_value(void);
		value_type &get_value_ref(void);
		value_type *get_value_ptr(void);
	};

	template <class T, class Allocator>
	STRUCT_NODE_TREE::Node()
		: data(ft_nullptr, ft_nullptr), color(RED), right(ft_nullptr),
		  left(ft_nullptr), parent(ft_nullptr), NIL(false), root(ft_nullptr) {}

	template <class T, class Allocator>
	STRUCT_NODE_TREE::Node(const pair_type &newData)
		: data(newData.first, newData.second), color(RED), right(ft_nullptr),
		  left(ft_nullptr), parent(ft_nullptr), NIL(false), root(ft_nullptr) {}

	template <class T, class Allocator>
	STRUCT_NODE_TREE::Node(const Node<T> &other)
		: data(other.data), color(other.color), right(ft_nullptr),
		  left(ft_nullptr), parent(ft_nullptr), NIL(false), root(ft_nullptr) {}
	template <class T, class Allocator>
	STRUCT_NODE_TREE &STRUCT_NODE_TREE::operator=(const Node &other)
	{
		if (*this == other)
			return (*this);
		data = other.data;
		color = other.color;
		right = other.right;
		left = other.left;
		parent = other.parent;
		NIL = other.NIL;
		root = other.root;
		return (*this);
	}

	template <class T, class Allocator>
	STRUCT_NODE_TREE::~Node() {}

	template <class T, class Allocator>
	typename STRUCT_NODE_TREE::value_type STRUCT_NODE_TREE::get_value(void)
	{
		return (data.second);
	}
	template <class T, class Allocator>
	typename STRUCT_NODE_TREE::value_type &STRUCT_NODE_TREE::get_value_ref(void)
	{
		return (data.second);
	}
	template <class T, class Allocator>
	typename STRUCT_NODE_TREE::value_type *STRUCT_NODE_TREE::get_value_ptr(void)
	{
		return (&data.second);
	}
}
#endif