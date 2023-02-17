#include <iostream>
#include <fstream>
#include "utils.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "set.hpp"

#include <map>
#include <vector>
#include <stack>
#include <set>

#include <time.h>

# define PRINT_RED "\033[31m"
# define PRINT_YELLOW "\033[33m"
# define PRINT_GREEN "\033[32m"
# define PRINT_RESET "\033[0m"

int main()
{
	std::vector<int> v1;
	ft::vector<int> v2;

	clock_t start, end;
	double result1, result2;

	start = clock();
	for (int i = 0; i < 1000000; i++)
		v1.push_back(i);
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		v2.push_back(i);
	end = clock();
	result2 = (double)(end - start) / 1000000;
	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;
	std::cout << "std::vector push_back time : " << result1 << std::endl;
	std::cout << "ft::vector push_back time : " << result2 << std::endl;
	std::cout << PRINT_RESET;

	start = clock();
	v1.insert(v1.begin(), v1.begin(), v1.end());
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	v2.insert(v2.begin(), v2.begin(), v2.end());
	end = clock();
	result2 = (double)(end - start) / 1000000;

	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;

	std::cout << "std::vector insert time : " << result1 << std::endl;
	std::cout << "ft::vector insert time : " << result2 << std::endl;

	std::cout << PRINT_RESET;

	start = clock();
	std::vector<int> v3(v1.rbegin(), v1.rend());
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	ft::vector<int> v4(v2.rbegin(), v2.rend());
	end = clock();
	result2 = (double)(end - start) / 1000000;

	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;

	std::cout << "std::vector constructor(with iterators) time : " << result1 << std::endl;
	std::cout << "ft::vector constructor(with iterators) time : " << result2 << std::endl;

	std::cout << PRINT_RESET;

	start = clock();
	for (int i = 0; i < 1000000; i++)
		v1.swap(v3);
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		v2.swap(v4);
	end = clock();
	result2 = (double)(end - start) / 1000000;
	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;

	std::cout << "std::vector swap time : " << result1 << std::endl;
	std::cout << "ft::vector swap time : " << result2 << std::endl;

	std::cout << PRINT_RESET;

	start = clock();
	for (int i = 0; i < 1000000; i++)
		v1.pop_back();
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		v2.pop_back();
	end = clock();
	result2 = (double)(end - start) / 1000000;
	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;

	std::cout << "std::vector pop_back time : " << result1 << std::endl;
	std::cout << "ft::vector pop_back time : " << result2 << std::endl;

	std::cout << PRINT_RESET;

	start = clock();
	for (int i = 0; i < 100000; i++)
		v1.erase(--v1.end());
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	for (int i = 0; i < 100000; i++)
		v2.erase(--v2.end());
	end = clock();
	result2 = (double)(end - start) / 1000000;
	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;

	std::cout << "std::vector erase time : " << result1 << std::endl;
	std::cout << "ft::vector erase time : " << result2 << std::endl;

	std::cout << PRINT_RESET;

	std::stack<int> s1;
	ft::stack<int> s2;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		s1.push(i);
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		s2.push(i);
	end = clock();
	result2 = (double)(end - start) / 1000000;
	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;

	std::cout << "std::stack push time : " << result1 << std::endl;
	std::cout << "ft::stack push time : " << result2 << std::endl;

	std::cout << PRINT_RESET;

	start = clock();
	for (int i = 0; i < 1000000; i++)
		s1.pop();
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		s2.pop();
	end = clock();
	result2 = (double)(end - start) / 1000000;
	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;

	std::cout << "std::stack pop time : " << result1 << std::endl;
	std::cout << "ft::stack pop time : " << result2 << std::endl;

	std::cout << PRINT_RESET;

	std::map<int, int> m1;
	ft::map<int, int> m2;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		m1.insert(std::make_pair(i, i));
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		m2.insert(ft::make_pair(i, i));
	end = clock();
	result2 = (double)(end - start) / 1000000;
	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;

	std::cout << "std::map insert time : " << result1 << std::endl;
	std::cout << "ft::map insert time : " << result2 << std::endl;

	std::cout << PRINT_RESET;

	start = clock();
	std::map<int, int> m3(m1.rbegin(), m1.rend());
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	ft::map<int, int> m4(m2.rbegin(), m2.rend());
	end = clock();
	result2 = (double)(end - start) / 1000000;
	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;

	std::cout << "std::map constructor(with iterators) time : " << result1 << std::endl;
	std::cout << "ft::map constructor(with iterators) time : " << result2 << std::endl;

	std::cout << PRINT_RESET;

	start = clock();
	for (int i = 0; i < 1000000; i++)
		m1.swap(m3);
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		m2.swap(m4);
	end = clock();
	result2 = (double)(end - start) / 1000000;
	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;

	std::cout << "std::map swap time : " << result1 << std::endl;
	std::cout << "ft::map swap time : " << result2 << std::endl;

	std::cout << PRINT_RESET;

	start = clock();
	for (int i = 0; i < 1000000; i++)
		m1.find(i);
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		m2.find(i);
	end = clock();
	result2 = (double)(end - start) / 1000000;
	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;

	std::cout << "std::map find time : " << result1 << std::endl;
	std::cout << "ft::map find time : " << result2 << std::endl;

	std::cout << PRINT_RESET;

	start = clock();
	for (int i = 0; i < 1000000; i++)
		m1.erase(i);
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		m2.erase(i);
	end = clock();
	result2 = (double)(end - start) / 1000000;
	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;

	std::cout << "std::map erase time : " << result1 << std::endl;
	std::cout << "ft::map erase time : " << result2 << std::endl;

	std::cout << PRINT_RESET;

	std::set<int> s3;
	ft::set<int> s4;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		s3.insert(i);
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		s4.insert(i);
	end = clock();
	result2 = (double)(end - start) / 1000000;
	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;

	std::cout << "std::set insert time : " << result1 << std::endl;
	std::cout << "ft::set insert time : " << result2 << std::endl;

	std::cout << PRINT_RESET;

	start = clock();
	std::set<int> s5(s3.rbegin(), s3.rend());
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	ft::set<int> s6(s4.rbegin(), s4.rend());
	end = clock();
	result2 = (double)(end - start) / 1000000;
	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;

	std::cout << "std::set constructor(with iterators) time : " << result1 << std::endl;
	std::cout << "ft::set constructor(with iterators) time : " << result2 << std::endl;

	std::cout << PRINT_RESET;

	start = clock();
	for (int i = 0; i < 1000000; i++)
		s3.erase(i);
	end = clock();
	result1 = (double)(end - start) / 1000000;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		s4.erase(i);
	end = clock();
	result2 = (double)(end - start) / 1000000;
	if (result1 * 20 < result2)
		std::cout << PRINT_RED << "FAIL❌" << std::endl;
	else if (result1 < result2)
		std::cout << PRINT_YELLOW << "WARNING⚠️" << std::endl;
	else
		std::cout << PRINT_GREEN << "OK✅" << std::endl;

	std::cout << "std::set erase time : " << result1 << std::endl;
	std::cout << "ft::set erase time : " << result2 << std::endl;

	std::cout << PRINT_RESET;
}