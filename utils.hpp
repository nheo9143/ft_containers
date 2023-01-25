#ifndef UTILS_HPP
# define UTILS_HPP

# include "iterator.hpp"

namespace ft
{
	template <typename InputIterator>
	typename ft::random_access_iterator<InputIterator>::difference_type difference(InputIterator first, InputIterator last)
	{
		typename ft::random_access_iterator<InputIterator>::difference_type n = 0;
		for (; first != last; first++)
			n++;
		return n;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1)
				return false;
			else if (*first1<*first2)
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}

	/* enable_if 기본형 선언 */
	template <bool, typename T>
	struct enable_if {};

	/* true가 들어왔을 때의 처리 */
	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	/* is_integral 기본형 선언 */
	template<typename T>
	struct is_integral { static const bool value = false;};

	template<>
	struct is_integral<bool> {static const bool value = true;};

	template<>
	struct is_integral<char> {static const bool value = true;};

	template<>
	struct is_integral<signed char> {static const bool value = true;};

	template<>
	struct is_integral<wchar_t> {static const bool value = true;};

	template<>
	struct is_integral<short> {static const bool value = true;};

	template<>
	struct is_integral<int> {static const bool value = true;};

	template<>
	struct is_integral<long> {static const bool value = true;};

	template<>
	struct is_integral<unsigned char> {static const bool value = true;};

	template<>
	struct is_integral<unsigned short> {static const bool value = true;};

	template<>
	struct is_integral<unsigned int> {static const bool value = true;};

	template<>
	struct is_integral<unsigned long> {static const bool value = true;};
}

#endif