#include <iostream>
#include "enable_if.hpp"
#include "vector.hpp"

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


	/* vector test */
	ft::vector<int> v1;
	ft::vector<int> v2(5, 10);
	// ft::vector<int> v3(v2);

	v1.push_back(1);
	v1.push_back(2);
	std::cout << "v1.size() = " << v1.size() << std::endl;
	std::cout << "v2.size() = " << v2.size() << std::endl;
	v1.insert(v1.begin(), 3);
	std::cout << "v1.size() = " << v1.size() << std::endl;
	v1.insert(v1.begin(), 4, 5);
	std::cout << "v1.size() = " << v1.size() << std::endl;
	ft::vector<int>::iterator it = v1.begin();
	// v1.insert(it, v2.begin(), v2.end()); -> not working...
	// std::cout << "v3.size() = " << v3.size() << std::endl;
	return 0;
}