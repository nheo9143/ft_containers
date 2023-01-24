#ifndef UTILS_HPP
# define UTILS_HPP

#include "iterator.hpp"

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
}

#endif