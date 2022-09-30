#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <stdexcept>
#include <functional>
#include "tree.hpp"
#include "../iterators/black_red_iterator.hpp"
#include "../iterators/const_black_red_iterator.hpp"
#include "../iterators/reverse_iterators.hpp"

#define IF_TYPE_NOT_INTEGRAL typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *
#define CLASS_MAP ft::map<Key, T, Compare, Alloc>

namespace ft
{

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	private:
		typedef ft::BlackRed_Tree<ft::pair<const Key, T>, Compare> tree_type;
		typedef typename tree_type::node_pointer node_pointer;
		typedef typename tree_type::node_type node_type;

	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef typename Allocator::size_type size_type;
		typedef typename Allocator::difference_type difference_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef tree_iterator<node_type> iterator;
		typedef const_tree_iterator<const node_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		class value_compare
		{
			friend class map;

		protected:
			key_compare comp;
			value_compare(const Compare c) : comp(c) {}

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

	private:
		key_compare _comp;
		allocator_type _alloc;
		tree_type _tree;

	public:
		// Constructors, operator=, destructor
		//-----------------------------------------------------------------
		map();
		explicit map(const Compare &comp,
					 const Allocator &alloc = Allocator());

		template <class InputIterator>
		map(InputIterator first,
			InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type());

		map(const map &other);

		map &operator=(const map &other);

		~map(void);

		allocator_type get_allocator() const;

		// Element access
		//-----------------------------------------------------------------
		T &at(const key_type &key) const;

		T &operator[](const Key &key);

		// Iterators
		//-----------------------------------------------------------------
		iterator begin();
		const_iterator begin() const;

		iterator end();
		const_iterator end() const;

		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;

		reverse_iterator rend();
		const_reverse_iterator rend() const;

		// Capacity
		//-----------------------------------------------------------------
		bool empty() const;

		size_type size() const;

		size_type max_size() const;

		// Modifiers
		//-----------------------------------------------------------------
		void clear();

		ft::pair<iterator, bool> insert(const value_type &value);

		iterator insert(iterator hint, const value_type &value);

		template <class InputIterator>
		void insert(InputIterator first,
					InputIterator last,
					IF_TYPE_NOT_INTEGRAL = ft_nullptr);

		void erase(iterator pos);

		void erase(iterator first, iterator last);

		size_type erase(const Key &key);

		void swap(map &other);

		// Lookup
		//-----------------------------------------------------------------
		size_type count(const Key &key) const;

		iterator find(const Key &key);

		const_iterator find(const Key &key) const;

		ft::pair<iterator, iterator> equal_range(const Key &key);

		ft::pair<const_iterator, const_iterator> equal_range(const Key &key) const;

		iterator lower_bound(const Key &key);

		const_iterator lower_bound(const Key &key) const;

		iterator upper_bound(const Key &key);

		const_iterator upper_bound(const Key &key) const;

		// Observers
		//-----------------------------------------------------------------
		value_compare value_comp() const;

		key_compare key_comp() const;
	};

	// constructs the map
	template <class Key, class T, class Compare, class Alloc>
	CLASS_MAP::map() : _comp(Compare()), _alloc(Alloc()), _tree() {}

	// constructs the map
	template <class Key, class T, class Compare, class Alloc>
	CLASS_MAP::map(const Compare &comp, const Alloc &alloc)
		: _comp(comp), _alloc(alloc), _tree() {}

	// constructs the map
	template <class Key, class T, class Compare, class Alloc>
	template <class InputIterator>
	CLASS_MAP::map(InputIterator first, InputIterator last,
				   const key_compare &comp, const allocator_type &alloc)
		: _comp(comp), _alloc(alloc), _tree()
	{
		insert(first, last);
	}

	// Copy constructor
	template <class Key, class T, class Compare, class Alloc>
	CLASS_MAP::map(const map &other)
	{
		for (const_iterator it = other.begin(); it != other.end(); it++)
			insert(ft::make_pair(it->first, it->second));
	}

	// assigns values to the container
	template <class Key, class T, class Compare, class Alloc>
	ft::map<Key, T, Compare, Alloc>& ft::map<Key, T, Compare, Alloc>::operator=(const map &other)
	{
		if (*this == other)
			return (*this);
		clear();
		if (other.empty() == false)
			this->insert(other.begin(), other.end());
		return (*this);
	}

	// destructs the map
	template <class Key, class T, class Compare, class Alloc>
	CLASS_MAP::~map(void) {}

	// returns the associated allocator
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::allocator_type CLASS_MAP::get_allocator() const
	{
		return (_alloc);
	}

