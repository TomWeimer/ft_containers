#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP
#include "iterator_traits.hpp"

#define CLASS_RITER ft::reverse_iterator<T>

namespace ft
{
	template <class T>
	class reverse_iterator
	{
	public:
		typedef T iterator_type;
		typedef typename iterator_traits<T>::iterator_category iterator_category;
		typedef typename iterator_traits<T>::value_type value_type;
		typedef typename iterator_traits<T>::difference_type difference_type;
		typedef typename iterator_traits<T>::pointer pointer;
		typedef typename iterator_traits<T>::reference reference;

	protected:
		iterator_type _current;

	public:
		// Constructors
		reverse_iterator();
		explicit reverse_iterator(T other);
		template <class U>
		reverse_iterator(const reverse_iterator<U> &other);

		// operator=, destructor
		reverse_iterator operator=(const reverse_iterator &other);
		~reverse_iterator();

		// Accessor
		iterator_type base() const;
		reference operator*() const;
		pointer operator->() const;
		reference operator[](difference_type n) const;

		// Modifier
		reverse_iterator &operator++();
		reverse_iterator &operator--();
		reverse_iterator operator++(int);
		reverse_iterator operator--(int);
		reverse_iterator operator+(difference_type n) const;
		reverse_iterator operator-(difference_type n) const;
		reverse_iterator &operator+=(difference_type n);
		reverse_iterator &operator-=(difference_type n);
	};
	
	template <class T>
	CLASS_RITER::reverse_iterator() : _current() {}

	template <class T>
	CLASS_RITER::reverse_iterator(iterator_type other) : _current(other) {}

	template <class T>
	template <class U>
	CLASS_RITER::reverse_iterator(const reverse_iterator<U> &other) : _current(other.base()){};

	template <class T>
	CLASS_RITER  CLASS_RITER::operator=(const reverse_iterator &other)
	{
		if (*this == other)
			return (*this);
		_current = other.base();
        return (*this);
	}

	template <class T>
	CLASS_RITER::~reverse_iterator() {}

	template <class T>
	typename CLASS_RITER::iterator_type CLASS_RITER::base(void) const
	{
		return (_current);
	}

	template <class T>
	typename CLASS_RITER::reference CLASS_RITER::operator*() const
	{
		iterator_type tmp = _current;
        return (*--tmp);
	}
	template <class T>
	typename CLASS_RITER::pointer	CLASS_RITER::operator->() const
	{
		return &(operator*());
	}

	template <class T>
	typename CLASS_RITER::reference CLASS_RITER::operator[] (difference_type n) const
	{
		 return (this->base()[-n-1]);
	}

	template <class T>
	CLASS_RITER & CLASS_RITER::operator++()
	{
		 --_current;
        return (*this);   
	}
	template <class T>
	CLASS_RITER & CLASS_RITER::operator--()
	{
		++_current;
        return (*this);  
	}
	template <class T>
	CLASS_RITER  CLASS_RITER::operator++( int )
	{
		reverse_iterator tmp = *this;
        --_current;
    	return (tmp);
	}

	template <class T>
	CLASS_RITER  CLASS_RITER::operator--( int )
	{
		reverse_iterator tmp = *this;
        ++_current;
        return (tmp);
	}

	template <class T>
	CLASS_RITER  CLASS_RITER::operator+( difference_type n ) const
	{
		 return (reverse_iterator(this->_current - n));
	}

	template <class T>
	CLASS_RITER  CLASS_RITER::operator-( difference_type n ) const
	{
		 return (reverse_iterator(this->_current + n));
	}

	template <class T>
	CLASS_RITER & CLASS_RITER::operator+=( difference_type n )
	{
		_current -= n;
        return (*this);
	}

	template <class T>
	CLASS_RITER & CLASS_RITER::operator-=( difference_type n )
	{
		_current += n;
        return (*this);
	}

	// Non member function, return the difference of the two underlying iterator
	template <class T>
	typename reverse_iterator<T>::difference_type
	operator-(const reverse_iterator<T> &lhs,
			  const reverse_iterator<T> &rhs)
	{
		return (rhs.base() - lhs.base());
	}

	// Non member function, return the difference of the two underlying iterator
	template <typename T, typename U>
	typename reverse_iterator<T>::difference_type
	operator-(const reverse_iterator<T> &x,
			  const reverse_iterator<U> &y)
	{
		return (y.base() - x.base());
	}

	// Non member function, comparison operator
	template <class T, class U>
	bool operator==(const reverse_iterator<T> &lhs,
					const reverse_iterator<U> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	// Non member function, comparison operator
	template <class T, class U>
	bool operator!=(const reverse_iterator<T> &lhs,
					const reverse_iterator<U> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	// Non member function, comparison operator
	template <class T, class U>
	bool operator<(const reverse_iterator<T> &lhs,
				   const reverse_iterator<U> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	// Non member function, comparison operator
	template <class T, class U>
	bool operator<=(const reverse_iterator<T> &lhs,
					const reverse_iterator<U> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	// Non member function, comparison operator
	template <class T, class U>
	bool operator>(const reverse_iterator<T> &lhs,
				   const reverse_iterator<U> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	// Non member function, comparison operator
	template <class T, class U>
	bool operator>=(const reverse_iterator<T> &lhs,
					const reverse_iterator<U> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iter>
	reverse_iterator<Iter>
	operator+(typename reverse_iterator<Iter>::difference_type n,
			  const reverse_iterator<Iter> &x)
	{
		return reverse_iterator<Iter>(x.base() - n);
	}

}
#endif
