#ifndef FT_CONTAINERS_PAIR_PAIR_HPP_
#define FT_CONTAINERS_PAIR_PAIR_HPP_
namespace ft
{
	/* Class template pair */
	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() : first(), second(){};

		pair(const first_type &x, const second_type &y) : first(x), second(y) {}

		template <class U, class V>
		pair(const pair<U, V> &p) : first(p.first), second(p.second) {}

		pair &operator=(const pair &p)
		{
			first = p.first;
			second = p.second;
			return (*this);
		}
	};

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first ? lhs.second < rhs.second : lhs.first < rhs.first);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs > rhs);
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs < rhs);
	}
	/* Template function make_pair*/
	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	template <class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
				return (false);
		}
		return (true);
	}

	template <class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!p(*first1, *first2))
				return (false);
		}
		return (true);
	}

	template <class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for (; first1 != last1 && (first2 != last2); ++first1, (void)++first2)
		{
			if (*first1 < *first2)
				return (true);
			if (*first2 < *first1)
				return (false);
		}
		return ((first1 == last1) && (first2 != last2));
	}

	template <class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; first1 != last1; ++first1, (void)++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <class T, T v>
	struct integral_constant
	{

		static const T value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type(void) const { return value; }
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;
	// bool, char, char16_t, char32_t, wchar_t, short, int, long, long long
	template <class T>
	struct is_integral : false_type
	{
	};
	template <>
	struct is_integral<short int> : true_type
	{
	};
	template <>
	struct is_integral<unsigned short int> : true_type
	{
	};

	template <>
	struct is_integral<int> : true_type
	{
	};
	template <>
	struct is_integral<unsigned int> : true_type
	{
	};

	template <>
	struct is_integral<long int> : true_type
	{
	};
	template <>
	struct is_integral<unsigned long int> : true_type
	{
	};

	template <>
	struct is_integral<bool> : true_type
	{
	};

	template <>
	struct is_integral<char> : true_type
	{
	};
	template <>
	struct is_integral<signed char> : true_type
	{
	};
	template <>
	struct is_integral<unsigned char> : true_type
	{
	};

	template <>
	struct is_integral<wchar_t> : true_type
	{
	};

	template <bool B, class T = void>
	struct enable_if
	{
	};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

}

#endif