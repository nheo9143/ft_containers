#include <iostream>
#include "enable_if.hpp"


template <typename T> // enalbe_if_version
void swap(T &a, T &b, typename ft::enable_if<!ft::is_integral<T>::vlaue, T >::type* = 0)
{
	T temp;

	temp = a;
	a = b;
	b = temp;
	std::cout << "template swap called" << std::endl;
}

/*
template <typename T> // non_enalbe_if version
void swap(T &a, T &b)
{
	T temp;

	temp = a;
	a = b;
	b = temp;
	std::cout << "template swap called" << std::endl;
}
*/

void swap(int a, int b)
{
	int temp;

	temp = a;
	a = b;
	b = temp;
	std::cout << "int swap called" << std::endl;
}

int main()
{
	/* enalbe_if_test */
	unsigned int a1 = 1;
	unsigned int a2 = 2;
	int b1 = 3;
	int b2 = 4;
	std::string c1 = "hello";
	std::string c2 = "world";

	::swap(a1, a2);
	::swap(b1, b2);
	::swap(c1, c2);


	/*  */
	return 0;
}