#ifndef TREE_HPP
# define TREE_HPP

# include "utils.hpp"
# include "pair.hpp"
# include "tree_iterator.hpp"
# include "node.hpp"
# include <memory>

namespace ft
{
	template <typename T, typename Compare, typename Alloc = std::allocator<T> >
	class red_black_tree
	{
		private:
			typedef node<T>		t_node;
			typedef node<T>*	node_ptr;
			typedef typename Alloc::template rebind<t_node>::other	node_allocator;

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

			typedef ft::tree_iterator<value_type>				iterator;
			typedef ft::tree_const_iterator<value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
			node_ptr		_root;
			node_ptr		_end;
			size_type		_size;
			value_compare	_comp;
			node_allocator	_alloc;

		public:
			explicit red_black_tree(const value_compare& comp, const allocator_type& alloc = allocator_type()) : _root(0), _end(0), _size(0), _comp(comp), _alloc(alloc) {
				try {
					_end = _alloc.allocate(1);
				} catch(...) {
					return ;
				}
				try	{
					_alloc.construct(_end, t_node());
				} catch(...) {
					_alloc.deallocate(_end, 1);
					return ;
				}				
				_root = _end;
			}

			template <class InputIterator>
			red_black_tree(InputIterator first, InputIterator last, const value_compare& comp, const allocator_type& alloc = allocator_type()) : _root(0), _end(0), _size(0), _comp(comp), _alloc(alloc) {
				try {
					_end = _alloc.allocate(1);
				} catch(...) {
					return ;
				}
				try	{
					_alloc.construct(_end, t_node());
				} catch(...) {
					_alloc.deallocate(_end, 1);
					return ;
				}
				insert(first, last);
			}

			red_black_tree(const red_black_tree& ref) : _root(0), _end(0), _size(0), _comp(ref._comp), _alloc(ref._alloc) {
				try {
					_end = _alloc.allocate(1);
				} catch(...) {
					return ;
				}
				try	{
					_alloc.construct(_end, t_node());
				} catch(...) {
					_alloc.deallocate(_end, 1);
					return ;
				}
				_root = _end;
				insert(ref.begin(), ref.end());
			}

			virtual ~red_black_tree() {
				clear();
				_alloc.destroy(_end);
				_alloc.deallocate(_end, 1);
			}

			red_black_tree&	operator=(const red_black_tree& ref) {
				if (this != &ref) {
					clear();
					_comp = ref._comp;
					_alloc = ref._alloc;
					insert(ref.begin(), ref.end());
				}
				return (*this);
			}

			iterator	begin() {
				if (_root == _end)
					return (iterator(_end));
				node_ptr tmp = _root;
				while (tmp->_left)
					tmp = tmp->_left;
				return (iterator(tmp));
			}

			const_iterator	begin() const {
				node_ptr tmp = _root;
				while (tmp->_left)
					tmp = tmp->_left;
				return (const_iterator(tmp));
			}

			iterator	end() {
				return (iterator(_end));
			}

