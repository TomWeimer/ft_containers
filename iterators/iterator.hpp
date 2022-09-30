#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#define CLASS_ITERATOR ft::wrap_iterator<T>
#include "iterator_traits.hpp"

namespace ft
{

	template <class T>
	class wrap_iterator
	{

	public:
		typedef T iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference reference;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;

	protected:
		iterator_type _current;

	public:
		// Constructors,
		wrap_iterator(void);
		wrap_iterator(iterator_type other);
		explicit wrap_iterator(const wrap_iterator &other);
		template <class U>
		wrap_iterator(const wrap_iterator<U> &other);

		// operator=, destructor
		wrap_iterator operator=(const wrap_iterator &other);
		~wrap_iterator(void);

		// Accessor
		iterator_type base(void) const;
		reference operator*() const;
		pointer operator->(void) const;
		reference operator[](difference_type n);

		// Modifier
		wrap_iterator &operator++();
		wrap_iterator operator++(int);
		wrap_iterator &operator--();
		wrap_iterator operator--(int);
		wrap_iterator operator+(difference_type n) const;
		wrap_iterator operator-(difference_type n) const;
		wrap_iterator &operator+=(difference_type n);
		wrap_iterator &operator-=(difference_type n);
	};

	// Default constructor
	template <class T>
	CLASS_ITERATOR::wrap_iterator(void) : _current() {}

	// Construct a wrap_iterator from a given value, or class
	template <class T>
	CLASS_ITERATOR::wrap_iterator(iterator_type other) : _current(other) {}

	// Copy constructor
	template <class T>
	CLASS_ITERATOR::wrap_iterator(const wrap_iterator &other) : _current(other.base()) {}

	// Copy constructor, from an other type
	template <class T>
	template <class U>
	CLASS_ITERATOR::wrap_iterator(const wrap_iterator<U> &other) : _current(other.base()) {}

	// Assignement operator
	template <class T>
	CLASS_ITERATOR CLASS_ITERATOR::operator=(const wrap_iterator &other)
	{
		if (*this == other)
			return (*this);
		_current = other.base();
		return (*this);
	}

	// Destructor
	template <class T>
	CLASS_ITERATOR::~wrap_iterator(void) {}

	// return the data contained in the iterator
	template <class T>
	typename CLASS_ITERATOR::iterator_type CLASS_ITERATOR::base(void) const
	{
		return (_current);
	}

	// return a the value of _current
	template <class T>
	typename CLASS_ITERATOR::reference CLASS_ITERATOR::operator*() const
	{
		return (*_current);
	}

	// return a pointer on the value of current
	template <class T>
	typename CLASS_ITERATOR::pointer CLASS_ITERATOR::operator->(void) const
	{
		return &(operator*());
	}

	// return the element at position n in current
	template <class T>
	typename CLASS_ITERATOR::reference CLASS_ITERATOR::operator[](difference_type n)
	{
		return (_current[n]);
	}

	// increment the iterator
	template <class T>
	CLASS_ITERATOR &CLASS_ITERATOR::operator++()
	{
		++_current;
		return (*this);
	}

	// increment the iterator
	template <class T>
	CLASS_ITERATOR CLASS_ITERATOR::operator++(int)
	{
		wrap_iterator tmp(*this);
		++(*this);
		return (tmp);
	}

	// decrement the iterator
	template <class T>
	CLASS_ITERATOR &CLASS_ITERATOR::operator--()
	{
		--_current;
		return *this;
	}

	// decrement the iterator
	template <class T>
	CLASS_ITERATOR CLASS_ITERATOR::operator--(int)
	{
		wrap_iterator tmp(*this);
		--(*this);
		return (tmp);
	}

	// return a new iterator n position further
	template <class T>
	CLASS_ITERATOR CLASS_ITERATOR::operator+(difference_type n) const
	{
		wrap_iterator w(*this);
		w += n;
		return (w);
	}

	// return a new iterator n position closer
	template <class T>
	CLASS_ITERATOR CLASS_ITERATOR::operator-(difference_type n) const
	{
		return (wrap_iterator(_current + (-n)));
	}

	// increment the iterator with a given value
	template <class T>
	CLASS_ITERATOR &CLASS_ITERATOR::operator+=(difference_type n)
	{
		_current += n;
		return (*this);
	}

	// decrement the iterator with a given value
	template <class T>
	CLASS_ITERATOR &CLASS_ITERATOR::operator-=(difference_type n)
	{
		*this += -n;
		return (*this);
	}

	// increment an iterator with a certain amount an return it
	template <class T>
	wrap_iterator<T> operator+(typename wrap_iterator<T>::difference_type n,
							   wrap_iterator<T> x)
	{
		x += n;
		return x;
	}

	// return the difference between two iterator of the same type <T>
	template <class T>
	typename wrap_iterator<T>::difference_type
	operator-(const wrap_iterator<T> &x, const wrap_iterator<T> &y)
	{
		return x.base() - y.base();
	}

	// return the difference between two iterator with different type <T> or <U>
	template <class T, class U>
	typename wrap_iterator<T>::difference_type
	operator-(const wrap_iterator<T> &x, const wrap_iterator<U> &y)
	{
		return (x.base() - y.base());
	}

	// non-member function, comparison operator
	template <class T, class U>
	bool operator==(const wrap_iterator<T> &lhs,
					const wrap_iterator<U> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	// non-member function, comparison operator
	template <class T, class U>
	bool operator!=(const wrap_iterator<T> &lhs,
					const wrap_iterator<U> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	// non-member function, comparison operator
	template <class T, class U>
	bool operator<(const wrap_iterator<T> &lhs,
				   const wrap_iterator<U> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	// non-member function, comparison operator
	template <class T, class U>
	bool operator<=(const wrap_iterator<T> &lhs,
					const wrap_iterator<U> &rhs)
	{
		return !(lhs.base() > rhs.base());
	}

	// non-member function, comparison operator
	template <class T, class U>
	bool operator>(const wrap_iterator<T> &lhs,
				   const wrap_iterator<U> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	// non-member function, comparison operator
	template <class T, class U>
	bool operator>=(const wrap_iterator<T> &lhs,
					const wrap_iterator<U> &rhs)
	{
		return !(lhs.base() < rhs.base());
	}

}
#endif