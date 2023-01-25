#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iterator>

namespace ft
{

    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : input_iterator_tag {};
    struct bidirectional_iterator_tag : forward_iterator_tag {};
    struct random_access_iterator_tag : bidirectional_iterator_tag {};

    template<typename Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
    };

    template<typename T>
    struct iterator_traits<T*>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T                          value_type;
        typedef ptrdiff_t                  difference_type;
        typedef T*                         pointer;
        typedef T&                         reference;
    };

    template<typename T>
    struct iterator_traits<const T*>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T                          value_type;
        typedef ptrdiff_t                  difference_type;
        typedef const T*                   pointer;
        typedef const T&                   reference;
    };

    template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
            typename _Pointer = _Tp*, typename _Reference = _Tp&>
    struct iterator
    {
        typedef _Tp        value_type;
        typedef _Distance  difference_type;
        typedef _Pointer   pointer;
        typedef _Reference reference;
        typedef _Category  iterator_category;
    };

    template <typename Iterator>
    class random_access_iterator
    {
        public:
            typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type        value_type;
            typedef typename iterator_traits<Iterator>::difference_type   difference_type;
            typedef typename iterator_traits<Iterator>::pointer           pointer;
            typedef typename iterator_traits<Iterator>::reference         reference;

        private:
            iterator_type _current;

        public:
            random_access_iterator() : _current() {}
            template <typename Iter>
            random_access_iterator(const random_access_iterator<Iter>& other) : _current(other.base()) {}
            random_access_iterator(const random_access_iterator& other) : _current(other._current) {}
            random_access_iterator(const iterator_type& it) : _current(it) {}

            random_access_iterator& operator=(const random_access_iterator& other)
            {
                _current = other._current;
                return *this;
            }

            ~random_access_iterator() {}

            const iterator_type base() const { return _current; }

            reference operator*() const { return *_current; }

            pointer operator->() const { return _current; }

            random_access_iterator& operator++()
            {
                ++_current;
                return *this;
            }

            random_access_iterator operator++(int)
            {
                random_access_iterator tmp(*this);
                ++_current;
                return tmp;
            }

            random_access_iterator& operator--()
            {
                --_current;
                return *this;
            }

            random_access_iterator operator--(int)
            {
                random_access_iterator tmp(*this);
                --_current;
                return tmp;
            }

            random_access_iterator operator+(difference_type n) const
            {
                return random_access_iterator(_current + n);
            }

            random_access_iterator operator-(difference_type n) const
            {
                return random_access_iterator(_current - n);
            }

            random_access_iterator& operator+=(difference_type n)
            {
                _current += n;
                return *this;
            }

            random_access_iterator& operator-=(difference_type n)
            {
                _current -= n;
                return *this;
            }

            reference operator[](difference_type n) const
            {
                return _current[n];
            }
    };

    template <typename Iterator>
    bool operator==(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator==(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename Iterator>
    bool operator!=(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator!=(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename Iterator>
    bool operator<(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator<(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename Iterator>
    bool operator<=(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator<=(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename Iterator>
    bool operator>(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator>(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename Iterator>
    bool operator>=(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator>=(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename Iterator>
    random_access_iterator<Iterator> operator+(typename random_access_iterator<Iterator>::difference_type n,
                                            const random_access_iterator<Iterator>& it)
    {
        return random_access_iterator<Iterator>(it.base() + n);
    }

    template <typename Iterator1, typename Iterator2>
    typename random_access_iterator<Iterator1>::difference_type operator-(const random_access_iterator<Iterator1>& it1,
                                            const random_access_iterator<Iterator2>& it2)
    {
        return it1.base() - it2.base();
    }

    template <typename Iterator>
    typename random_access_iterator<Iterator>::difference_type operator-(const random_access_iterator<Iterator>& lhs,
                                                                        const random_access_iterator<Iterator>& rhs)
    {
        return lhs.base() - rhs.base();
    }

    template <typename Iterator>
    class reverse_iterator
    {
        public:
            typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type        value_type;
            typedef typename iterator_traits<Iterator>::difference_type   difference_type;
            typedef typename iterator_traits<Iterator>::pointer           pointer;
            typedef typename iterator_traits<Iterator>::reference         reference;

        private:
            iterator_type _current;

        public:
            reverse_iterator() : _current() {}
            template <typename Iter>
            reverse_iterator(const reverse_iterator<Iter>& other) : _current(other.base()) {}
            reverse_iterator(const reverse_iterator& other) : _current(other._current) {}
            reverse_iterator(const iterator_type& it) : _current(it) {}

            reverse_iterator& operator=(const reverse_iterator& other)
            {
                _current = other._current;
                return *this;
            }

            ~reverse_iterator() {}

            const iterator_type base() const { return _current; }

            reference operator*() const
            {
                iterator_type tmp = _current;
                return *--tmp;
            }

            pointer operator->() const
            {
                return &(operator*());
            }

            reverse_iterator& operator++()
            {
                --_current;
                return *this;
            }

            reverse_iterator operator++(int)
            {
                reverse_iterator tmp(*this);
                --_current;
                return tmp;
            }

            reverse_iterator& operator--()
            {
                ++_current;
                return *this;
            }

            reverse_iterator operator--(int)
            {
                reverse_iterator tmp(*this);
                ++_current;
                return tmp;
            }

            reverse_iterator operator+(difference_type n) const
            {
                return reverse_iterator(_current - n);
            }

            reverse_iterator operator-(difference_type n) const
            {
                return reverse_iterator(_current + n);
            }

            reverse_iterator& operator+=(difference_type n)
            {
                _current -= n;
                return *this;
            }

            reverse_iterator& operator-=(difference_type n)
            {
                _current += n;
                return *this;
            }

            reference operator[](difference_type n) const
            {
                return _current[-n - 1];
            }
    };

    template <typename Iterator>
    bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename Iterator>
    bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename Iterator>
    bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename Iterator>
    bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename Iterator>
    bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename Iterator>
    bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it)
    {
        return reverse_iterator<Iterator>(it.base() - n);
    }

    template <typename Iterator>
    typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return rhs.base() - lhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
    {
        return rhs.base() - lhs.base();
    }
}

#endif