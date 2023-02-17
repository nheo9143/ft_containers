#include <iostream>
#include <fstream>
#include "utils.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "set.hpp"

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
	// unsigned int a1 = 1;
	// unsigned int a2 = 2;
	// int b1 = 3;
	// int b2 = 4;
	// std::string c1 = "hello";
	// std::string c2 = "world";

	// ::swap(a1, a2);
	// ::swap(b1, b2);
	// ::swap(c1, c2);

	std::ofstream	ofs("./logs/ft_vector.txt");
	std::streambuf *origin = std::cout.rdbuf();
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

	/* reverse_iterator test */
	std::cout << std::endl << "---------------------reverse_iterator test---------------------" << std::endl;
	ft::vector<int>::reverse_iterator rit = v3.rbegin();
	std::cout << "v3.rbegin() = " << *rit << std::endl;
	rit++;
	std::cout << "v3.rbegin()++ = " << *rit << std::endl;
	rit--;
	std::cout << "v3.rbegin()-- = " << *rit << std::endl;
	rit += 2;
	std::cout << "v3.rbegin() += 2 = " << *rit << std::endl;

	std::cout.rdbuf(origin);
	ofs.close();

	ofs.open("./logs/ft_map.txt");
	std::cout.rdbuf(ofs.rdbuf());

	/* map test */
	std::cout << "---------------------map test---------------------" << std::endl;

	/* constructer test */
	std::cout << std::endl << "---------------------constructer test---------------------" << std::endl;
	ft::map<int, int> mp;
	ft::map<int, std::string> mp2;
	mp.insert(ft::pair<int, int>(1, 0));
	mp.insert(ft::pair<int, int>(10, 0));
	ft::map<int, int> mp4(mp);
	ft::map<int, int> mp5(mp.begin(), mp.end());

	/* insert test */
	std::cout << std::endl << "---------------------insert test---------------------" << std::endl;
	mp.insert(ft::pair<int, int>(5, 0));
	mp.insert(ft::pair<int, int>(3, 0));
	mp.insert(ft::pair<int, int>(7, 0));
	mp.insert(ft::pair<int, int>(9, 0));
	mp.insert(ft::pair<int, int>(8, 0));
	mp.insert(ft::pair<int, int>(6, 0));
	mp.insert(ft::pair<int, int>(4, 0));
	mp.insert(ft::pair<int, int>(2, 0));
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

	/* erase test */
	std::cout << std::endl << "---------------------erase test---------------------" << std::endl;
	ft::map<int, std::string> mp3;
	mp3.insert(mp2.begin(), mp2.end());
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
	mp3.erase(++(++mitt));
	mp3.erase(--(--mp3.end()));
	mp3.erase(--(--mp3.end()), mp3.end());
	mp3.erase(++mp3.begin());
	mp3.erase(mp3.begin());
	mp3.erase(--mp3.end());
	mp3.erase(mp3.begin(), ++(++(++mp3.begin())));
	mp3[11] = "101";
	mp3[10] = "100";
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
	if (it4 != mp2.end())
		std::cout << "it4: " << it4->first << " " << it4->second << std::endl;
	if (it5 != mp2.end())
		std::cout << "it5: " << it5->first << " " << it5->second << std::endl;
	if (it6 != mp2.end())
		std::cout << "it6: " << it6->first << " " << it6->second << std::endl;
	if (it7 != mp2.end())
		std::cout << "it7: " << it7->first << " " << it7->second << std::endl;
	if (it8 != mp2.end())
		std::cout << "it8: " << it8->first << " " << it8->second << std::endl;
	/* count test */
	std::cout << std::endl << "---------------------count test---------------------" << std::endl;
	std::cout << "count 21: " << mp2.count(21) << std::endl;
	std::cout << "count 38: " << mp2.count(38) << std::endl;
	std::cout << "count 100: " << mp2.count(100) << std::endl;
	std::cout << "count 0: " << mp2.count(0) << std::endl;
	std::cout << "count 1: " << mp2.count(1) << std::endl;
	/* lower bound test */
	std::cout << std::endl << "---------------------lower bound test---------------------" << std::endl;
	ft::map<int, std::string>::iterator it9 = mp2.lower_bound(21);
	ft::map<int, std::string>::iterator it10 = mp2.lower_bound(38);
	ft::map<int, std::string>::iterator it11 = mp2.lower_bound(100);
	if (it9 != mp2.end())
		std::cout << "it9: " << it9->first << " " << it9->second << std::endl;
	if (it10 != mp2.end())
		std::cout << "it10: " << it10->first << " " << it10->second << std::endl;
	if (it11 != mp2.end())
		std::cout << "it11: " << it11->first << " " << it11->second << std::endl;
	/* upper bound test */
	std::cout << std::endl << "---------------------upper bound test---------------------" << std::endl;
	ft::map<int, std::string>::iterator it12 = mp2.upper_bound(21);
	ft::map<int, std::string>::iterator it13 = mp2.upper_bound(38);
	ft::map<int, std::string>::iterator it14 = mp2.upper_bound(100);
	if (it12 != mp2.end())
		std::cout << "it12: " << it12->first << " " << it12->second << std::endl;
	if (it13 != mp2.end())
		std::cout << "it13: " << it13->first << " " << it13->second << std::endl;
	if (it14 != mp2.end())
		std::cout << "it14: " << it14->first << " " << it14->second << std::endl;
	/* equal range test */
	std::cout << std::endl << "---------------------equal range test---------------------" << std::endl;
	ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator> pr1 = mp2.equal_range(21);
	ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator> pr2 = mp2.equal_range(38);
	ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator> pr3 = mp2.equal_range(100);
	if (pr1.first != mp2.end() && pr1.second != mp2.end())
		std::cout << "pr1: " << pr1.first->first << " " << pr1.first->second << " " << pr1.second->first << " " << pr1.second->second << std::endl;
	if (pr2.first != mp2.end() && pr2.second != mp2.end())
		std::cout << "pr2: " << pr2.first->first << " " << pr2.first->second << " " << pr2.second->first << " " << pr2.second->second << std::endl;
	if (pr3.first != mp2.end() && pr3.second != mp2.end())
		std::cout << "pr3: " << pr3.first->first << " " << pr3.first->second << " " << pr3.second->first << " " << pr3.second->second << std::endl;

	std::cout.rdbuf(origin);
	ofs.close();

	ofs.open("./logs/ft_stack.txt");
	std::cout.rdbuf(ofs.rdbuf());

	/* stack test */
	std::cout << std::endl << "---------------------stack test---------------------" << std::endl;

	/* constructor test */
	std::cout << std::endl << "---------------------constructor test---------------------" << std::endl;
	ft::stack<int> st1;
	st1.push(1);
	ft::stack<int> st2(st1);
	ft::stack<int> st3;

	/* empty test */
	std::cout << std::endl << "---------------------empty test---------------------" << std::endl;
	std::cout << "st1 empty: " << st1.empty() << std::endl;
	std::cout << "st2 empty: " << st2.empty() << std::endl;
	std::cout << "st3 empty: " << st3.empty() << std::endl;

	/* push test */
	std::cout << std::endl << "---------------------push test---------------------" << std::endl;
	st3.push(2);
	st3.push(3);
	st3.push(4);

	/* size test */
	std::cout << std::endl << "---------------------size test---------------------" << std::endl;
	std::cout << "st1 size: " << st1.size() << std::endl;
	std::cout << "st2 size: " << st2.size() << std::endl;
	std::cout << "st3 size: " << st3.size() << std::endl;

	/* top test */
	std::cout << std::endl << "---------------------top test---------------------" << std::endl;
	std::cout << "st1 top: " << st1.top() << std::endl;
	std::cout << "st2 top: " << st2.top() << std::endl;
	std::cout << "st3 top: " << st3.top() << std::endl;

	/* pop test */
	std::cout << std::endl << "---------------------pop test---------------------" << std::endl;
	st3.pop();
	std::cout << "st3 top: " << st3.top() << std::endl;
	st3.pop();
	std::cout << "st3 top: " << st3.top() << std::endl;
	st3.pop();
	std::cout << "st3 empty: " << st3.empty() << std::endl;

	std::cout.rdbuf(origin);
	ofs.close();

	ofs.open("./logs/ft_set.txt");
	std::cout.rdbuf(ofs.rdbuf());

	/* set test */
	std::cout << std::endl << "---------------------set test---------------------" << std::endl;

	/* constructor test */
	std::cout << std::endl << "---------------------constructor test---------------------" << std::endl;
	ft::set<int> s1;
	s1.insert(1);
	s1.insert(2);
	s1.insert(3);
	ft::set<int> s2(s1);
	ft::set<int> s3(s2.begin(), s2.end());

	/* iterator test */
	std::cout << std::endl << "---------------------iterator test---------------------" << std::endl;
	for (ft::set<int>::iterator it = s3.begin(); it != s3.end(); it++) {
		std::cout << "value: " << *it << std::endl;
	}
	/* reverse iterator test */
	std::cout << std::endl << "---------------------reverse iterator test---------------------" << std::endl;
	for (ft::set<int>::reverse_iterator it = s3.rbegin(); it != s3.rend(); it++) {
		std::cout << "value: " << *it << std::endl;
	}
	/* empty test */
	std::cout << std::endl << "---------------------empty test---------------------" << std::endl;
	std::cout << "s1.empty(): " << s1.empty() << std::endl;
	std::cout << "s2.empty(): " << s2.empty() << std::endl;
	std::cout << "s3.empty(): " << s3.empty() << std::endl;
	/* size test */
	std::cout << std::endl << "---------------------size test---------------------" << std::endl;
	std::cout << "s1.size(): " << s1.size() << std::endl;
	std::cout << "s2.size(): " << s2.size() << std::endl;
	std::cout << "s3.size(): " << s3.size() << std::endl;

	/* max size test */
	std::cout << std::endl << "---------------------max size test---------------------" << std::endl;
	std::cout << "s1.max_size(): " << s1.max_size() << std::endl;
	std::cout << "s2.max_size(): " << s2.max_size() << std::endl;
	std::cout << "s3.max_size(): " << s3.max_size() << std::endl;
	/* insert test */
	std::cout << std::endl << "---------------------insert test---------------------" << std::endl;
	ft::set<int> s4;
	s4.insert(1);
	s4.insert(2);
	s4.insert(3);
	s4.insert(4);
	s4.insert(5);
	s4.insert(6);
	ft::set<int> s5;
	s5.insert(s4.begin(), s4.end());
	for (ft::set<int>::iterator it = s5.begin(); it != s5.end(); it++) {
		std::cout << "value: " << *it << std::endl;
	}
	/* erase test */
	std::cout << std::endl << "---------------------erase test---------------------" << std::endl;
	s5.erase(1);
	s5.erase(2);
	s5.erase(3);
	s5.erase(4);
	s5.erase(5);
	s5.erase(6);
	for (ft::set<int>::iterator it = s5.begin(); it != s5.end(); it++) {
		std::cout << "value: " << *it << std::endl;
	}
	/* swap test */
	std::cout << std::endl << "---------------------swap test---------------------" << std::endl;
	s5.swap(s4);
	for (ft::set<int>::iterator it = s5.begin(); it != s5.end(); it++) {
		std::cout << "value: " << *it << std::endl;
	}
	/* clear test */
	std::cout << std::endl << "---------------------clear test---------------------" << std::endl;
	s5.clear();
	for (ft::set<int>::iterator it = s5.begin(); it != s5.end(); it++) {
		std::cout << "value: " << *it << std::endl;
	}
	/* key comp test */
	std::cout << std::endl << "---------------------key comp test---------------------" << std::endl;
	ft::set<int>::key_compare kc = s5.key_comp();
	std::cout << "kc(1, 2): " << kc(1, 2) << std::endl;
	std::cout << "kc(2, 1): " << kc(2, 1) << std::endl;
	std::cout << "kc(1, 1): " << kc(1, 1) << std::endl;
	/* value comp test */
	std::cout << std::endl << "---------------------value comp test---------------------" << std::endl;
	ft::set<int>::value_compare vc = s5.value_comp();
	std::cout << "vc(1, 2): " << vc(1, 2) << std::endl;
	std::cout << "vc(2, 1): " << vc(2, 1) << std::endl;
	std::cout << "vc(1, 1): " << vc(1, 1) << std::endl;
	/* find test */
	std::cout << std::endl << "---------------------find test---------------------" << std::endl;
	s5.insert(1);
	s5.insert(2);
	s5.insert(3);
	s5.insert(4);
	s5.insert(5);
	s5.insert(6);
	ft::set<int>::iterator sit = s5.find(3);
	std::cout << "value: " << *sit << std::endl;
	/* count test */
	std::cout << std::endl << "---------------------count test---------------------" << std::endl;
	std::cout << "s5.count(3): " << s5.count(3) << std::endl;
	std::cout << "s5.count(4): " << s5.count(4) << std::endl;
	std::cout << "s5.count(5): " << s5.count(5) << std::endl;
	std::cout << "s5.count(6): " << s5.count(6) << std::endl;
	std::cout << "s5.count(7): " << s5.count(7) << std::endl;
	/* lower bound test */
	std::cout << std::endl << "---------------------lower bound test---------------------" << std::endl;
	sit = s5.lower_bound(3);
	std::cout << "value: " << *sit << std::endl;
	/* upper bound test */
	std::cout << std::endl << "---------------------upper bound test---------------------" << std::endl;
	sit = s5.upper_bound(3);
	std::cout << "value: " << *sit << std::endl;

	std::cout.rdbuf(origin);
	ofs.close();
	return 0;
}

int main(int ac, char *av[])
{
	(void)ac;
	(void)av;
	main2();
	system("leaks ft_container > leaks.txt");
	return 0;
}