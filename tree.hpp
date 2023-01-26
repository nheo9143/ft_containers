#ifndef TREE_HPP
# define TREE_HPP

# include "utils.hpp"
# include "pair.hpp"
# include "bidirectional_iterator.hpp"

# define RED		true
# define BLACK		false

template <typename T, typename Alloc>
class tree
{
	public:
		typedef T															value_type;
		typedef Alloc														allocator_type;
		typedef typename T::first_type										key_type;
		typedef typename T::second_type										mapped_type;
		typedef typename allocator_type::size_type							size_type;
		typedef typename Alloc::difference_type								difference_type;
		typedef typename Alloc::reference									reference;
		typedef typename Alloc::const_reference								const_reference;
		typedef typename Alloc::pointer										pointer;
		typedef typename Alloc::const_pointer								const_pointer;

		typedef typename ft::bidirectional_iterator<pointer>				iterator;
		typedef typename ft::bidirectional_iterator<const_pointer>			const_iterator;
		typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;

		class node
		{
			public:
				node*		parent;
				node*		left;
				node*		right;
				value_type	value;
				bool		color;

				node() : parent(NULL), left(NULL), right(NULL), value(), color(BLACK) {};
				node(const value_type& val) : parent(NULL), left(NULL), right(NULL), value(val), color(BLACK) {};
				node(const node& x) : parent(x.parent), left(x.left), right(x.right), value(x.value), color(x.color) {};
				~node() {};
				node& operator=(const node& x)
				{
					if (this != &x)
					{
						parent = x.parent;
						left = x.left;
						right = x.right;
						value = x.value;
						color = x.color;
					}
					return *this;
				};
		};

	private:
		allocator_type	_a;
		node*			_root;
		node*			_nil;
		size_type		_size;

	public:
		tree() : _a(), _root(NULL), _nil(NULL), _size(0) {};
		tree(const tree& x) : _a(x.alloc), _root(x._root), _nil(x._nil), _size(x._size) {};
		~tree() {};
		tree& operator=(const tree& x)
		{
			if (this != &x)
			{
				_a = x._a;
				_root = x._root;
				_nil = x._nil;
				_size = x._size;
			}
			return *this;
		};

		iterator begin() { return iterator(_root); };
		iterator end() { return iterator(_nil); };
		reverse_iterator rbegin() { return reverse_iterator(end()); };
		reverse_iterator rend() { return reverse_iterator(begin()); };

		bool empty() const { return (_size == 0); };
		size_type size() const { return _size; };
		size_type max_size() const { return _a.max_size(); };

		void insert(const value_type& val)
		{
			node * new_node;
			try {
				new_node = _a.allocate(1);
			} catch(...) {
				return ;
			}
			try {
				_a.construct(new_node, val);
			} catch(...) {
				_a.deallocate(new_node, 1);
				return ;
			}
			node*	y = _nil;
			node*	x = _root;

			while (x != _nil)
			{
				y = x;
				if (new_node->value < x->value)
					x = x->left;
				else
					x = x->right;
			}
			new_node->parent = y;
			if (y == _nil)
				_root = new_node;
			else if (new_node->value < y->value)
				y->left = new_node;
			else
				y->right = new_node;
			new_node->left = _nil;
			new_node->right = _nil;
			new_node->color = RED;
			insert_fixup(new_node);
			_size++;
		};

		void insert(iterator position, const value_type& val)
		{
			if (position < begin() || position > end())
				return ;
			node* new_node;
			try {
				new_node = _a.allocate(1);
			} catch(...) {
				return ;
			}
			try {
				_a.construct(new_node, val);
			} catch(...) {
				_a.deallocate(new_node, 1);
				return ;
			}
			node*	y = _nil;
			node*	x = _root;
			if (*position <= val)
			{
				while (x != _nil)
				{
					y = x;
					if (new_node->value < x->value)
						x = x->left;
					else
						x = x->right;
				}
				new_node->parent = y;
				if (y == _nil)
					_root = new_node;
				else if (new_node->value < y->value)
					y->left = new_node;
				else
					y->right = new_node;
				new_node->left = _nil;
				new_node->right = _nil;
				new_node->color = RED;
				insert_fixup(new_node);
				_size++;
				return ;
			}
			if (*position > val)
			{
				while (x != _nil)
				{
					y = x;
					if (new_node->value < x->value)
						x = x->left;
					else
						x = x->right;
				}
				new_node->parent = y;
				if (y == _nil)
					_root = new_node;
				else if (new_node->value < y->value)
					y->left = new_node;
				else
					y->right = new_node;
				new_node->left = _nil;
				new_node->right = _nil;
				new_node->color = RED;
				insert_fixup(new_node);
				_size++;
				return ;
			}
			_a.destroy(new_node);
			_a.deallocate(new_node, 1);
			return ;
		};

