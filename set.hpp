#ifndef SET_HPP
# define SET_HPP

# include "tree.hpp"
# include "utils.hpp"
#include "tree_iterator.hpp"
# include <memory>

namespace ft
{
	template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
	class set
	{
		public:
			typedef T										key_type;
			typedef T										value_type;
			typedef Compare									key_compare;
			typedef Compare									value_compare;
			typedef Alloc									allocator_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type			size_type;

			typedef ft::tree_const_iterator<value_type>			iterator;
			typedef ft::tree_const_iterator<value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			tree<value_type, key_compare, allocator_type>	_tree;
			key_compare										_comp;
			allocator_type									_a;

		public:
			explicit set(const key_compare& comp = key_compare(), const allocator_type& a = allocator_type()) : _tree(value_compare(comp)), _comp(comp), _a(a) {}
			template <typename InputIterator>
			set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& a = allocator_type()) : _tree(value_compare(comp)), _comp(comp), _a(a) { _tree.insert(first, last); }
			set(const set& x) : _tree(x._tree), _comp(x._comp), _a(x._a) {}
			virtual ~set() {}

			set& operator=(const set& x)
			{
				_tree = x._tree;
				_comp = x._comp;
				_a = x._a;
				return *this;
			}

			iterator begin() { return _tree.begin(); }
			const_iterator begin() const { return _tree.begin(); }
			iterator end() { return _tree.end(); }
			const_iterator end() const { return _tree.end(); }
			reverse_iterator rbegin() { return _tree.rbegin(); }
			const_reverse_iterator rbegin() const { return _tree.rbegin(); }
			reverse_iterator rend() { return _tree.rend(); }
			const_reverse_iterator rend() const { return _tree.rend(); }
			bool empty() const { return _tree.empty(); }
			size_type size() const { return _tree.size(); }
			size_type max_size() const { return _tree.max_size(); }
			pair<iterator, bool> insert(const value_type& val)
			{
				return _tree.insert(val);
			}
			iterator insert(iterator position, const value_type& val)
			{
				(void)position;
				_tree.insert(val);
				return find(val);
			}
			template <typename InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				_tree.insert(first, last);
			}
			void erase(iterator position) { _tree.erase(position); }
			size_type erase(const key_type& k) { return _tree.erase(k); }
			void erase(iterator first, iterator last) { _tree.erase(first, last); }
			void swap(set& x) {
				_tree.swap(x._tree);
				ft::swap(_comp, x._comp);
				ft::swap(_a, x._a);
			}
			void clear() { _tree.clear(); }
			key_compare key_comp() const { return _comp; }
			value_compare value_comp() const { return _comp; }
			iterator find(const key_type& k) { return _tree.find(k); }
			const_iterator find(const key_type& k) const { return _tree.find(k); }
			size_type count(const key_type& k) const { return _tree.count(k); }
			iterator lower_bound(const key_type& k) {
				iterator it = begin();
				while (it != end() && _comp(*it, k))
					++it;
				return it;
			}
			const_iterator lower_bound(const key_type& k) const {
				const_iterator it = begin();
				while (it != end() && _comp(*it, k))
					++it;
				return it;
			}
			iterator upper_bound(const key_type& k) {
				iterator it = begin();
				while (it != end() && !_comp(k, *it))
					++it;
				return it;
			}
			const_iterator upper_bound(const key_type& k) const {
				const_iterator it = begin();
				while (it != end() && !_comp(k, *it))
					++it;
				return it;
			}
			pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
				return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
			}
			pair<iterator, iterator> equal_range(const key_type& k) {
				return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
			}
			allocator_type get_allocator() const { return _a; }
	};

	template <typename T, typename Compare, typename Alloc>
	bool operator==(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		typename set<T, Compare, Alloc>::const_iterator it1 = lhs.begin();
		typename set<T, Compare, Alloc>::const_iterator it2 = rhs.begin();
		while (it1 != lhs.end() && it2 != rhs.end())
		{
			if (*it1 != *it2)
				return false;
			++it1;
			++it2;
		}
		return it1 == lhs.end() && it2 == rhs.end();
	}
	template <typename T, typename Compare, typename Alloc>
	bool operator!=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) { return !(lhs == rhs); }
	template <typename T, typename Compare, typename Alloc>
	bool operator<(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <typename T, typename Compare, typename Alloc>
	bool operator<=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) { return !(rhs < lhs); }
	template <typename T, typename Compare, typename Alloc>
	bool operator>(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) { return rhs < lhs; }
	template <typename T, typename Compare, typename Alloc>
	bool operator>=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) { return !(lhs < rhs); }
	template <typename T, typename Compare, typename Alloc>
	void swap(set<T, Compare, Alloc>& x, set<T, Compare, Alloc>& y) { x.swap(y); }
}

#endif