	// access specified element with bounds checking
	template <class Key, class T, class Compare, class Alloc>
	T &CLASS_MAP::at(const key_type &key) const
	{
		node_pointer to_find = _tree.find(key);
		if (to_find == ft_nullptr)
			throw std::out_of_range("map::at: key not found");
		return (to_find->data.second);
	}

	// access or insert specified element
	template <class Key, class T, class Compare, class Alloc>
	T &CLASS_MAP::operator[](const Key &key)
	{
		return ((*((this->insert(ft::make_pair(key, mapped_type()))).first)).second);
	}

	// returns an iterator to the beginning
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::iterator CLASS_MAP::begin()
	{
		if (this->_tree.is_empty() == true)
			return this->end();
		else if (_tree.get_size() == 1)
			return iterator(_tree.get_root());
		else if (_tree.get_size() > 1 && _tree.get_root())
			return iterator(_tree.minimum(_tree.get_root()));
		return iterator(_tree.maximum(_tree.get_root()));
	}

	// returns an iterator to the beginning
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::const_iterator CLASS_MAP::begin() const
	{
		if (this->_tree.is_empty() == true)
			return this->end();
		else if (_tree.get_size() == 1)
			return const_iterator(_tree.get_root());
		else if (_tree.get_size() > 1 && _tree.get_root())
			return const_iterator(_tree.minimum(_tree.get_root()));
		return const_iterator(_tree.maximum(_tree.get_root()));
	}

	// returns an iterator to the end
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::iterator CLASS_MAP::end()
	{
		if (this->_tree.is_empty() == true)
			return iterator(_tree.get_last());
		return iterator(_tree.get_last());
	}

	// returns an iterator to the end
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::const_iterator CLASS_MAP::end() const
	{
		if (this->_tree.is_empty() == true)
			return const_iterator(_tree.get_last());
		return const_iterator(_tree.get_last());
	}

	// returns a reverse iterator to the beginning
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::reverse_iterator CLASS_MAP::rbegin()
	{
		return (reverse_iterator(this->end()));
	}

	// returns a reverse iterator to the beginning
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::const_reverse_iterator CLASS_MAP::rbegin() const
	{
		return (const_reverse_iterator(this->end()));
	}

	// returns a reverse iterator to the end
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::reverse_iterator CLASS_MAP::rend()
	{
		return (reverse_iterator(this->begin()));
	}

	// returns a reverse iterator to the end
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::const_reverse_iterator CLASS_MAP::rend() const
	{
		return (const_reverse_iterator(this->begin()));
	}

	// checks whether the container is empty
	template <class Key, class T, class Compare, class Alloc>
	bool CLASS_MAP::empty() const
	{
		if (_tree.get_size() <= 0)
			return (true);
		return (false);
	}

	// returns the number of elements
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::size_type CLASS_MAP::size() const
	{
		return static_cast<size_type>(_tree.get_size());
	}

	// returns the maximum possible number of elements
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::size_type CLASS_MAP::max_size() const
	{
		return static_cast<size_type>(_tree.get_max_size());
	}

	// clears the contents
	template <class Key, class T, class Compare, class Alloc>
	void CLASS_MAP::clear(void)
	{
		_tree.clear();
		_tree.set_root(ft_nullptr);
	}

	// inserts elements
	template <class Key, class T, class Compare, class Alloc>
	ft::pair<typename CLASS_MAP::iterator, bool> CLASS_MAP::insert(const value_type &value)
	{
		node_pointer node_exist = _tree.find(value.first);
		if (node_exist)
			return (ft::pair<iterator, bool>(iterator(node_exist), false));
		_tree.insert(value);
		node_exist = _tree.find(value.first);
		return (ft::pair<iterator, bool>(iterator(node_exist), true));
	}

	// inserts elements
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::iterator CLASS_MAP::insert(iterator hint, const value_type &value)
	{
		node_pointer new_node = _tree.find(value.first);
		if (new_node)
			return (iterator(new_node));
		if (hint == this->end())
			_tree.insert(value);
		else
			_tree.insert(value, hint.base());
		new_node = _tree.find(value.first);
		return (iterator(new_node));
	}

	// inserts elements
	template <class Key, class T, class Compare, class Alloc>
	template <class InputIterator>
	void CLASS_MAP::insert(InputIterator first,
						   InputIterator last,
						   IF_TYPE_NOT_INTEGRAL)
	{
		node_pointer exist;
		for (; first != last;)
		{
			exist = _tree.find(first->first);
			if (exist == ft_nullptr)
				_tree.insert(ft::make_pair(first->first, first->second));
			else
				exist = ft_nullptr;
			first++;
		}
	}

	// erases elements
	template <class Key, class T, class Compare, class Alloc>
	void CLASS_MAP::erase(iterator pos)
	{
		_tree.erase(pos->first);
	}

	// erases elements
	template <class Key, class T, class Compare, class Alloc>
	void CLASS_MAP::erase(iterator first, iterator last)
	{
		while (first != last)
			erase(first++);
	}

	// erases elements
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::size_type CLASS_MAP::erase(const Key &key)
	{
		size_type counter = count(key);
		size_type i = 0;
		while (i < counter)
		{
			_tree.erase(key);
			i++;
		}
		return (counter);
	}

	// swaps the contents
	template <class Key, class T, class Compare, class Alloc>
	void CLASS_MAP::swap(map &other)
	{
		std::swap(this->_comp, other._comp);
		_tree.swap(other._tree);
		std::swap(this->_alloc, other._alloc);
	}

	// returns the number of elements matching specific key
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::size_type CLASS_MAP::count(const Key &key) const
	{
		size_type counter = 0;
		for (const_iterator it = this->begin(); it != this->end(); ++it)
		{
			if (it->first == key)
				++counter;
		}
		return (counter);
	}

	//	finds element with specific key
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::iterator CLASS_MAP::find(const Key &key)
	{
		node_pointer to_find = this->_tree.find(key);
		if (to_find == ft_nullptr)
			return iterator(_tree.get_last());
		return iterator(to_find);
	}

	// 	finds element with specific key
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::const_iterator CLASS_MAP::find(const Key &key) const
	{
		node_pointer to_find = this->_tree.find(key);
		if (to_find == ft_nullptr)
			return const_iterator(_tree.get_last());
		return const_iterator(to_find);
	}

	// returns range of elements matching a specific key
	template <class Key, class T, class Compare, class Alloc>
	ft::pair<typename CLASS_MAP::iterator, typename CLASS_MAP::iterator>
	CLASS_MAP::equal_range(const Key &key)
	{
		return ft::make_pair(lower_bound(key), upper_bound(key));
	}

	// returns range of elements matching a specific key
	template <class Key, class T, class Compare, class Alloc>
	ft::pair<typename CLASS_MAP::const_iterator, typename CLASS_MAP::const_iterator>
	CLASS_MAP::equal_range(const Key &key) const
	{
		return ft::make_pair(lower_bound(key), upper_bound(key));
	}

	// returns an iterator to the first element not less than the given key
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::iterator CLASS_MAP::lower_bound(const Key &key)
	{
		iterator first = this->begin();
		iterator last = this->end();
		for (; first != last; ++first)
		{
			if (this->_comp((*first).first, key) == false)
				return (first);
		}
		return (last);
	}

	// returns an iterator to the first element not less than the given key
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::const_iterator CLASS_MAP::lower_bound(const Key &key) const
	{
		const_iterator first = this->begin();
		const_iterator last = this->end();
		for (; first != last; ++first)
		{
			if (this->_comp((*first).first, key) == false)
				return (first);
		}
		return (last);
	}

	// returns an iterator to the first element greater than the given key
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::iterator CLASS_MAP::upper_bound(const Key &key)
	{
		iterator first = this->begin();
		iterator last = this->end();

		for (; first != last; ++first)
		{
			if (this->_comp(key, (*first).first) == true)
				return (first);
		}
		return (last);
	}

	// returns an iterator to the first element greater than the given key
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::const_iterator CLASS_MAP::upper_bound(const Key &key) const
	{
		const_iterator first = this->begin();
		const_iterator last = this->end();

		for (; first != last; ++first)
		{
			if (this->_comp(key, (*first).first) == true)
				return (first);
		}
		return (last);
	}

	// returns the function that compares keys in objects of type value_type
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::value_compare CLASS_MAP::value_comp() const
	{
		return (value_compare(this->_comp));
	}

	// returns the function that compares keys
	template <class Key, class T, class Compare, class Alloc>
	typename CLASS_MAP::key_compare CLASS_MAP::key_comp() const
	{
		return (this->_comp);
	}

	// Non member function, comparison operator
	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs,
					const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	// Non member function, comparison operator
	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs,
					const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	// Non member function, comparison operator
	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs,
				   const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	// Non member function, comparison operator
	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs,
				   const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return rhs < lhs;
	}

	// Non member function, comparison operator
	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs,
					const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	// Non member function, comparison operator
	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs,
					const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	// Non member function, comparison operator
	template <class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key, T, Compare, Alloc> &lhs,
			  ft::map<Key, T, Compare, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}

}

#endif // HASH_MAP_HPP