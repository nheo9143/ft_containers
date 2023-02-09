#ifndef TREE_HPP
# define TREE_HPP

# include "utils.hpp"
# include "pair.hpp"
# include "tree_iterator.hpp"
# include "iterator.hpp"
# include "node.hpp"

namespace ft
{
	template <typename T, typename Compare, typename Alloc = std::allocator<T> >
	class tree
	{
		private:
			typedef node<T>		node;
			typedef node*		node_ptr;
			typedef typename Alloc::template rebind<node>::other	node_allocator;

		public:
			typedef T			value_type;
			typedef Compare		value_compare;
			typedef Alloc		allocator_type;

			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef size_t		size_type;
			typedef ptrdiff_t	difference_type;
			typedef tree_iterator<T>	iterator;
			typedef tree_iterator<const T>	const_iterator;
			typedef reverse_iterator<iterator>	reverse_iterator;
			// typedef reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			node_ptr		_root;
			node_ptr		_end;
			size_type		_size;
			value_compare	_comp;
			node_allocator	_alloc;

		public:
			explicit tree(const value_compare& comp, const allocator_type& alloc = allocator_type()) : _root(0), _end(0), _size(0), _comp(comp), _alloc(alloc) {
				_end = _alloc.allocate(1);
				_alloc.construct(_end, node());
				_end->_color = BLACK;
			}

			template <class InputIterator>
			tree(InputIterator first, InputIterator last, const value_compare& comp, const allocator_type& alloc = allocator_type()) : _root(0), _end(0), _size(0), _comp(comp), _alloc(alloc) {
				// insert(first, last);
			}

			tree(const tree& ref) : _root(0), _end(0), _size(0), _comp(ref._comp), _alloc(ref._alloc) {
				// insert(ref.begin(), ref.end());
			}

			virtual ~tree() {
				// clear();
				_alloc.destroy(_end);
				_alloc.deallocate(_end, 1);
			}

			// tree&	operator=(const tree& ref) {
			// 	if (this != &ref) {
			// 		clear();
			// 		_comp = ref._comp;
			// 		insert(ref.begin(), ref.end());
			// 	}
			// 	return (*this);
			// }

			// iterator	begin() {
			// 	node_ptr tmp = _root;
			// 	while (tmp->_left)
			// 		tmp = tmp->_left;
			// 	return (iterator(tmp, _end));
			// }

			// const_iterator	begin() const {
			// 	node_ptr tmp = _root;
			// 	while (tmp->_left)
			// 		tmp = tmp->_left;
			// 	return (const_iterator(tmp, _end));
			// }

			// iterator	end() {
			// 	return (iterator(_end, _end));
			// }

			// const_iterator	end() const {
			// 	return (const_iterator(_end, _end));
			// }

			// reverse_iterator	rbegin() {
			// 	return (reverse_iterator(end()));
			// }

			// const_reverse_iterator	rbegin() const {
			// 	return (const_reverse_iterator(end()));
			// }

			// reverse_iterator	rend() {
			// 	return (reverse_iterator(begin()));
			// }

			// const_reverse_iterator	rend() const {
			// 	return (const_reverse_iterator(begin()));
			// }

			bool	empty() const {
				return (_size == 0);
			}

			size_type	size() const {
				return (_size);
			}

			size_type	max_size() const {
				return (_alloc.max_size());
			}

			void	swap(tree& ref) {
				ft::swap(_root, ref._root);
				ft::swap(_end, ref._end);
				ft::swap(_size, ref._size);
				ft::swap(_comp, ref._comp);
				ft::swap(_alloc, ref._alloc);
			}

			// std::pair<iterator, bool>	insert(const value_type& val) {
			// 	node_ptr tmp = _root;
			// 	node_ptr parent = 0;
			// 	while (tmp) {
			// 		parent = tmp;
			// 		if (_comp(val, tmp->_value))
			// 			tmp = tmp->_left;
			// 		else if (_comp(tmp->_value, val))
			// 			tmp = tmp->_right;
			// 		else
			// 			return (std::make_pair(iterator(tmp, _end), false));
			// 	}
			// 	tmp = _alloc.allocate(1);
			// 	_alloc.construct(tmp, node(val));
			// 	tmp->_parent = parent;
			// 	if (!parent)
			// 		_root = tmp;
			// 	else if (_comp(val, parent->_value))
			// 		parent->_left = tmp;
			// 	else
			// 		parent->_right = tmp;
			// 	++_size;
			// 	insert_fixup(tmp);
			// 	return (std::make_pair(iterator(tmp, _end), true));
			// }
	};
}

#endif