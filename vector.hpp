#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "utils.hpp"

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T 		value_type;
			typedef Alloc	allocator_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type			size_type;

			typedef typename ft::random_access_iterator<pointer>		iterator;
			typedef typename ft::random_access_iterator<const_pointer>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
			pointer			_begin;
			pointer			_end;
			pointer			_end_cap;
			allocator_type	_a;

		public:
			/* constructer, destructor, operator= */
			explicit vector(const allocator_type& a = allocator_type()) : _begin(0), _end(0), _end_cap(0), _a(a) {};
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& a = allocator_type()) : _begin(0), _end(0), _end_cap(0), _a(a)
			{
				try {
					_begin = _a.allocate(n);
				} catch(...) {
					_begin = 0;
					return ;
				}
				_end = _begin;
				_end_cap = _begin + n;
				try {
					for (size_type i = 0; i < n; i++)
						_a.construct(_end++, val);
				} catch(...) {
					for (; _begin != _end; _end--)
						_a.destroy(_end);
					_a.deallocate(_begin, n);
				}
			};
			template <typename InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& a = allocator_type(), typename enable_if<!is_integral<InputIterator>::value, value_type>::type* = 0) : _a(a)
			{
				size_type n = difference(first, last);
				try {
					_begin = _a.allocate(n);
				} catch(...) {
					_begin = 0;
					return ;
				}
				_end = _begin;
				_end_cap = _begin + n;
				try {
					for (InputIterator it = first; it != last; it++)
						_a.construct(_end++, *it);
				} catch(...) {
					for (; _begin != _end; _end--)
						_a.destroy(_end);
					_a.deallocate(_begin, n);
				}
			};
			vector(const vector& x) : _a(x._a)
			{
				try {
					_begin = _a.allocate(x._end - x._begin);
				} catch(...) {
					_begin = 0;
					return ;
				}
				_end = _begin;
				_end_cap = _begin + (x._end - x._begin);
				try {
					for (const_iterator it = x.begin(); it != x.end(); it++)
						_a.construct(_end++, *it);					
				} catch(...) {
					for (; _begin != _end; _end--)
						_a.destroy(_end);
					_a.deallocate(_begin, x._end - x._begin);
				}
			};
			~vector()
			{
				if (_begin)
				{
					clear();
					_a.deallocate(_begin, _end_cap - _begin);
				}
			};
			vector& operator=(const vector& x)
			{
				if (this != &x)
				{
					clear();
					_a.deallocate(_begin, _end_cap - _begin);
					try {
						_begin = _a.allocate(x._end - x._begin);
					} catch(...) {
						_begin = 0;
						_end = 0;
						_end_cap = 0;
						return *this;
					}
					_end = _begin;
					_end_cap = _begin + (x._end - x._begin);
					try {
						for (const_iterator it = x.begin(); it != x.end(); it++)
							_a.construct(_end++, *it);
					} catch (...) {
						for (; _begin != _end; _end--)
							_a.destroy(_end);
						_a.deallocate(_begin, x._end - x._begin);
						_begin = 0;
						_end = 0;
						_end_cap = 0;
					}
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
			size_type size() const { return _end - _begin; };
			size_type max_size() const { return _a.max_size(); };
			size_type capacity() const { return _end_cap - _begin; };
			bool empty() const { return _begin == _end; };
			void resize(size_type n, value_type val = value_type()) {
				pointer tmp;
				if (n > size())
				{
					if (n > capacity())
					{
						try {
							tmp = _a.allocate(n);							
						} catch(...) {
							return ;
						}
						size_type i = 0;
						try {
							for (; i < size(); i++)
								_a.construct(tmp + i, _begin[i]);
							for (; i < n; i++)
								_a.construct(tmp + i, val);
						} catch (...) {
							for (; i; i--)
								_a.destroy(tmp + i);
							_a.deallocate(tmp, n);
							return ;
						}
						clear();
						_a.deallocate(_begin, _end_cap - _begin);
						_begin = tmp;
						_end = _begin + n;
						_end_cap = _begin + n;
					}
					else
					{
						try {
							for (size_type i = size(); i < n; i++)
								_a.construct(_end++, val);
						} catch(...) {
							for (; _begin != _end; _end--)
								_a.destroy(_end);
							_a.deallocate(_begin, _end_cap - _begin);
							throw ;
						}
					}
				}
				else
				{
					for (size_type i = size(); i > n; i--)
						_a.destroy(_end--);
				}
			};
			void reserve(size_type n) {
				if ( !n && _end_cap == _begin)
					n = 1;
				pointer tmp;
				if (n > capacity())
				{
					try {
						tmp = _a.allocate(n);
					} catch (...) {
						return ;
					}
					size_type origin_size = size();
					size_type i = 0;
					try {
						for (; i < origin_size; i++)
							_a.construct(tmp + i, _begin[i]);
					} catch (...) {
						for (; i; i--)
							_a.destroy(tmp + i);
						_a.deallocate(tmp, n);
						return ;
					}
					clear();
					_a.deallocate(_begin, _end_cap - _begin);
					_begin = tmp;
					_end = _begin + origin_size;
					_end_cap = _begin + n;
				}
			};

			/* element access */
			reference operator[](size_type n) { return _begin[n]; };
			const_reference operator[](size_type n) const { return _begin[n]; };
			reference at(size_type n)
			{
				if (n >= size())
					throw std::out_of_range("out of range");
				return _begin[n];
			};
			const_reference at(size_type n) const
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
			void assign(InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0) {
				size_type n = difference(first, last);
				pointer new_vec;
				try {
					new_vec = _a.allocate(n);
				} catch (...)
				{
					return ;
				}
				_a.deallocate(_begin, _end_cap - _begin);
				_begin = new_vec;
				_end = _begin + n;
				_end_cap = _begin + n;
				clear();
				InputIterator it = first;
				try {
					for (; it != last; it++)
						_a.construct(_end++, *it);
				} catch (...)
				{
					for (; it != first; it--)
						_a.destroy(_end--);
					return ;
				}
			};
			void assign(size_type n, const value_type& val) {
				pointer new_vec;
				try {
					new_vec = _a.allocate(n);
				} catch (...)
				{
					return ;
				}
				clear();
				size_type i = 0;
				try {
					for (; i < n; i++)
						_a.construct(new_vec + i, val);
				} catch (...)
				{
					for (; i; i--)
						_a.destroy(new_vec + i);
					_a.deallocate(new_vec, n);
					return ;
				}
				clear();
				_a.deallocate(_begin, _end_cap - _begin);
				_begin = new_vec;
				_end = _begin + n;
				_end_cap = _begin + n;
			};
			void push_back(const value_type& val) {
				try {
					if (_end_cap == _end)
						reserve(size() * 2);
				} catch(...) {
					return ;
				}
				try {
					_a.construct(_end++, val);
				} catch (...)
				{
					return ;
				}
			};
			void pop_back() {
				if (_end != _begin)
					_a.destroy(_end--);
			};
			iterator insert(iterator position, const value_type& val) {
				size_type to_pos = position - begin();
				size_type origin_size = size();
				size_type new_cap = capacity() == 0 ? 1 : (capacity() == origin_size ? origin_size * 2 : capacity());
				pointer tmp;
				try {
					tmp = _a.allocate(new_cap);
				} catch(...) {
					return position;
				}
				size_type i = 0;
				try {
					for (; i < to_pos; i++)
						_a.construct(tmp + i, _begin[i]);
					_a.construct(tmp + to_pos, val);
					for (; i < origin_size; i++)
						_a.construct(tmp + i + 1, _begin[i]);
				} catch(...) {
					for (; i; i--)
						_a.destroy(tmp + i);
					_a.deallocate(tmp, capacity());
					return position;
				}
				clear();
				_a.deallocate(_begin, _end_cap - _begin);
				_begin = tmp;
				_end = _begin + origin_size + 1;
				_end_cap = _begin + new_cap;
				return iterator(_begin + to_pos);
			};
			void insert(iterator position, size_type n, const value_type& val) {
				size_type to_pos = position - begin();
				size_type origin_size = size();
				size_type new_size = origin_size + n;
				size_type new_cap = capacity() > new_size ? capacity() : new_size;
				pointer tmp;
				try {
					tmp = _a.allocate(new_cap);
				} catch(...) {
					return ;
				}
				size_type i = 0;
				size_type j = 0;
				try {
					for (; i < to_pos; i++)
						_a.construct(tmp + i, _begin[i]);
					for (; j < n; j++)
						_a.construct(tmp + j + to_pos, val);
					for (; i < origin_size; i++)
						_a.construct(tmp + i + n, _begin[i]);
				} catch(...) {
					for (; i; i--)
						_a.destroy(tmp + i + j);
					for (; j; j--)
						_a.destroy(tmp + j);
					_a.deallocate(tmp, origin_size + n);
					return ;
				}				
				clear();
				_a.deallocate(_begin, _end_cap - _begin);
				_begin = tmp;
				_end = _begin + new_size;
				_end_cap = _begin + new_cap;
			};
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0) {
				size_type n = difference(first, last);
				size_type to_first = position - begin();
				size_type origin_size = size();
				size_type new_size = size() + n;
				size_type new_cap = capacity() > new_size ? capacity() : new_size;
				pointer tmp;
				try {
					tmp = _a.allocate(new_cap);
				} catch(...) {
					return ;
				}
				size_type i = 0;
				size_type j = 0;
				try {
					InputIterator it = first;
					for (; i < to_first; i++)
						_a.construct(tmp + i, _begin[i]);
					for (; j < n; j++)
						_a.construct(tmp + i + j, *(it++));
					for (; i < origin_size; i++)
						_a.construct(tmp + i + n, _begin[i]);
				} catch(...) {
					for (; i; i--)
						_a.destroy(tmp + i + j);
					for (; j; j--)
						_a.destroy(tmp + j);
					_a.deallocate(tmp, capacity());
					return ;
				}
				clear();
				_a.deallocate(_begin, _end_cap - _begin);
				_begin = tmp;
				_end = _begin + new_size;
				_end_cap = _begin + new_cap;
			};
			iterator erase(iterator position) {
				size_type to_pos = position - begin();
				size_type origin_size = size();
				size_type origin_cap = capacity();
				pointer tmp;
				try {
					tmp = _a.allocate(origin_cap);
				} catch(...) {
					return position;
				}
				size_type i = 0;
				try {
					for (; i < to_pos; i++)
						_a.construct(tmp + i, _begin[i]);
					for (; i + 1 < origin_size; i++)
						_a.construct(tmp + i, _begin[i + 1]);
				} catch(...) {
					for (; i; i--)
						_a.destroy(tmp + i - 1);
					_a.deallocate(tmp, origin_cap);
					return position;
				}
				clear();
				_a.deallocate(_begin, _end_cap - _begin);
				_begin = tmp;
				_end = _begin + origin_size - 1;
				_end_cap = _begin + origin_cap;
				return iterator(_begin + to_pos);
			};
			iterator erase(iterator first, iterator last) {
				size_type n = difference(first, last);
				size_type to_first = first - begin();
				size_type origin_size = size();
				size_type origin_cap = capacity();
				pointer tmp;
				try {
					tmp = _a.allocate(origin_cap);
				} catch(...) {
					return first;
				}
				size_type i = 0;
				size_type j = 0;
				try {
					for (; i < to_first; i++)
						_a.construct(tmp + i, _begin[i]);
					for (j = last - iterator(_begin); j < origin_size; j++)
						_a.construct(tmp + j - n, _begin[j]);
				} catch(...) {
					for (; j; j--)
						_a.destroy(tmp + j - n);
					for (; i; i--)
						_a.destroy(tmp + i);
					_a.deallocate(tmp, origin_cap);
					return first;
				}
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
				for (size_type i = 0; i < size(); i++)
					_a.destroy(_begin + i);
				_end = _begin;
			};

			/* allocator */
			allocator_type get_allocator() const { return _a; };
	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return rhs < lhs;
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs < rhs);
	}
}

#endif