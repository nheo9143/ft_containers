#include <iostream>
#include <fstream>
#include "utils.hpp"
#include "vector.hpp"
#include <vector>
#include <unistd.h>
#include "map.hpp"
#include "set.hpp"

#include <map>

class Base {
	private:
		int i;
		Base();
	public:
		Base(int i) : i(i) {};
};

template <typename T> // enalbe_if_version
void swap(T &a, T &b, typename ft::enable_if<!ft::is_integral<T>::value, T >::type* = 0)
{
	T temp;

	temp = a;
	a = b;
	b = temp;
	std::cout << "template swap called" << std::endl;
}


// template <typename T> // non_enalbe_if version
// void swap(T &a, T &b)
// {
// 	T temp;

// 	temp = a;
// 	a = b;
// 	b = temp;
// 	std::cout << "template swap called" << std::endl;
// }

void swap(int a, int b)
{
	int temp;

	temp = a;
	a = b;
	b = temp;
	std::cout << "int swap called" << std::endl;
}

int main2()
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
	std::cout << "---------------------vector test---------------------" << std::endl;

	std::ofstream	ofs("real.txt");
	std::streambuf *origin = std::cout.rdbuf();
	std::cout.rdbuf(ofs.rdbuf());

	/* real vector */
	std::cout << "---------------------constructer test---------------------" << std::endl;
	std::vector<int> rv1;
	std::vector<int> rv2(5, 10);
	std::cout << "v2.size() = " << rv2.size() << std::endl;
	std::vector<int> rv3(rv2.begin(), rv2.end());

	/* push_back test */
	std::cout << std::endl << "---------------------push_back test---------------------" << std::endl;
	rv1.push_back(1);
	rv1.push_back(2);
	std::cout << "v1.size() = " << rv1.size() << std::endl;

	/* insert test */
	std::cout << std::endl << "---------------------insert test---------------------" << std::endl;
	rv1.insert(rv1.begin(), 3);
	std::cout << "v1.size() = " << rv1.size() << std::endl;
	rv1.insert(rv1.begin(), 4, 5);
	std::cout << "v1.size() = " << rv1.size() << std::endl;

	/* erase test */
	std::cout << std::endl << "---------------------erase test---------------------" << std::endl;
	std::vector<int>::iterator rit = rv1.begin();
	rit++;
	std::vector<int>::iterator rit2 = rv1.erase(rit);
	std::cout << "v1.size() = " << rv1.size() << std::endl;
	std::cout << "position of erased position: " << rit2 - rv1.begin() << std::endl;

	rv1.clear();
	std::cout << std::endl << "after clear, v1.size() = " << rv1.size() << std::endl;
	rv1.insert(rv1.begin(), rv2.begin(), rv2.end());
	std::cout << "v1.size() = " << rv1.size() << std::endl;

	/* assign test */
	std::cout << std::endl << "---------------------assign test---------------------" << std::endl;
	rv1.assign(5, 10);
	std::cout << "after assgin(5,10), v1.size() = " << rv1.size() << std::endl;
	rv1.assign(rv2.begin(), rv2.end());
	std::cout << "after assgin(v2.begin(), v2.end()), v1.size() = " << rv1.size() << std::endl;
	rv2.assign(rv1.begin(), rv1.end());
	std::cout << "after assgin(v1.begin(), v1.end()), v2.size() = " << rv2.size() << std::endl;
	std::vector<int> rv4(4);
	for (int i = 0; i < 4; i++)
		rv4[i] = i * 5;
	std::vector<int> rv5;
	rv5.assign(rv4.begin(), rv4.end());
	std::cout << "after assgin(v2.begin(), v2.end()), v5.size() = " << rv5.size() << std::endl;

	/* swap test */
	std::cout << std::endl << "---------------------swap test---------------------" << std::endl;
	rv2.clear();
	std::cout << "before swap, v1.size() = " << rv1.size() << std::endl;
	std::cout << "before swap, v2.size() = " << rv2.size() << std::endl;
	rv1.swap(rv2);
	std::cout << "after swap, v1.size() = " << rv1.size() << std::endl;
	std::cout << "after swap, v2.size() = " << rv2.size() << std::endl;

	/* iterator test */
	std::cout << std::endl << "---------------------iterator test---------------------" << std::endl;
	rv3.push_back(1);
	rv3.push_back(2);
	rv3.push_back(3);
	rv3.push_back(4);
	rv3.push_back(5);
	for (std::vector<int>::iterator it = rv3.begin(); it != rv3.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	for (std::vector<int>::reverse_iterator it = rv3.rbegin(); it != rv3.rend(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;


	ofs.close();

	ofs.open("my.txt", std::ios::trunc);
	std::cout.rdbuf(ofs.rdbuf());
	/* vector constructer test */
	std::cout << "---------------------constructer test---------------------" << std::endl;
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
	v1.insert(v1.begin(), v2.begin(), v2.end());
	std::cout << "v1.size() = " << v1.size() << std::endl;

	/* assign test */
	std::cout << std::endl << "---------------------assign test---------------------" << std::endl;
	v1.assign(5, 10);
	std::cout << "after assgin(5,10), v1.size() = " << v1.size() << std::endl;
	v1.assign(v2.begin(), v2.end());
	std::cout << "after assgin(v2.begin(), v2.end()), v1.size() = " << v1.size() << std::endl;
	v2.assign(v1.begin(), v1.end());
	std::cout << "after assgin(v1.begin(), v1.end()), v2.size() = " << v2.size() << std::endl;
	ft::vector<int> v4(4);
	for (int i = 0; i < 4; i++)
		v4[i] = i * 5;
	ft::vector<int> v5;
	v5.assign(v4.begin(), v4.end());
	std::cout << "after assgin(v2.begin(), v2.end()), v5.size() = " << v5.size() << std::endl;

	/* swap test */
	std::cout << std::endl << "---------------------swap test---------------------" << std::endl;
	v2.clear();
	std::cout << "before swap, v1.size() = " << v1.size() << std::endl;
	std::cout << "before swap, v2.size() = " << v2.size() << std::endl;
	v1.swap(v2);
	std::cout << "after swap, v1.size() = " << v1.size() << std::endl;
	std::cout << "after swap, v2.size() = " << v2.size() << std::endl;

	/* iterator test */
	std::cout << std::endl << "---------------------iterator test---------------------" << std::endl;
	v3.push_back(1);
	v3.push_back(2);
	v3.push_back(3);
	v3.push_back(4);
	v3.push_back(5);
	for (ft::vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	for (ft::vector<int>::reverse_iterator it = v3.rbegin(); it != v3.rend(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout.rdbuf(origin);
	ofs.close();

	system("diff my.txt real.txt > diff");

	std::ifstream ifs("diff");

	std::string str;
	std::getline(ifs, str);
	if (str.empty())
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAIL" << std::endl;


	std::cout << "---------------------map test---------------------" << std::endl;
	ft::map<int, int> mp;
	ft::pair<int, int> pr;
	pr.first = 1;
	pr.second = 2;
	
	/* insert test */
	std::cout << std::endl << "---------------------insert test---------------------" << std::endl;
	mp.insert(ft::pair<int, int>(1, 0));
	mp.insert(ft::pair<int, int>(10, 0));
	mp.insert(ft::pair<int, int>(5, 0));
	mp.insert(ft::pair<int, int>(3, 0));
	mp.insert(ft::pair<int, int>(7, 0));
	mp.insert(ft::pair<int, int>(9, 0));
	mp.insert(ft::pair<int, int>(8, 0));
	mp.insert(ft::pair<int, int>(6, 0));
	mp.insert(ft::pair<int, int>(4, 0));
	mp.insert(ft::pair<int, int>(2, 0));
	ft::map<int, std::string> mp2;
	ft::pair<ft::map<int, std::string>::iterator, bool> mit1 = mp2.insert(ft::pair<int, std::string>(42, "lol"));
	ft::pair<ft::map<int, std::string>::iterator, bool> mit2 = mp2.insert(ft::pair<int, std::string>(42, "mdr"));
	ft::pair<ft::map<int, std::string>::iterator, bool> mit3 = mp2.insert(ft::pair<int, std::string>(50, "mdr"));
	ft::pair<ft::map<int, std::string>::iterator, bool> mit4 = mp2.insert(ft::pair<int, std::string>(35, "funny"));
	ft::pair<ft::map<int, std::string>::iterator, bool> mit5 = mp2.insert(ft::pair<int, std::string>(35, "bunny"));
	ft::pair<ft::map<int, std::string>::iterator, bool> mit6 = mp2.insert(ft::pair<int, std::string>(21, "fizz"));
	ft::pair<ft::map<int, std::string>::iterator, bool> mit7 = mp2.insert(ft::pair<int, std::string>(38, "buzz"));
	ft::printPair(*mit1.first);
	std::cout << std::boolalpha;
	std::cout << "inserted? " << mit1.second << std::endl;
	ft::printPair(*mit2.first);
	std::cout << "inserted? " << mit2.second << std::endl;
	ft::printPair(*mit3.first);
	std::cout << "inserted? " << mit3.second << std::endl;
	ft::printPair(*mit4.first);
	std::cout << "inserted? " << mit4.second << std::endl;
	ft::printPair(*mit5.first);
	std::cout << "inserted? " << mit5.second << std::endl;
	ft::printPair(*mit6.first);
	std::cout << "inserted? " << mit6.second << std::endl;
	ft::printPair(*mit7.first);
	std::cout << "inserted? " << mit7.second << std::endl;
	ft::map<int, std::string> mp3;

	/* erase test */
	std::cout << std::endl << "---------------------erase test---------------------" << std::endl;
	mp3.insert(mp2.begin(), mp2.end());
	// for (ft::map<int, std::string>::iterator mitt = mp3.begin(); mitt != --mp3.end(); mitt++)
	mp3[5] = "HI";
	mp3[4] = "...";
	mp3[1] = "\"\"";
	mp3[100] = "WOW";
	mp3[10] = "10";
	mp3.clear();
	for (int i = 0; i < 10; i++) {
		mp3.insert(ft::pair<int, std::string>(i, "123"));
	}
	ft::map<int, std::string>::iterator mitt = mp3.begin();
	// mp3.erase(++(++mitt));
	// mp3.erase(--(--mp3.end()));
	// mp3.erase(--(--mp3.end()), mp3.end());
	mp3.erase(++mp3.begin());
	mp3.erase(mp3.begin());
	mp3.erase(--mp3.end());
	mp3.erase(mp3.begin(), ++(++(++mp3.begin())));
	mp3.erase(--(--(--mp3.end()), --mp3.end()));
	// mp3[11] = "101";
	// mp3[10] = "100";
	std::cout << std::endl;
	for (ft::map<int, std::string>::iterator mitt = mp3.begin(); mitt != mp3.end(); mitt++)
		ft::printPair(*mitt);

	/* iterator test */
	std::cout << std::endl << "---------------------iterator test---------------------" << std::endl;
	for (ft::map<int, std::string>::iterator itt = mp2.begin(); itt != mp2.end(); itt++) {
		ft::node<ft::pair<const int, std::string> > node = *itt;
		std::cout << "node: " << node._value.first << " " << node._value.second << std::endl;
	}
	/* reverse iterator test */
	std::cout << std::endl << "---------------------reverse iterator test---------------------" << std::endl;
	for (ft::map<int, std::string>::reverse_iterator itt = mp2.rbegin(); itt != mp2.rend(); itt++) {
		ft::node<ft::pair<const int, std::string> > node = *itt;
		std::cout << "node: " << node._value.first << " " << node._value.second << std::endl;
	}

	/* find test */
	std::cout << std::endl << "---------------------find test---------------------" << std::endl;
	ft::map<int, std::string>::iterator it4 = mp2.find(21);
	ft::map<int, std::string>::iterator it5 = mp2.find(38);
	ft::map<int, std::string>::iterator it6 = mp2.find(100);
	ft::map<int, std::string>::iterator it7 = mp2.find(0);
	ft::map<int, std::string>::iterator it8 = mp2.find(1);
	std::cout << "it4: " << it4->first << " " << it4->second << std::endl;
	std::cout << "it5: " << it5->first << " " << it5->second << std::endl;
	std::cout << "it6: " << it6->first << " " << it6->second << std::endl;
	std::cout << "it7: " << it7->first << " " << it7->second << std::endl;
	std::cout << "it8: " << it8->first << " " << it8->second << std::endl;

	ft::set<int> s1;
	s1.insert(1);
	s1.erase(s1.begin());
	return 0;
}

int main()
{
	main2();
	system("leaks a.out");
}