			const_iterator	end() const {
				return (const_iterator(_end));
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

			reference	operator[](const size_type& val) {
				iterator it = begin();
				for (size_type i = 0; i < val; i++)
					it++;
				return (*it);
			}
			const_reference	operator[](const size_type& val) const {
				const_iterator it = begin();
				for (size_type i = 0; i < val; i++)
					it++;
				return (*it);
			}

			void	swap(red_black_tree& ref) {
				ft::swap(_root, ref._root);
				ft::swap(_end, ref._end);
				ft::swap(_size, ref._size);
				ft::swap(_comp, ref._comp);
				ft::swap(_alloc, ref._alloc);
			}

			ft::pair<iterator, bool>	insert(const value_type& val) {
				node_ptr tmp = _root;
				node_ptr origin_root = _root;
				node_ptr parent = 0;
				if (find(val) != end())
					return (ft::make_pair(find(val), false));
				node_ptr new_node;
				try	{
					new_node = _alloc.allocate(1);
				}catch(...) {
					return (ft::make_pair(iterator(tmp), false));
				}
				try {
					_alloc.construct(new_node, t_node(val, parent));
				} catch(...) {
					_alloc.deallocate(new_node, 1);
					return (ft::make_pair(iterator(tmp), false));
				}
				while (tmp && tmp != _end) {
					parent = tmp;
					if (_comp(val, tmp->_value))
						tmp = tmp->_left;
					else
						tmp = tmp->_right;
				}
				if (!parent)
					_root = new_node;
				else if (_comp(val, parent->_value))
					parent->_left = new_node;
				else
					parent->_right = new_node;
				if (parent)
					new_node->_parent = parent;
				else
					new_node->_parent = _end;
				insert_fixup(new_node);
				++_size;
				if (!origin_root || origin_root != _root) {
					_root->_parent = _end;
					_end->_left = _root;
				}
				return (ft::make_pair(iterator(new_node), true));
			}

			iterator	insert(iterator position, const value_type& val) {
				(void)position;
				return (insert(val).first);
			}

			template <typename InputIterator>
			void	insert(InputIterator first, InputIterator last) {
				while (first != last) {
					insert(*first);
					++first;
				}
			}

			void	erase(const_iterator position) {
				node_ptr tmp = position.base();
				node_ptr to_delete = tmp;
				if (to_delete == _end)
					return ;
				if ((!to_delete->_left && !to_delete->_right && to_delete->_color == RED) || _size == 1) {
					if (to_delete->_parent->_left == to_delete)
						to_delete->_parent->_left = 0;
					else
						to_delete->_parent->_right = 0;
					_alloc.destroy(to_delete);
					_alloc.deallocate(to_delete, 1);
					_size--;
					if (to_delete == _root) {
						_root = _end;
					}
					return ;
				}
				node_ptr successor = 0;
				node_ptr origin_root = _root;
				if (tmp->_left && tmp->_right) {		// 삭제할 노드의 자식이 두개인경우
					if (tmp->_parent->_left == tmp) {	// 삭제할 노드가 부모의 왼쪽 노드인 경우
						successor = tmp->_left;
						while (successor->_right)
							successor = successor->_right;
					} else {							// 삭제할 노드가 부모의 오른쪽 노드인 경우
						successor = tmp->_right;
						while (successor->_left)
							successor = successor->_left;
					}
					if (successor->_parent != tmp && successor == successor->_parent->_left) {	//successor 아래에 있던 노드를 successor의 부모에 연결
						successor->_parent->_left = successor->_right;
						if (successor->_right)
							successor->_right->_parent = successor->_parent;
					} else if (successor->_parent != tmp) {
						successor->_parent->_right = successor->_left;
						if (successor->_left)
							successor->_left->_parent = successor->_parent;
					}
					successor->_parent = tmp->_parent;	// successor 찾은거를 삭제할 노드의 위치로 이동
					if (successor != tmp->_left) {
						successor->_left = tmp->_left;
						successor->_left->_parent = successor;
					}
					if (successor != tmp->_right) {
						successor->_right = tmp->_right;
						successor->_right->_parent = successor;
					}
					if (tmp->_parent->_left == tmp) {
						tmp->_parent->_left = successor;
					} else {
						tmp->_parent->_right = successor;
					}
				} else {									// 자식이 한 개인 경우, 바로 밑의 자식으로 대체해준다.
					if (tmp->_right) {
						tmp->_right->_parent = tmp->_parent;
						if (tmp == tmp->_parent->_left) {
							tmp->_parent->_left = tmp->_right;
						} else {
							tmp->_parent->_right = tmp->_right;
						}
						successor = tmp->_right;
					} else if (tmp->_left) {
						tmp->_left->_parent = tmp->_parent;
						if (tmp == tmp->_parent->_left) {
							tmp->_parent->_left = tmp->_left;
						} else {
							tmp->_parent->_right = tmp->_left;
						}
						successor = tmp->_left;
					} else {
						if (tmp == tmp->_parent->_left) {
							tmp->_parent->_left = 0;						
						} else
							tmp->_parent->_right = 0;
					}
				}
				if (successor && successor->_parent == _end) {
					_root = successor;
					successor->_color = BLACK;
				}
				if (!successor || successor->_color == BLACK)
					erase_fixup(tmp->_parent, successor);
				_alloc.destroy(to_delete);
				_alloc.deallocate(to_delete, 1);
				_size--;
				if (_root != origin_root) {
					_end->_left = _root;
					_root->_parent = _end;
				}
			}

			size_type	erase(const value_type& val) {
				iterator it = find(val);
				if (it == end())
					return (0);
				erase(it);
				return (1);
			}

			void	erase(const_iterator first, const_iterator last) {
				while (first != last) {
					const_iterator tmp = first;
					++first;
					erase(tmp);
				}
			}

			void clear() {
				erase(begin(), end());
			}

			iterator find(const value_type& val) {
				node_ptr tmp = _root;
				while (tmp && tmp != _end) {
					if (_comp(val, tmp->_value))
						tmp = tmp->_left;
					else if (_comp(tmp->_value, val))
						tmp = tmp->_right;
					else
						return (iterator(tmp));
				}
				return (end());
			}

			const_iterator find(const value_type& val) const {
				node_ptr tmp = _root;
				while (tmp && tmp != _end) {
					if (_comp(val, tmp->_value))
						tmp = tmp->_left;
					else if (_comp(tmp->_value, val))
						tmp = tmp->_right;
					else
						return (const_iterator(tmp));
				}
				return (end());
			}

			size_type count(const value_type& val) const {
				return (find(val) != end());
			}

		private:
			void insert_fixup(node_ptr node) {
				while (node->_parent != _end && node->_parent->_color == RED) {
					if (node->_parent == node->_parent->_parent->_left) {
						node_ptr uncle = node->_parent->_parent->_right;
						if (uncle && uncle->_color == RED) {
							node->_parent->_color = BLACK;
							uncle->_color = BLACK;
							node->_parent->_parent->_color = RED;
							node = node->_parent->_parent;
						} else {
							if (node == node->_parent->_right) {
								node = node->_parent;
								left_rotate(node);
							}
							node->_parent->_color = BLACK;
							node->_parent->_parent->_color = RED;
							right_rotate(node->_parent->_parent);
						}
					} else {
						node_ptr uncle = node->_parent->_parent->_left;
						if (uncle && uncle->_color == RED) {
							node->_parent->_color = BLACK;
							uncle->_color = BLACK;
							node->_parent->_parent->_color = RED;
							node = node->_parent->_parent;
						} else {
							if (node == node->_parent->_left) {
								node = node->_parent;
								right_rotate(node);
							}
							node->_parent->_color = BLACK;
							node->_parent->_parent->_color = RED;
							left_rotate(node->_parent->_parent);
						}
					}
				}
				_root->_color = BLACK;
			}

			void erase_fixup(node_ptr parent, node_ptr node) {
				while (node != _root && (!node || node->_color == BLACK)) {
					if (node == parent->_left) {
						node_ptr sibling = parent->_right;
						if (sibling && sibling->_color == RED) {
							sibling->_color = BLACK;
							parent->_color = RED;
							left_rotate(parent);
							sibling = parent->_right;
						}
						if (!sibling)
							break;
						if ((!sibling->_left || sibling->_left->_color == BLACK) &&
							(!sibling->_right || sibling->_right->_color == BLACK)) {
							sibling->_color = RED;
							node = parent;
							parent = node->_parent;
						} else {
							if ((!sibling->_right || sibling->_right->_color == BLACK)) {
								sibling->_left->_color = BLACK;
								sibling->_color = RED;
								right_rotate(sibling);
								sibling = parent->_right;
							}
							sibling->_color = parent->_color;
							parent->_color = BLACK;
							sibling->_right->_color = BLACK;
							left_rotate(parent);
							node = _root;
						}
					} else {
						node_ptr sibling = parent->_left;
						if (sibling && sibling->_color == RED) {
							sibling->_color = BLACK;
							parent->_color = RED;
							right_rotate(parent);
							sibling = parent->_left;
						}
						if (!sibling)
							break;
						if ((!sibling->_left || sibling->_left->_color == BLACK) &&
							(!sibling->_right || sibling->_right->_color == BLACK)) {
							sibling->_color = RED;
							node = parent;
							parent = node->_parent;
						} else {
							if ((!sibling->_left || sibling->_left->_color == BLACK)) {
								sibling->_right->_color = BLACK;
								sibling->_color = RED;
								left_rotate(sibling);
								sibling = parent->_left;
							}
							sibling->_color = parent->_color;
							parent->_color = BLACK;
							sibling->_left->_color = BLACK;
							right_rotate(parent);
							node = _root;
						}
					}
				}
				if (node)
					node->_color = BLACK;
			}

			// 오른쪽
			void left_rotate(node_ptr node) {
				node_ptr tmp = node->_right;
				node->_right = tmp->_left;
				if (tmp->_left)
					tmp->_left->_parent = node;
				tmp->_parent = node->_parent;
				if (node->_parent == _end)
					_root = tmp;
				else if (node == node->_parent->_left)
					node->_parent->_left = tmp;
				else
					node->_parent->_right = tmp;
				tmp->_left = node;
				node->_parent = tmp;
			}

			void right_rotate(node_ptr node) {
				node_ptr tmp = node->_left;
				node->_left = tmp->_right;
				if (tmp->_right)
					tmp->_right->_parent = node;
				tmp->_parent = node->_parent;
				if (node->_parent == _end)
					_root = tmp;
				else if (node == node->_parent->_right)
					node->_parent->_right = tmp;
				else
					node->_parent->_left = tmp;
				tmp->_right = node;
				node->_parent = tmp;
			}
		};
}

#endif