		void erase(iterator position)
		{
			node* z = *position;
			node* y = z;
			node* x;
			bool y_original_color = y->color;

			if (z->left == _nil)
			{
				x = z->right;
				transplant(z, z->right);
			}
			else if (z->right == _nil)
			{
				x = z->left;
				transplant(z, z->left);
			}
			else
			{
				y = tree_minimum(z->right);
				y_original_color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			if (y_original_color == BLACK)
				erase_fixup(x);
			delete z;
			_size--;
		};

		void erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		};

		size_type erase(const key_type& k)
		{
			size_type i = 0;
			for (iterator it = begin(); it != end(); it++)
				if (*it == k)
				{
					erase(it);
					++i;
				}
			return i;
		};

		void swap(tree& x)
		{
			tree tmp = x;
			x = *this;
			*this = tmp;
		};

		void clear()
		{
			erase(begin(), end());
		};

		iterator find(const key_type& k)
		{
			node* x = _root;
			while (x != _nil && x->value != k)
			{
				if (k < x->value)
					x = x->left;
				else
					x = x->right;
			}
			return iterator(x);
		};

		const_iterator find(const key_type& k) const
		{
			node* x = _root;
			while (x != _nil && x->value != k)
			{
				if (k < x->value)
					x = x->left;
				else
					x = x->right;
			}
			return const_iterator(x);
		};

		size_type count(const key_type& k) const
		{
			size_type i = 0;
			for (const_iterator it = begin(); it != end(); it++)
				if (*it == k)
					++i;
			return i;
		};

		iterator lower_bound(const key_type& k)
		{
			node* x = _root;
			node* y = _nil;
			while (x != _nil)
			{
				if (x->value < k)
					x = x->right;
				else
				{
					y = x;
					x = x->left;
				}
			}
			return iterator(y);
		};

		const_iterator lower_bound(const key_type& k) const
		{
			node* x = _root;
			node* y = _nil;
			while (x != _nil)
			{
				if (x->value < k)
					x = x->right;
				else
				{
					y = x;
					x = x->left;
				}
			}
			return const_iterator(y);
		};

		iterator upper_bound(const key_type& k)
		{
			node* x = _root;
			node* y = _nil;
			while (x != _nil)
			{
				if (k < x->value)
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return iterator(y);
		};

		const_iterator upper_bound(const key_type& k) const
		{
			node* x = _root;
			node* y = _nil;
			while (x != _nil)
			{
				if (k < x->value)
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			return const_iterator(y);
		};

		pair<iterator, iterator> equal_range(const key_type& k)
		{
			return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
		};

		pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{
			return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
		};

	private:
		void erase_fixup(node* x)
		{
			while (x != _root && x->color == BLACK)
			{
				if (x == x->parent->left)
				{
					node* w = x->parent->right;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->parent->color = RED;
						left_rotate(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == BLACK && w->right->color == BLACK)
					{
						w->color = RED;
						x = x->parent;
					}
					else
					{
						if (w->right->color == BLACK)
						{
							w->left->color = BLACK;
							w->color = RED;
							right_rotate(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->right->color = BLACK;
						left_rotate(x->parent);
						x = _root;
					}
				}
				else
				{
					node* w = x->parent->left;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->parent->color = RED;
						right_rotate(x->parent);
						w = x->parent->left;
					}
					if (w->right->color == BLACK && w->left->color == BLACK)
					{
						w->color = RED;
						x = x->parent;
					}
					else
					{
						if (w->left->color == BLACK)
						{
							w->right->color = BLACK;
							w->color = RED;
							left_rotate(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->left->color = BLACK;
						right_rotate(x->parent);
						x = _root;
					}
				}
			}
			x->color = BLACK;
		};

		void transplant(node* u, node* v)
		{
			if (u->parent == _nil)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		};

		node* tree_minimum(node* x)
		{
			while (x->left != _nil)
				x = x->left;
			return x;
		};

		node* tree_maximum(node* x)
		{
			while (x->right != _nil)
				x = x->right;
			return x;
		};

		node* tree_successor(node* x)
		{
			if (x->right != _nil)
				return tree_minimum(x->right);
			node* y = x->parent;
			while (y != _nil && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		};

		node* tree_predecessor(node* x)
		{
			if (x->left != _nil)
				return tree_maximum(x->left);
			node* y = x->parent;
			while (y != _nil && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return y;
		};

		void insert_fixup(node* z)
		{
			while (z->parent->color == RED)
			{
				if (z->parent == z->parent->parent->left)
				{
					node* y = z->parent->parent->right;
					if (y->color == RED)
					{
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->right)
						{
							z = z->parent;
							left_rotate(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						right_rotate(z->parent->parent);
					}
				}
				else
				{
					node* y = z->parent->parent->left;
					if (y->color == RED)
					{
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->left)
						{
							z = z->parent;
							right_rotate(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						left_rotate(z->parent->parent);
					}
				}
			}
			_root->color = BLACK;
		};

		void left_rotate(node* x)
		{
			node* y = x->right;
			x->right = y->left;
			if (y->left != _nil)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == _nil)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		};

		void right_rotate(node* x)
		{
			node* y = x->left;
			x->left = y->right;
			if (y->right != _nil)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == _nil)
				_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		};
};

#endif