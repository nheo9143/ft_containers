#ifndef MAP_HPP
# define MAP_HPP

# include "utils.hpp"
# include "pair.hpp"
# include "red_black_tree.hpp"
# include <memory>

namespace ft
{
	template <typename Key, typename T, typename Compare = ft::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef ft::pair<const key_type, mapped_type>					value_type;
			typedef Compare													key_compare;
			typedef Alloc													allocator_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef size_t		size_type;
			typedef ptrdiff_t	difference_type;

			typedef ft::tree_iterator<value_type>				iterator;
			typedef ft::tree_const_iterator<value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			class value_compare : public ft::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

		private:
			ft::red_black_tree<value_type, value_compare, allocator_type>		_tree;
			key_compare															_comp;
			allocator_type														_a;
		
		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(value_compare(comp)), _comp(comp), _a(alloc) {};

			template <typename InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& a = allocator_type()) : _tree(value_compare(comp)), _comp(comp), _a(a) { insert(first, last); };
			explicit map(const map& x) : _tree(x._tree), _comp(x._comp), _a(x._a) {};
			virtual ~map() {};

			map& operator=(const map& x)
			{
				_tree = x._tree;
				_comp = x._comp;
				_a = x._a;
				return *this;
			};

			iterator begin() { return _tree.begin(); };
			const_iterator begin() const { return _tree.begin(); };
			iterator end() { return _tree.end(); };
			const_iterator end() const { return _tree.end(); };
			reverse_iterator rbegin() { return _tree.rbegin(); };
			const_reverse_iterator rbegin() const { return _tree.rbegin(); };
			reverse_iterator rend() { return _tree.rend(); };
			const_reverse_iterator rend() const { return _tree.rend(); };

			bool empty() const { return _tree.empty(); };
			size_type size() const { return _tree.size(); };
			size_type max_size() const { return _tree.max_size(); };

			mapped_type& operator[](const key_type& k)
			{
				iterator it = 0;
				it = insert(it, value_type(k, mapped_type()));
				return (*it).second;
			};

			ft::pair<iterator, bool> insert(const value_type& val)
			{
				return _tree.insert(val);
			};

			iterator insert(iterator position, const value_type& val)
			{
				(void)position;
				return _tree.insert(position, val);
			};

			template <typename InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				_tree.insert(first, last);
			};

			void erase(iterator position) { _tree.erase(position); };
			size_type erase(const key_type& k) { return _tree.erase(ft::make_pair(k, mapped_type())); };
			void erase(iterator first, iterator last) { _tree.erase(first, last); };

			void swap(map& x) {
				_tree.swap(x._tree);
				ft::swap(_comp, x._comp);
				ft::swap(_a, x._a);
			};

			void clear() { _tree.clear(); };

			key_compare key_comp() const { return key_compare(); };

			value_compare value_comp() const { return value_compare(key_compare()); };

			iterator find(const key_type& k) { return _tree.find(ft::make_pair(k, mapped_type())); };

			const_iterator find(const key_type& k) const { return _tree.find(ft::make_pair(k, mapped_type())); };

			size_type count(const key_type& k) const { return _tree.count(ft::make_pair(k, mapped_type())); };

			iterator lower_bound(const key_type& k) {
				iterator it = begin();
				while (it != end() && _comp((*it).first, k))
					++it;
				return it;
			};

			const_iterator lower_bound(const key_type& k) const {
				const_iterator it = begin();
				while (it != end() && _comp((*it).first, k))
					++it;
				return it;
			};

			iterator upper_bound(const key_type& k) {
				iterator it = begin();
				while (it != end() && !_comp(k, (*it).first))
					++it;
				return it;
			};

			const_iterator upper_bound(const key_type& k) const {
				const_iterator it = begin();
				while (it != end() && !_comp(k, (*it).first))
					++it;
				return it;
			};

			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
				return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
			};

			ft::pair<iterator, iterator> equal_range(const key_type& k) {
				return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
			};

			allocator_type get_allocator() const { return _a; };
	};
	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		typename map<Key, T, Compare, Alloc>::const_iterator it1 = lhs.begin();
		typename map<Key, T, Compare, Alloc>::const_iterator it2 = rhs.begin();
		while (it1 != lhs.end())
		{
			if (*it1 != *it2)
				return false;
			++it1;
			++it2;
		}
		return it1 == lhs.end() && it2 == rhs.end();
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs == rhs);
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(rhs < lhs));
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	};

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif