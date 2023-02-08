#ifndef MAP_HPP
# define MAP_HPP

# include "utils.hpp"
# include "pair.hpp"
# include "tree.hpp"
# include <memory>
// # include <map>

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
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type			size_type;

			// typedef typename ft::tree_iterator<pointer>					iterator;
			// typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			// typedef typename ft::tree_iterator<const_pointer>			const_iterator;
			// typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			class value_compare : public std::binary_function<value_type, value_type, bool>
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
			tree<value_type, value_compare, allocator_type>			_tree;
			key_compare												_comp;
			allocator_type											_a;
		
		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(value_compare(comp), _a), _comp(comp), _a(alloc) {};
			// template <typename InputIterator>
			// map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& a = allocator_type()) : _tree(), _comp(comp), _a(a) { insert(first, last); };
			explicit map(const map& x) : _tree(x._tree), _comp(x._comp), _a(x._a) {};
			~map() {};

			map& operator=(const map& x)
			{
				_tree = x._tree;
				_comp = x._comp;
				_a = x._a;
				return *this;
			};

			// iterator begin() { return _tree.begin(); };
			// const_iterator begin() const { return _tree.begin(); };
			// iterator end() { return _tree.end(); };
			// const_iterator end() const { return _tree.end(); };
			// reverse_iterator rbegin() { return _tree.rbegin(); };
			// const_reverse_iterator rbegin() const { return _tree.rbegin(); };
			// reverse_iterator rend() { return _tree.rend(); };
			// const_reverse_iterator rend() const { return _tree.rend(); };

			bool empty() const { return _tree.empty(); };
			size_type size() const { return _tree.size(); };
			size_type max_size() const { return _tree.max_size(); };

			// mapped_type& operator[](const key_type& k)
			// {
			// 	iterator it = lower_bound(k);
			// 	if (it == end() || _comp(k, (*it).first))
			// 		it = insert(it, value_type(k, mapped_type()));
			// 	return (*it).second;
			// };

			// ft::pair<iterator, bool> insert(const value_type& val)
			// {
			// 	_tree.insert(val);
			// 	return ft::pair<iterator, bool>(val);
			// };

			// iterator insert(iterator position, const value_type& val)
			// {
			// 	(void)position;
			// 	return _tree.insert(position, val).first;
			// };

			// template <typename InputIterator>
			// void insert(InputIterator first, InputIterator last)
			// {
			// 	_tree.insert(first, last);
			// };

			// void erase(iterator position) { _tree.erase(position); };
			size_type erase(const key_type& k) { return _tree.erase(k); };
			// void erase(iterator first, iterator last) { _tree.erase(first, last); };

			void swap(map& x) {
				_tree.swap(x._tree);
				ft::swap(_comp, x._comp);
				ft::swap(_a, x._a);
			};

			void clear() { _tree.clear(); };

			key_compare key_comp() const { return key_compare(); };

			value_compare value_comp() const { return value_compare(key_compare()); };

			// iterator find(const key_type& k) { return _tree.find(k); };
			// const_iterator find(const key_type& k) const { return _tree.find(k); };

			// size_type count(const key_type& k) const { return _tree.count(k); };

			// iterator lower_bound(const key_type& k) { return _tree.lower_bound(k); };
			// const_iterator lower_bound(const key_type& k) const { return _tree.lower_bound(k); };

			// iterator upper_bound(const key_type& k) { return _tree.upper_bound(k); };
			// const_iterator upper_bound(const key_type& k) const { return _tree.upper_bound(k); };

			// ft::pair<iterator, iterator> equal_range(const key_type& k) { return _tree.equal_range(k); };
			// ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const { return _tree.equal_range(k); }

			allocator_type get_allocator() const { return _a; };
	};
}

#endif