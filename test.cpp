#include <iostream>
#include "enable_if.hpp"
#include "vector.hpp"
#include <vector>

template <typename T> // enalbe_if_version
void swap(T &a, T &b, typename ft::enable_if<!ft::is_integral<T>::value, T >::type* = 0)
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

	/* real vector */
	std::vector<int> rv1;
	std::vector<int> rv2(5, 10);
	std::cout << "rv2.size() = " << rv2.size() << std::endl;
	std::vector<int> rv3(rv2.begin(), rv2.end());


	/* vector constructer test */
	std::cout << std::endl << "---------------------my vector test---------------------" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl << "---------------------constructer test---------------------" << std::endl;
	ft::vector<int> v1;
	ft::vector<int> v2(5, 10);
	std::cout << "v2.size() = " << v2.size() << std::endl;
	ft::vector<int> v3(v2.begin(), v2.end());

	/* push_back test */
	std::cout << std::endl << "---------------------push_back test---------------------" << std::endl;
	v1.push_back(1);
	v1.push_back(2);
	std::cout << "v1.size() = " << v1.size() << std::endl;

	/* insert test */
	std::cout << std::endl << "---------------------insert test---------------------" << std::endl;
	v1.insert(v1.begin(), 3);
	std::cout << "v1.size() = " << v1.size() << std::endl;
	v1.insert(v1.begin(), 4, 5);
	std::cout << "v1.size() = " << v1.size() << std::endl;

	/* erase test */
	std::cout << std::endl << "---------------------erase test---------------------" << std::endl;
	ft::vector<int>::iterator it = v1.begin();
	it++;
	ft::vector<int>::iterator it2 = v1.erase(it);
	std::cout << "v1.size() = " << v1.size() << std::endl;
	std::cout << "position of erased position: " << it2 - v1.begin() << std::endl;

	v1.clear();
	std::cout << std::endl << "after clear, v1.size() = " << v1.size() << std::endl;
	v1.insert(it, v2.begin(), v2.end());
	std::cout << "v1.size() = " << v1.size() << std::endl;

	/* assign test */
	std::cout << std::endl << "---------------------assign test---------------------" << std::endl;
	v1.assign(5, 10);
	std::cout << "after assgin(5,10), v1.size() = " << v1.size() << std::endl;

	/* swap test */
	std::cout << std::endl << "---------------------swap test---------------------" << std::endl;
	v2.clear();
	std::cout << "before swap, v1.size() = " << v1.size() << std::endl;
	std::cout << "before swap, v2.size() = " << v2.size() << std::endl;
	v1.swap(v2);
	std::cout << "after swap, v1.size() = " << v1.size() << std::endl;
	std::cout << "after swap, v2.size() = " << v2.size() << std::endl;
	return 0;
}
