#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iterator>

namespace ft
{

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

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
        template <typename Iter>
        random_access_iterator() : _current() {}
        random_access_iterator(const random_access_iterator<Iter>& other) : _current(other.base()) {}
        iterator(random_access_iterator it) : _current(it) {}
        iterator(const random_access_iterator& other) : _current(other._it) {}

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
            iterator tmp(*this);
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

template <typename Iterator>
bool operator!=(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
{
    return lhs.base() != rhs.base();
}

template <typename Iterator>
bool operator<(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
{
    return lhs.base() < rhs.base();
}

template <typename Iterator>
bool operator<=(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
{
    return lhs.base() <= rhs.base();
}

template <typename Iterator>
bool operator>(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
{
    return lhs.base() > rhs.base();
}

template <typename Iterator>
bool operator>=(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
{
    return lhs.base() >= rhs.base();
}

#endif