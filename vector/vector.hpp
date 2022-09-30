#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <limits>
#include "vector_base.hpp"
#include <algorithm>
#include "../iterators/iterator.hpp"

#define VECTOR__BASE vector_base<T, Allocator>
#define VECTOR_T T
#define VECTOR_ALLOC typename _base::allocator_type
#define VECTOR_REF typename _base::reference
#define VECTOR_C_REF typename _base::const_reference
#define VECTOR_SIZE typename _base::size_type
#define VECTOR_DIFF typename _base::difference_type
#define VECTOR_PTR typename _base::pointer
#define VECTOR_C_PTR typename _base::const_pointer
#define VECTOR_ITER ft::wrap_iterator<pointer>
#define VECTOR_C_ITER ft::wrap_iterator<const_pointer>
#define VECTOR_RITER ft::reverse_iterator<iterator>
#define VECTOR_C_RITER ft::reverse_iterator<const_iterator>
#define IF_NOT_INTEGRAL \
	typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type *
#define CLASS_VECTOR vector<T, Allocator>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector : public vector_base<T, Allocator>
	{

	private:
		typedef VECTOR__BASE _base;

	public:
		typedef VECTOR_T value_type;
		typedef VECTOR_ALLOC allocator_type;
		typedef VECTOR_REF reference;
		typedef VECTOR_C_REF const_reference;
		typedef VECTOR_SIZE size_type;
		typedef VECTOR_DIFF difference_type;
		typedef VECTOR_PTR pointer;
		typedef VECTOR_C_PTR const_pointer;
		typedef VECTOR_ITER iterator;
		typedef VECTOR_C_ITER const_iterator;
		typedef VECTOR_RITER reverse_iterator;
		typedef VECTOR_C_RITER const_reverse_iterator;

	private:
		void _vallocate(size_type n);
		void _vdeallocate();
		void _construct_at_end(size_type n);
		void _construct_at_end(size_type n, const_reference x);
		template <class Iterator>
		void _construct_range(Iterator first, Iterator last);
		iterator make_iterator(pointer p);
		const_iterator make_iterator(const_pointer p) const;
		pointer move_range(pointer first, pointer last, pointer d_first);
		size_type _recommend(size_type new_size) const;
		void _destruct_at_end(pointer new_last);

	public:
		// Constructors
		vector();
		vector(const vector &other);
		explicit vector(const allocator_type &alloc);

		explicit vector(size_type count, const T &value = T(),
						const Allocator &alloc = Allocator());

		template <class InputIt>
		explicit vector(InputIt first, InputIt last,
						const Allocator &alloc = Allocator(),
						IF_NOT_INTEGRAL = 0);

		// Destructor, operator=, get_allocator()
		~vector();
		vector &operator=(const vector &other);
		allocator_type get_allocator(void) const;
		// Assign
		void assign(size_type count, const T &value);
		template <class InputIt>
		void assign(InputIt first, InputIt last,
					IF_NOT_INTEGRAL = 0);
		//--------------------------------------------------------------
		//	Element access
		reference at(size_type n);
		const_reference at(size_type n) const;
		reference operator[](size_type n);
		const_reference operator[](size_type n) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;
		value_type *data(void);
		const value_type *data() const;
		//--------------------------------------------------------------
		// Iterators
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;
		//--------------------------------------------------------------
		// Capacity
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
		void reserve(size_type n);
		//--------------------------------------------------------------
		// Modifiers
		void clear(void);

		iterator insert(iterator position, const T &x);
		void insert(iterator position, size_type n, const T &x);
		template <class InputIt>
		void insert(iterator position, InputIt first,
					InputIt last, IF_NOT_INTEGRAL = 0);

		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		void push_back(const T &x);
		void pop_back(void);
		void resize(size_type n, value_type val = value_type());
		void swap(vector &x);
	};

	// Allocate memory
	template <class T, class Allocator>
	void CLASS_VECTOR::_vallocate(size_type n)
	{
		if (n > max_size())
			throw(std::length_error("cannot create ft::vector larger than max_size()"));
		this->_begin = this->_alloc().allocate(n);
		this->_end = this->_begin;
		this->_end_cap() = this->_begin + n;
	}

	// Deallocate memory
	template <class T, class Allocator>
	void CLASS_VECTOR::_vdeallocate(void)
	{
		if (this->_begin != ft_nullptr)
		{
			clear();
			this->_alloc().deallocate(this->_begin, this->capacity());
			this->_begin = this->_end = this->_end_cap() = ft_nullptr;
		}
	}

	// Constructs an element on an allocated but uninitialized element
	template <class T, class Allocator>
	void CLASS_VECTOR::_construct_at_end(size_type n)
	{
		if (n > max_size())
			throw(std::length_error("cannot create ft::vector larger than max_size()"));
		while (n--)
		{
			this->_alloc().construct((this->_end)++);
		}
	}

	// Constructs an element on an allocated but uninitialized element
	template <class T, class Allocator>
	void CLASS_VECTOR::_construct_at_end(size_type n, const_reference x)
	{
		if (n > max_size())
			throw(std::length_error("cannot create ft::vector larger than max_size()"));
		while (n--)
		{
			this->_alloc().construct((this->_end)++, x);
		}
	}

	// Constructs an element on a range of allocated but uninitialized element
	template <class T, class Allocator>
	template <class Iterator>
	void CLASS_VECTOR::_construct_range(Iterator first, Iterator last)
	{
		difference_type n = ft::distance(first, last);
		while (n--)
			this->_alloc().construct(this->_end++, *first++);
	}

	// return a new iterator
	template <class T, class Allocator>
	typename CLASS_VECTOR::iterator CLASS_VECTOR::make_iterator(pointer p)
	{
		return iterator(p);
	}

	// return a new iterator
	template <class T, class Allocator>
	typename CLASS_VECTOR::const_iterator CLASS_VECTOR::make_iterator(const_pointer p) const
	{
		return const_iterator(p);
	}

	// destroy the the end of the vector
	template <class T, class Allocator>
	void CLASS_VECTOR::_destruct_at_end(pointer new_last)
	{
		_base::__destruct_at_end(new_last);
	}

	// constructs the vector
	template <class T, class Allocator>
	CLASS_VECTOR::vector(void) : CLASS_VECTOR::_base() {}

	// constructs the vector
	template <class T, class Allocator>
	CLASS_VECTOR::vector(const allocator_type &alloc) : CLASS_VECTOR::_base(alloc) {}

	// constructs the vector
	template <class T, class Allocator>
	CLASS_VECTOR::vector(const vector &other)
		: CLASS_VECTOR::_base(other._alloc())
	{
		size_type n = other.size();
		if (n > 0)
		{
			_vallocate(n);
			_construct_range(other.begin(), other.end());
		}
	}

	// constructs the vector
	template <class T, class Allocator>
	CLASS_VECTOR::vector(size_type count, const T &value,
						 const Allocator &alloc) : CLASS_VECTOR::_base(alloc)
	{
		if (count > 0)
		{
			_vallocate(count);
			_construct_at_end(count, value);
		}
	}

	// constructs the vector
	template <class T, class Allocator>
	template <class InputIt>
	CLASS_VECTOR::vector(InputIt first, InputIt last,
						 const Allocator &alloc, IF_NOT_INTEGRAL) : CLASS_VECTOR::_base(alloc)
	{
		size_type n = static_cast<size_type>(ft::distance(first, last));
		if (n > 0)
		{
			_vallocate(n);
			_construct_range(first, last);
		}
	}

	// assigns values to the container
	template <class T, class Allocator>
	CLASS_VECTOR &CLASS_VECTOR::operator=(const vector &other)
	{
		if (*this == other)
			return (*this);
		clear();
		assign(other.begin(), other.end());
		return *this;
	}

	// destructs the vector
	template <class T, class Allocator>
	CLASS_VECTOR::~vector() {}

	// access the last element
	template <class T, class Allocator>
	typename CLASS_VECTOR::reference CLASS_VECTOR::back()
	{
		return (*(this->_end - 1));
	}

	// access the first element
	template <class T, class Allocator>
	typename CLASS_VECTOR::reference CLASS_VECTOR::front()
	{
		return (*this->_begin);
	}

	// direct access to the underlying array
	template <class T, class Allocator>
	typename CLASS_VECTOR::value_type *CLASS_VECTOR::data()
	{
		return (this->_begin);
	}

	// access specified element with bounds checking
	template <class T, class Allocator>
	typename CLASS_VECTOR::reference CLASS_VECTOR::at(size_type n)
	{
		if (n >= size())
			throw(std::out_of_range("vector::at"));
		return *(this->begin() + n);
	}

	// access the last element
	template <class T, class Allocator>
	typename CLASS_VECTOR::const_reference CLASS_VECTOR::back() const
	{
		return (*(this->_end - 1));
	}

	// access the first element
	template <class T, class Allocator>
	typename CLASS_VECTOR::const_reference CLASS_VECTOR::front() const
	{
		return (*this->_begin);
	}

	// direct access to the underlying array
	template <class T, class Allocator>
	const typename CLASS_VECTOR::value_type *CLASS_VECTOR::data() const
	{
		return (*this->_begin);
	}

	// access specified element with bounds checking
	template <class T, class Allocator>
	typename CLASS_VECTOR::const_reference CLASS_VECTOR::at(size_type n) const
	{
		if (n >= size())
			throw(std::out_of_range("vector::at"));
		return *(this->begin() + n);
	}

	// access specified element
	template <class T, class Allocator>
	typename CLASS_VECTOR::reference CLASS_VECTOR::operator[](size_type n)
	{
		return this->_begin[n];
	}

	// access specified element
	template <class T, class Allocator>
	typename CLASS_VECTOR::const_reference CLASS_VECTOR::operator[](size_type n) const
	{
		return this->_begin[n];
	}

	// returns an iterator to the beginning
	template <class T, class Allocator>
	typename CLASS_VECTOR::iterator CLASS_VECTOR::begin(void)
	{
		return make_iterator(this->_begin);
	}

	// returns an iterator to the beginning
	template <class T, class Allocator>
	typename CLASS_VECTOR::const_iterator CLASS_VECTOR::begin(void) const
	{
		return make_iterator(this->_begin);
	}

	// returns an iterator to the end
	template <class T, class Allocator>
	typename CLASS_VECTOR::iterator CLASS_VECTOR::end(void)
	{
		return make_iterator(this->_end);
	}

	// returns an iterator to the end
	template <class T, class Allocator>
	typename CLASS_VECTOR::const_iterator CLASS_VECTOR::end(void) const
	{
		return make_iterator(this->_end);
	}

	// returns a reverse iterator to the beginning
	template <class T, class Allocator>
	typename CLASS_VECTOR::reverse_iterator CLASS_VECTOR::rbegin(void)
	{
		return reverse_iterator(this->end());
	}

	// returns a reverse iterator to the beginning
	template <class T, class Allocator>
	typename CLASS_VECTOR::const_reverse_iterator CLASS_VECTOR::rbegin(void) const
	{
		return const_reverse_iterator(this->end());
	}

	// returns a reverse iterator to the end
	template <class T, class Allocator>
	typename CLASS_VECTOR::reverse_iterator CLASS_VECTOR::rend(void)
	{
		return reverse_iterator(this->begin());
	}

	// returns a reverse iterator to the end
	template <class T, class Allocator>
	typename CLASS_VECTOR::const_reverse_iterator CLASS_VECTOR::rend(void) const
	{
		return const_reverse_iterator(this->begin());
	}

	// returns the number of elements
	template <class T, class Allocator>
	typename CLASS_VECTOR::size_type CLASS_VECTOR::size() const
	{
		return ft::distance(this->_begin, this->_end);
	}

	// returns the maximum possible number of elements
	template <class T, class Allocator>
	typename CLASS_VECTOR::size_type CLASS_VECTOR::max_size() const
	{
		return std::min<size_type>(this->_alloc().max_size(), std::numeric_limits<difference_type>::max());
	}

	//	checks whether the container is empty
	template <class T, class Allocator>
	bool CLASS_VECTOR::empty(void) const
	{
		return size() == 0 ? true : false;
	}

	// returns the associated allocator
	template <class T, class Allocator>
	typename CLASS_VECTOR::allocator_type CLASS_VECTOR::get_allocator(void) const
	{
		return this->_alloc();
	}

	// clears the contents
	template <class T, class Allocator>
	void CLASS_VECTOR::clear(void)
	{
		_base::clear();
	}

	// swaps the contents
	template <class T, class Allocator>
	void CLASS_VECTOR::swap(vector &x)
	{

		std::swap(this->_end_capacity, x._end_capacity);
		std::swap(this->_begin, x._begin);
		std::swap(this->_end, x._end);
	}

	// adds an element to the end
	template <class T, class Allocator>
	void CLASS_VECTOR::push_back(const T &x)
	{
		if (size() >= this->capacity())
			reserve(_recommend(size() + 1));
		this->_alloc().construct(this->_end++, x);
	}

	// removes the last element
	template <class T, class Allocator>
	void CLASS_VECTOR::pop_back(void)
	{
		if (!empty())
			this->_destruct_at_end(this->_end - 1);
	}

	// inserts elements
	template <class T, class Allocator>
	typename CLASS_VECTOR::iterator CLASS_VECTOR::insert(iterator position, const T &x)
	{
		difference_type pos = position - this->begin();
		if (this->_end < this->_end_cap())
		{
			pointer p = this->_begin + pos;
			move_range(p, this->end().base(), p + 1);
			*(this->_begin + static_cast<size_type>(pos)) = x;
			this->_end++;
			return make_iterator(p);
		}
		else
		{
			iterator it2 = this->end();
			reserve(_recommend(size() + 1));
			pointer p = this->_begin + pos;
			move_range(p, this->end().base(), p + 1);
			if (static_cast<size_type>(pos) > size() || (position == it2))
				this->_alloc().construct(p, x);
			else
				*(this->_begin + static_cast<size_type>(pos)) = x;
			this->_end++;
			return make_iterator(p);
		}
	}

	// inserts elements
	template <class T, class Allocator>
	void CLASS_VECTOR::insert(iterator position, size_type n, const T &x)
	{
		if (n > 0)
		{

			difference_type pos = position - this->begin();
			pointer p = this->_begin + pos;
			if (n <= static_cast<size_type>(this->_end_cap() - this->_end))
			{
				size_type old_n = n;
				pointer old_last = this->_end;
				size_type i = 0;
				if (n > static_cast<size_type>(this->_end - p))
				{
					size_type size_tmp = n - (this->_end - p);
					while (i < n)
					{
						this->_alloc().construct(p, x);
						this->_end++;
						p++;
						i++;
					}
					n -= size_tmp;
				}
				if (n > 0)
				{
					move_range(p, old_last, p + old_n);
					*(this->_begin + pos + i) = x;
					this->_end++;
				}
			}
			else
			{
				size_type size_keep = size();
				vector temp;
				temp.reserve(_recommend(size() + n));
				size_type i = 0;
				size_type j = 0;
				for (; i < static_cast<size_type>(pos); i++)
				{
					this->_alloc().construct(temp._begin + i + j, *(this->_begin + i));
					temp._end++;
				}
				for (; j < n; j++)
				{
					this->_alloc().construct(temp._begin + i + j, x);
					temp._end++;
				}
				if (size_keep > i)
				{
					for (; i < size_keep; i++)
					{
						this->_alloc().construct(temp._begin + i + j, *(this->_begin + i));
						temp._end++;
					}
				}

				this->swap(temp);
			}
		}
	}

	// inserts elements
	template <class T, class Allocator>
	template <class InputIt>
	void CLASS_VECTOR::insert(iterator position, InputIt first, InputIt last,
							  IF_NOT_INTEGRAL)
	{
		difference_type pos = position - this->begin();
		size_type n = ft::distance(first, last);
		size_type size_keep = size();
		vector temp;
		temp.reserve(_recommend(size() + n));
		size_type i = 0;
		size_type j = 0;

		for (; i < static_cast<size_type>(pos); i++)
		{
			this->_alloc().construct(temp._begin + i + j, *(this->_begin + i));
			temp._end++;
		}
		for (; first != last; first++)
		{
			this->_alloc().construct(temp._begin + i + j, *first);
			temp._end++;
			j++;
		}
		if (size_keep > i)
		{
			for (; i < size_keep; i++)
			{
				this->_alloc().construct(temp._begin + i + j, *(this->_begin + i));
				temp._end++;
			}
		}

		this->swap(temp);
	}

	// erases elements
	template <class T, class Allocator>
	typename CLASS_VECTOR::iterator CLASS_VECTOR::erase(iterator position)
	{
		difference_type pos = position - this->begin();
		pointer p = this->_begin + pos;
		_destruct_at_end(
			move_range(p + 1, this->end().base(), p));
		iterator r = make_iterator(p);
		return r;
	}

	// erases elements
	template <class T, class Allocator>
	typename CLASS_VECTOR::iterator CLASS_VECTOR::erase(iterator first, iterator last)
	{
		difference_type pos = first - this->begin();
		pointer p = this->_begin + pos;
		if (first != last)
			_destruct_at_end(move_range(p + (last - first), end().base(), p));
		iterator r = make_iterator(p);
		return r;
	}

	// advance an range of element
	template <class T, class Allocator>
	typename CLASS_VECTOR::pointer CLASS_VECTOR::move_range(pointer first, pointer last, pointer d_first)
	{
		vector temp(first, last);
		iterator beg = temp.begin();
		while (beg != temp.end())
		{
			if (last > d_first)
				*d_first++ = *beg++;
			else
				this->_alloc().construct(d_first++, *beg++);
		}
		temp.clear();
		return d_first;
	}

	// assigns values to the container
	template <class T, class Allocator>
	void CLASS_VECTOR::assign(size_type n, const T &value)
	{
		if (n >= this->capacity())
			reserve(_recommend(n));
		clear();
		while (n--)
			this->_alloc().construct(this->_end++, value);
	};

	// assigns values to the container
	template <class T, class Allocator>
	template <class InputIt>
	void CLASS_VECTOR::assign(InputIt first, InputIt last, IF_NOT_INTEGRAL)
	{
		clear();
		for (; first != last; ++first)
		{
			if (this->_end < this->_end_cap())
				this->_alloc().construct(this->_end++, *first);
			else
			{
				reserve(_recommend(size() + 1));
				this->_alloc().construct(_base::to_address(this->_end++), *first);
			}
		}
	}

	// return a size recommended to allocate for example
	template <class T, class Allocator>
	typename CLASS_VECTOR::size_type CLASS_VECTOR::_recommend(size_type new_size) const
	{

		const size_type max_size = this->max_size();
		if (new_size > max_size)
			throw(std::length_error("cannot create ft::vector larger than max_size()"));
		const size_type capacity = this->capacity();
		if (capacity >= max_size / 2)
			return max_size;
		return std::max<size_type>(2 * capacity, new_size);
	}

	//	reserves storage
	template <class T, class Allocator>
	void CLASS_VECTOR::reserve(size_type n)
	{
		if (n > this->max_size())
			throw(std::length_error("vector::reserve"));
		else if (n > this->capacity())
		{
			pointer new_begin = this->_alloc().allocate(n);
			size_type sz = size();
			for (size_type i = 0; i < size(); i++)
			{
				this->_alloc().construct(new_begin + i, *(this->_begin + i));
			}
			_vdeallocate();
			this->_begin = new_begin;
			this->_end = new_begin + sz;
			this->_end_cap() = new_begin + n;
		}
	}

	// changes the number of elements stored
	template <class T, class Allocator>
	void CLASS_VECTOR::resize(size_type n, value_type val)
	{
		if (n > max_size())
			throw(std::length_error("vector::resize"));
		while (n > size())
			push_back(val);
		while (n < size())
			pop_back();
	}

	// Non member function, comparison operator
	template <class T, class Allocator>
	bool operator==(const CLASS_VECTOR &lhs,
					const CLASS_VECTOR &rhs)
	{
		const typename CLASS_VECTOR::size_type sz = lhs.size();
		return sz == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	// Non member function, comparison operator
	template <class T, class Allocator>
	bool operator!=(const CLASS_VECTOR &lhs,
					const CLASS_VECTOR &rhs)
	{
		return !(lhs == rhs);
	}

	// Non member function, comparison operator
	template <class T, class Allocator>
	bool operator<(const CLASS_VECTOR &lhs,
				   const CLASS_VECTOR &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
										   rhs.end());
	}

	// Non member function, comparison operator
	template <class T, class Allocator>
	bool operator<=(const CLASS_VECTOR &lhs,
					const CLASS_VECTOR &rhs)
	{
		return !(rhs < lhs);
	}

	// Non member function, comparison operator
	template <class T, class Allocator>
	bool operator>(const CLASS_VECTOR &lhs,
				   const CLASS_VECTOR &rhs)
	{
		return (rhs < lhs);
	}

	// Non member function, comparison operator
	template <class T, class Allocator>
	bool operator>=(const CLASS_VECTOR &lhs,
					const CLASS_VECTOR &rhs)
	{
		return !(lhs < rhs);
	}

	// Non member function, comparison operator
	template <class T, class Allocator>
	void swap(CLASS_VECTOR &x, CLASS_VECTOR &y)
	{
		x.swap(y);
	}
}

#endif // VECTOR_HPP
