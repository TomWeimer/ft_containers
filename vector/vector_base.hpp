#ifndef VECTORBASE_HPP
#define VECTORBASE_HPP

#include <memory>
#include "../utils/utility.hpp"
#include "../utils/ft_nullptr.hpp"
#include "../iterators/reverse_iterators.hpp"

#define ALLOC_TYPES Allocator
#define SIZE_TYPE typename allocator_type::size_type
#define VALUE_TYPE T
#define REFERENCE typename allocator_type::reference
#define CONST_REF typename allocator_type::const_reference
#define DIFFERENCE typename allocator_type::difference_type
#define POINTER typename allocator_type::pointer
#define CONST_PTR typename allocator_type::const_pointer
#define ITERATOR pointer
#define CONST_ITER const_pointer
#define REV_ITER ft::reverse_iterator<iterator>
#define CONST_RITER ft::reverse_iterator<const_iterator>
#define FT_PAIR ft::pair<pointer, allocator_type>
#define CLASS_VECTOR_BASE vector_base<T, Allocator>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector_base
	{
	public:
		typedef ALLOC_TYPES allocator_type;
		typedef SIZE_TYPE size_type;

	protected:
		typedef VALUE_TYPE value_type;
		typedef REFERENCE reference;
		typedef CONST_REF const_reference;
		typedef DIFFERENCE difference_type;
		typedef POINTER pointer;
		typedef CONST_PTR const_pointer;
		typedef ITERATOR iterator;
		typedef CONST_ITER const_iterator;
		typedef REV_ITER reverse_iterator;
		typedef CONST_RITER const_reverse_iterator;

		// Member variables
		pointer _begin;
		pointer _end;
		FT_PAIR _end_capacity;

		// Constructors, destructor, operator=
		explicit vector_base(const allocator_type &alloc = Allocator());
		explicit vector_base(const vector_base &other);
		vector_base &operator=(const vector_base &other);
		~vector_base(void);

		// Getter
		allocator_type &_alloc(void);
		const allocator_type &_alloc(void) const;
		pointer &_end_cap(void);
		const pointer &_end_cap(void) const;

		//	Modifiers
		void clear(void);
		void __destruct_at_end(pointer new_end);
		value_type *to_address(pointer p);

	public:
		size_type capacity() const;
	};

	// Constructs vector_base
	template <class T, class Allocator>
	CLASS_VECTOR_BASE::vector_base(const allocator_type &alloc)
		: _begin(ft_nullptr), _end(ft_nullptr), _end_capacity(ft_nullptr, alloc) {}

	// Constructs vector_base
	template <class T, class Allocator>
	CLASS_VECTOR_BASE::vector_base(const vector_base &other)
		: _begin(other._begin), _end(other._end), _end_capacity(other._end_capacity) {}

	// Assignement operator
	template <class T, class Allocator>
	CLASS_VECTOR_BASE &CLASS_VECTOR_BASE::operator=(const vector_base &other)
	{
		if (*this == other)
			return (*this);
		clear();
		_begin = other._begin;
		_end = other._end;
		_end_capacity = other._end_capacity;
		return (*this);
	}

	// Destructor
	template <class T, class Allocator>
	CLASS_VECTOR_BASE::~vector_base(void)
	{
		if (_begin != ft_nullptr)
		{
			clear();
			this->_alloc().deallocate(_begin, this->capacity());
		}
	}

	// return the second_type of _end_capacity
	template <class T, class Allocator>
	typename CLASS_VECTOR_BASE::allocator_type &CLASS_VECTOR_BASE::_alloc(void)
	{
		return (_end_capacity.second);
	}

	// return the second_type of _end_capacity
	template <class T, class Allocator>
	const typename CLASS_VECTOR_BASE::allocator_type &CLASS_VECTOR_BASE::_alloc(void) const
	{
		return (_end_capacity.second);
	}

	// return the first_type of _end_capacity
	template <class T, class Allocator>
	typename CLASS_VECTOR_BASE::pointer &CLASS_VECTOR_BASE::_end_cap(void)
	{
		return (_end_capacity.first);
	}

	// return the first_type of _end_capacity
	template <class T, class Allocator>
	const typename CLASS_VECTOR_BASE::pointer &CLASS_VECTOR_BASE::_end_cap(void) const
	{
		return (_end_capacity.first);
	}

	// returns the number of elements that can be held in currently allocated storage
	template <class T, class Allocator>
	typename CLASS_VECTOR_BASE::size_type CLASS_VECTOR_BASE::capacity() const
	{
		return (static_cast<size_type>(_end_cap() - _begin));
	}

	// clears the contents
	template <class T, class Allocator>
	void CLASS_VECTOR_BASE::clear(void)
	{
		__destruct_at_end(_begin);
	}

	// Obtain the address represented by p without forming a reference to the object pointed to by p.
	template <class T, class Allocator>
	typename CLASS_VECTOR_BASE::value_type *CLASS_VECTOR_BASE::to_address(pointer p)
	{
		return p;
	}

	// destroy the the end of the vector
	template <class T, class Allocator>
	void CLASS_VECTOR_BASE::__destruct_at_end(pointer new_end)
	{
		pointer tmp = this->_end;
		while (new_end != tmp)
		{
			this->_alloc().destroy(--tmp);
		}
		this->_end = new_end;
	}
}
#endif