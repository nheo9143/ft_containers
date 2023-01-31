#ifndef TREE_HPP
# define TREE_HPP

# include "utils.hpp"
# include "pair.hpp"
# include "tree_iterator.hpp"

# define RED		true
# define BLACK		false

namespace ft
{
	template <typename T>
	class node {

		T			_value;
		node*		_parent;
		node*		_left;
		node*		_right;
		bool		_color;

		node(): _value(), _parent(0), _left(0), _right(0), _color(RED) {}

		node(const T& value, node* parent = 0, node* left = 0, node* right = 0, bool color = RED) : _value(value), _parent(parent), _left(left), _right(right), _color(color) {}

		node(const node& ref) : _value(ref._value), _parent(ref._parent), _left(ref._left), _right(ref._right), _color(ref._color) {}
		
		virtual ~node() {}
		
		node&	operator=(const node& ref) {
			if (this != &ref) {
				this->_value = ref._value;
				this->_parent = ref._parent;
				this->_left = ref._left;
				this->_right = ref._right;
				this->_color = ref._color;
			}
			return (*this);
		}

		bool	operator==(const node& ref) const {
			return (this->_value == ref._value);
		}

		bool	operator!=(const node& ref) const {
			return (this->_value != ref._value);
		}

	};

	template <class T1, class T2>
	bool operator==(const node<T1>& lhs, const node<T2>& rhs) {
		return lhs == rhs;
	}
	
	template <class T1, class T2>
	bool operator!=(const node<T1>& lhs, const node<T2>& rhs) {
		return lhs != rhs;
	}

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

			typedef T&			reference;
			typedef const T&	const_reference;
			typedef T*			pointer;
			typedef const T*	const_pointer;
			typedef size_t		size_type;
			typedef ptrdiff_t	difference_type;
			typedef tree_iterator<T>	iterator;
			typedef tree_iterator<const T>	const_iterator;
			typedef tree_reverse_iterator<iterator>	reverse_iterator;
			typedef tree_reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			node_ptr		_root;
			node_ptr		_end;
			size_type		_size;
			value_compare	_comp;
			node_allocator	_alloc;

		public:
			explicit tree(const value_compare& comp = value_compare(), const allocator_type& alloc = allocator_type()) : _root(0), _end(0), _size(0), _comp(comp), _alloc(alloc) {
				_end = _alloc.allocate(1);
				_alloc.construct(_end, node());
				_end->_color = BLACK;
			}

			template <class InputIterator>
			tree(InputIterator first, InputIterator last, const value_compare& comp = value_compare(), const allocator_type& alloc = allocator_type()) : _root(0), _end(0), _size(0), _comp(comp), _alloc(alloc) {
				_end = _alloc.allocate(1);
				_alloc.construct(_end, node());
				_end->_color = BLACK;
				insert(first, last);
			}

			tree(const tree& ref) : _root(0), _end(0), _size(0), _comp(ref._comp), _alloc(ref._alloc) {
				_end = _alloc.allocate(1);
				_alloc.construct(_end, node());
				_end->_color = BLACK;
				insert(ref.begin(), ref.end());
			}

			virtual ~tree() {
				clear();
				_alloc.destroy(_end);
				_alloc.deallocate(_end, 1);
			}

			tree&	operator=(const tree& ref) {
				if (this != &ref) {
					clear();
					_comp = ref._comp;
					insert(ref.begin(), ref.end());
				}
				return (*this);
			}

			iterator	begin() {
				node_ptr tmp = _root;
				while (tmp->_left)
					tmp = tmp->_left;
				return (iterator(tmp, _end));
			}

			const_iterator	begin() const {
				node_ptr tmp = _root;
				while (tmp->_left)
					tmp = tmp->_left;
				return (const_iterator(tmp, _end));
			}

			iterator	end() {
				return (iterator(_end, _end));
			}

			const_iterator	end() const {
				return (const_iterator(_end, _end));
			}

			reverse_iterator	rbegin() {
				return (reverse_iterator(end()));
			}

			const_reverse_iterator	rbegin() const {
				return (const_reverse_iterator(end()));
			}

			reverse_iterator	rend() {
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rend() const {
				return (const_reverse_iterator(begin()));
			}

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
				std::swap(_root, ref._root);
				std::swap(_end, ref._end);
				std::swap(_size, ref._size);
				std::swap(_comp, ref._comp);
				std::swap(_alloc, ref._alloc);
			}

			std::pair<iterator, bool>	insert(const value_type& val) {
				node_ptr tmp = _root;
				node_ptr parent = 0;
				while (tmp) {
					parent = tmp;
					if (_comp(val, tmp->_value))
						tmp = tmp->_left;
					else if (_comp(tmp->_value, val))
						tmp = tmp->_right;
					else
						return (std::make_pair(iterator(tmp, _end), false));
				}
				tmp = _alloc.allocate(1);
				_alloc.construct(tmp, node(val));
				tmp->_parent = parent;
				if (!parent)
					_root = tmp;
				else if (_comp(val, parent->_value))
					parent->_left = tmp;
				else
					parent->_right = tmp;
				++_size;
				insert_fixup(tmp);
				return (std::make_pair(iterator(tmp, _end), true));
			}
	};
}

#endif