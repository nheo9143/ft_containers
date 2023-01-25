#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <typename T, typename Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;
		
		private:
			container_type	_c;

		public:
			/* constructer */
			explicit stack(const container_type& ctnr = container_type()) : _c(ctnr) {}

			/* member functions */
			bool empty() const { return _c.empty(); }
			size_type size() const { return _c.size(); }
			value_type& top() { return _c.back(); }
			const value_type& top() const { return _c.back(); }
			void push(const value_type& val) { _c.push_back(val); }
			void pop() { _c.pop_back(); }

			template <typename T2, typename Container2>
			friend bool operator==(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs) {
				return lhs._c == rhs._c;
			};
			template <typename T2, typename Container2>
			friend bool operator!=(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs) {
				return lhs._c != rhs._c;
			};
			template <typename T2, typename Container2>
			friend bool operator<(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs) {
				return lhs._c < rhs._c;
			};
			template <typename T2, typename Container2>
			friend bool operator<=(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs) {
				return lhs._c <= rhs._c;
			}
			template <typename T2, typename Container2>
			friend bool operator>(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs) {
				return lhs._c > rhs._c;
			}
			template <typename T2, typename Container2>
			friend bool operator>=(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs) {
				return lhs._c >= rhs._c;
			}
	};
}

#endif