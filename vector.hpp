#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <vector>
#include <memory>
#include "iterator.hpp"
#include <type_traits>

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef typename allocator_type::difference_type difference_type;

			typedef typename ft::random_access_iterator<pointer> iterator;
			typedef typename ft::random_access_iterator<const_pointer> const_iterator;
			typedef typename ft::reverse_iterator<iterator> reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		protected:
			pointer _begin;
			pointer _end;
			pointer _end_cap;
			allocator_type _a;

		public:
			/* constructer */
			explicit vector(const allocator_type& a = allocator_type()) : _begin(NULL), _end(NULL), _end_cap(NULL), _a(a) {};
			explicit vector(difference_type n, const allocator_type& a = allocator_type()) : _a(a)
			{
				_begin = _a.allocate(n);
				_end = _begin;
				_end_cap = _begin + n;
				for (difference_type i = 0; i < n; i++)
					_a.construct(_end++);
			};
			explicit vector(difference_type n, const value_type& val = value_type(), const allocator_type& a = allocator_type()) : _a(a)
			{
				_begin = _a.allocate(n);
				_end = _begin;
				_end_cap = _begin + n;
				for (difference_type i = 0; i < n; i++)
					_a.construct(_end++, val);
			};
			template <typename InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& a = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, T >::type* = 0) : _a(a)
			{
				_begin = _a.allocate(last - first);
				_end = _begin;
				_end_cap = _begin + (last - first);
				for (InputIterator it = first; it != last; it++)
					_a.construct(_end++, *it);
			};
			vector(const vector& x) : _a(x._a)
			{
				_begin = _a.allocate(x._end - x._begin);
				_end = _begin;
				_end_cap = _begin + (x._end - x._begin);
				for (const_iterator it = x.begin(); it != x.end(); it++)
					_a.construct(_end++, *it);
			};
			~vector()
			{
				clear();
				_a.deallocate(_begin, _end_cap - _begin);
			};
			vector& operator=(const vector& x)
			{
				if (this != &x)
				{
					clear();
					_a.deallocate(_begin, _end_cap - _begin);
					_begin = _a.allocate(x._end - x._begin);
					_end = _begin;
					_end_cap = _begin + (x._end - x._begin);
					for (const_iterator it = x.begin(); it != x.end(); it++)
						_a.construct(_end++, *it);
				}
				return *this;
			};

			/* iterator */
			iterator begin() { return iterator(_begin); };
			const_iterator begin() const { return const_iterator(_begin); };
			iterator end() { return iterator(_end); };
			const_iterator end() const { return const_iterator(_end); };
			reverse_iterator rbegin() { return reverse_iterator(end()); };
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };
			reverse_iterator rend() { return reverse_iterator(begin()); };
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };

			/* capacity */
			difference_type size() const { return _end - _begin; };
			difference_type max_size() const { return _a.max_size(); };
			difference_type capacity() const { return _end_cap - _begin; };
			bool empty() const { return _begin == _end; };
			void resize(difference_type n, value_type val = value_type()) {
				if (n > size())
				{
					if (n > capacity())
					{
						pointer tmp = _a.allocate(n);
						for (difference_type i = 0; i < size(); i++)
							_a.construct(tmp + i, _begin[i]);
						for (difference_type i = size(); i < n; i++)
							_a.construct(tmp + i, val);
						clear();
						_a.deallocate(_begin, _end_cap - _begin);
						_begin = tmp;
						_end = _begin + n;
						_end_cap = _begin + n;
					}
					else
					{
						for (difference_type i = size(); i < n; i++)
							_a.construct(_end++, val);
					}
				}
				else
				{
					for (difference_type i = size(); i > n; i--)
						_a.destroy(_end--);
				}
			};
			void reserve(difference_type n) {
				if (_end_cap - _begin == 0)
					n = 1;
				if (n > capacity())
				{
					pointer tmp = _a.allocate(n);
					difference_type origin_size = size();
					for (difference_type i = 0; i < origin_size; i++)
						_a.construct(tmp + i, _begin[i]);
					clear();
					_a.deallocate(_begin, _end_cap - _begin);
					_begin = tmp;
					_end = _begin + origin_size;
					_end_cap = _begin + n;
				}
			};

			/* element access */
			reference operator[](difference_type n) { return _begin[n]; };
			const_reference operator[](difference_type n) const { return _begin[n]; };
			reference at(difference_type n)
			{
				if (n >= size())
					throw std::out_of_range("out of range");
				return _begin[n];
			};
			const_reference at(difference_type n) const
			{
				if (n >= size())
					throw std::out_of_range("out of range");
				return _begin[n];
			};
			reference front() { return *_begin; };
			const_reference front() const { return *_begin; };
			reference back() { return *(_end - 1); };
			const_reference back() const { return *(_end - 1); };

			/* modifier */
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
				clear();
				if (last - first > capacity())
					reserve(last - first);
				for (InputIterator it = first; it != last; it++)
					_a.construct(_end++, *it);
			};
			void assign(difference_type n, const value_type& val) {
				clear();
				if (n > capacity())
					reserve(n);
				for (difference_type i = 0; i < n; i++)
					_a.construct(_end++, val);
			};
			void push_back(const value_type& val) {
				if (_end_cap == _end)
					reserve(size() * 2);
				_a.construct(_end++, val);
			};
			void pop_back() {
				_a.destroy(_end--);
			};
			iterator insert(iterator position, const value_type& val) {
				difference_type to_pos = position - begin();
				difference_type origin_size = size();
				if (size() == capacity())
					reserve(size() * 2);
				pointer tmp = _a.allocate(capacity());
				for (difference_type i = 0; i < to_pos; i++)
					_a.construct(tmp + i, _begin[i]);
				_a.construct(tmp + to_pos, val);
				clear();
				_a.deallocate(_begin, _end_cap - _begin);
				_begin = tmp;
				_end = _begin + origin_size + 1;
				_end_cap = _begin + capacity();
				return iterator(_begin + to_pos);
			};
			void insert(iterator position, difference_type n, const value_type& val) {
				difference_type to_pos = position - begin();
				difference_type origin_size = size();
				difference_type new_size = size() + n;
				difference_type origin_cap = capacity();
				if (size() + n > capacity())
					reserve(size() + n);
				pointer tmp = _a.allocate(capacity());
				for (difference_type i = 0; i < to_pos; i++)
					_a.construct(tmp + i, _begin[i]);
				for (difference_type i = to_pos; i < n; i++)
					_a.construct(tmp + i, val);
				for (difference_type i = to_pos + n; i < new_size; i++)
					_a.construct(tmp + i, _begin[i]);
				clear();
				_a.deallocate(_begin, _end_cap - _begin);
				_begin = tmp;
				_end = _begin + new_size;
				_end_cap = _begin + origin_cap;
			};
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
				difference_type n = last - first;
				if (size() + n > capacity())
					reserve(size() + n);
				difference_type origin_size = size();
				difference_type new_size = size() + n;
				difference_type origin_cap = capacity();
				difference_type to_first = position - begin();
				pointer tmp = _a.allocate(capacity());
				for (difference_type i = 0; i < to_first; i++)
					_a.construct(tmp + i, _begin[i]);
				for (difference_type i = 0; i < n; i++)
					_a.construct(tmp + to_first + i, *(first + i));
				for (difference_type i = to_first; i < origin_size; i++)
					_a.construct(tmp + i + n, _begin[i]);
				clear();
				_a.deallocate(_begin, _end_cap - _begin);
				_begin = tmp;
				_end = _begin + origin_size + n;
				_end_cap = _begin + origin_cap;
			};
			iterator erase(iterator position) {
				difference_type to_pos = position - begin();
				difference_type origin_size = size();
				difference_type origin_cap = capacity();
				pointer tmp = _a.allocate(origin_cap);
				for (difference_type i = 0; i < to_pos; i++)
					_a.construct(tmp + i, _begin[i]);
				for (difference_type i = to_pos + 1; i < origin_size; i++)
					_a.construct(tmp + i - 1, _begin[i]);
				clear();
				_a.deallocate(_begin, _end_cap - _begin);
				_begin = tmp;
				_end = _begin + origin_size - 1;
				_end_cap = _begin + origin_cap;
				return iterator(_begin + to_pos);
			};
			iterator erase(iterator first, iterator last) {
				difference_type n = last - first;
				difference_type to_first = first - begin();
				difference_type origin_size = size();
				difference_type origin_cap = capacity();
				pointer tmp = _a.allocate(origin_cap);
				for (difference_type i = 0; i < to_first; i++)
					_a.construct(tmp + i, _begin[i]);
				for (difference_type i = last - iterator(_begin); i < origin_size; i++)
					_a.construct(tmp + i - n, _begin[i]);
				clear();
				_a.deallocate(_begin, _end_cap - _begin);
				_begin = tmp;
				_end = _begin + origin_size - n;
				_end_cap = _begin + origin_cap;
				return iterator(_begin + to_first);
			};
			void swap(vector& x) {
				pointer tmp = _begin;
				_begin = x._begin;
				x._begin = tmp;
				tmp = _end;
				_end = x._end;
				x._end = tmp;
				tmp = _end_cap;
				_end_cap = x._end_cap;
				x._end_cap = tmp;
			};
			void clear() {
				for (difference_type i = 0; i < size(); i++)
					_a.destroy(_begin + i);
				_end = _begin;
			};

			/* allocator */
			allocator_type get_allocator() const { return _a; };
	};
}

#endif