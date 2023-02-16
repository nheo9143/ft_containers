#ifndef NODE_HPP
# define NODE_HPP

# define RED		true
# define BLACK		false

namespace ft
{
	template <typename T>
	class node {
		public:

			T			_value;
			node*		_parent;
			node*		_left;
			node*		_right;
			bool		_color;

			node() : _value(), _parent(0), _left(0), _right(0), _color(RED) {}

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
}

#endif