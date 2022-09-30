#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iterator>
#include <cstddef>
#include "../utils/utility.hpp"

namespace ft
{
	template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template <class T>
	struct iterator_traits<T *>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct iterator_traits<const T *>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct is_input_iterator : false_type {};

	template <>
	struct is_input_iterator<std::input_iterator_tag> : true_type {};

	template <class T>
	struct is_output_iterator : false_type {};

	template <>
	struct is_output_iterator<std::output_iterator_tag> : true_type {};

	template <class T>
	struct is_forward_iterator : false_type {};

	template <>
	struct is_forward_iterator<std::forward_iterator_tag> : true_type {};

	template <class T>
	struct is_bidirectional_iterator : false_type {};

	template <>
	struct is_bidirectional_iterator<std::bidirectional_iterator_tag> : true_type {};

	template <class T>
	struct is_random_access_iterator : false_type {};

	template <>
	struct is_random_access_iterator<std::random_access_iterator_tag> : true_type {};

	template <class InputIt>
	typename ft::iterator_traits<InputIt>::difference_type do_distance(InputIt first, InputIt last, std::input_iterator_tag)
	{
		typename ft::iterator_traits<InputIt>::difference_type result = 0;
		while (first != last)
		{
			++first;
			++result;
		}
		return result;
	}

	template <class It>
	typename ft::iterator_traits<It>::difference_type do_distance(It first, It last, std::random_access_iterator_tag)
	{
		return last - first;
	}

	template <class InputIt>
	typename ft::iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last)
	{
		return do_distance(first, last, typename ft::iterator_traits<InputIt>::iterator_category());
	}
}

#endif