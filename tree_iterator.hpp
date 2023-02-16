#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "utils.hpp"
# include "pair.hpp"
# include "iterator.hpp"
# include "tree.hpp"
# include "node.hpp"

namespace ft
{
	template <typename T>
	class tree_const_iterator;

	template <typename T>
	class tree_iterator : public iterator<ft::bidirectional_iterator_tag, T>
	{
		private:
			typedef node<T>	t_node;
			typedef node<T>	*node_ptr;

		public:
			typedef bidirectional_iterator_tag	iterator_category;
			typedef T							value_type;
			typedef ptrdiff_t					difference_type;
			typedef T*							pointer;
			typedef T&							reference;

		private:
			node_ptr _node;
		
		public:
			tree_iterator() : _node() {}
			tree_iterator(node_ptr node) : _node(node) {}
			tree_iterator(const tree_iterator &other) : _node(other._node) {}
			virtual ~tree_iterator() {}
			tree_iterator &operator=(const tree_iterator &other)
			{
				_node = other._node;
				return (*this);
			}
			node_ptr base() const { return (_node); }
			reference operator*() const { return (_node->_value); }
			pointer operator->() const { return (&_node->_value); }
			tree_iterator &operator++()
			{
				if (_node->_right)
				{
					_node = _node->_right;
					while (_node->_left)
						_node = _node->_left;
				}
				else
				{
					node_ptr tmp = _node->_parent;
					while (tmp && _node == tmp->_right)
					{
						_node = tmp;
						tmp = tmp->_parent;
					}
					_node = tmp;
				}
				return (*this);
			}
			tree_iterator operator++(int)
			{
				tree_iterator tmp(*this);
				++(*this);
				return (tmp);
			}
			tree_iterator &operator--()
			{
				if (_node->_left)
				{
					_node = _node->_left;
					while (_node->_right)
						_node = _node->_right;
				}
				else
				{
					node_ptr tmp = _node->_parent;
					while (tmp && _node == tmp->_left)
					{
						_node = tmp;
						tmp = tmp->_parent;
					}
					_node = tmp;
				}
				return (*this);
			}
			tree_iterator operator--(int)
			{
				tree_iterator tmp(*this);
				--(*this);
				return (tmp);
			}
			bool operator==(const tree_iterator &other) const { return (_node == other._node); }
			bool operator!=(const tree_iterator &other) const { return (_node != other._node); }
			bool operator==(const tree_const_iterator<T> &other) const { return (_node == other.base()); }
			bool operator!=(const tree_const_iterator<T> &other) const { return (_node != other.base()); }
	};

	template <typename T>
	class tree_const_iterator : public iterator<ft::bidirectional_iterator_tag, T>
	{
		private:
			typedef node<T>	t_node;
			typedef node<T>	*node_ptr;

		public:
			typedef bidirectional_iterator_tag	iterator_category;
			typedef T							value_type;
			typedef ptrdiff_t					difference_type;
			typedef const T*					pointer;
			typedef const T&					reference;

		private:
			node_ptr _node;
		
		public:
			tree_const_iterator() : _node(NULL) {}
			tree_const_iterator(node_ptr node) : _node(node) {}
			tree_const_iterator(const tree_const_iterator &other) : _node(other._node) {}
			tree_const_iterator(const tree_iterator<T> &other) : _node(other.base()) {}
			virtual ~tree_const_iterator() {}
			tree_const_iterator &operator=(const tree_const_iterator &other)
			{
				_node = other._node;
				return (*this);
			}
			tree_const_iterator &operator=(const tree_iterator<T> &other)
			{
				_node = other.base();
				return (*this);
			}
			node_ptr base() const { return (_node); }
			reference operator*() const { return (_node->_value); }
			pointer operator->() const { return (&_node->_value); }
			tree_const_iterator &operator++()
			{
				if (_node->_right)
				{
					_node = _node->_right;
					while (_node->_left)
						_node = _node->_left;
				}
				else
				{
					node_ptr tmp = _node->_parent;
					while (tmp && _node == tmp->_right)
					{
						_node = tmp;
						tmp = tmp->_parent;
					}
					_node = tmp;
				}
				return (*this);
			}
			tree_const_iterator operator++(int)
			{
				tree_const_iterator tmp(*this);
				++(*this);
				return (tmp);
			}
			tree_const_iterator &operator--()
			{
				if (_node->_left)
				{
					_node = _node->_left;
					while (_node->_right)
						_node = _node->_right;
				}
				else
				{
					node_ptr tmp = _node->_parent;
					while (tmp && _node == tmp->_left)
					{
						_node = tmp;
						tmp = tmp->_parent;
					}
					_node = tmp;
				}
				return (*this);
			}
			tree_const_iterator operator--(int)
			{
				tree_const_iterator tmp(*this);
				--(*this);
				return (tmp);
			}
			bool operator==(const tree_const_iterator &other) const { return (_node == other._node); }
			bool operator!=(const tree_const_iterator &other) const { return (_node != other._node); }
			bool operator==(const tree_iterator<T> &other) const { return (_node == other.base()); }
			bool operator!=(const tree_iterator<T> &other) const { return (_node != other.base()); }
	};
}

#endif