/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:01:56 by zhliew            #+#    #+#             */
/*   Updated: 2022/11/04 15:13:47 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
# define ITERATORS_HPP

#include <memory>

namespace ft
{
	struct random_access_iterator_tag {};

	struct bidirectional_iterator_tag {};
	
	struct forward_iterator_tag {};

	struct input_iterator_tag {};

	struct output_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&> 
	struct iterator
	{
		typedef T         value_type;
    	typedef Distance  difference_type;
    	typedef Pointer   pointer;
    	typedef Reference reference;
    	typedef Category  iterator_category;
	};

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};
	
	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};
	
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category		iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference				reference;

			random_access_iterator()
				: _ptr(nullptr) {}
			
			random_access_iterator(pointer ptr)
				: _ptr(ptr) {}

			random_access_iterator(const random_access_iterator &ref)
				: _ptr(ref._ptr) {}

			~random_access_iterator()
				{}
			
			pointer base() const
			{
				return (_ptr);
			}

			random_access_iterator &operator=(const random_access_iterator &ref)
			{
				_ptr = ref.base();
				return (*this);
			}

			reference operator*()
			{
				return (*_ptr);
			}
			
			pointer operator->() const
			{
				return (_ptr);
			}

			random_access_iterator operator+(difference_type n) const
			{
				return (_ptr + n);
			}

			random_access_iterator operator-(difference_type n) const
			{
				return (_ptr - n);
			}

			random_access_iterator &operator++()
			{
				_ptr++;
				return (*this);
			}

			random_access_iterator operator++(int)
			{
				random_access_iterator tmp = *this;
				_ptr++;
				return (tmp);
			}

			random_access_iterator &operator--()
			{
				_ptr--;
				return (*this);
			}

			random_access_iterator operator--(int)
			{
				random_access_iterator tmp = *this;
				_ptr--;
				return (tmp);
			}

			random_access_iterator &operator+=(difference_type n)
			{
				_ptr += n;
				return (*this);
			}

			random_access_iterator &operator-=(difference_type n)
			{
				_ptr -= n;
				return (*this);
			}

			reference operator[](difference_type n) const
			{
				return *(_ptr + n);
			}

			operator random_access_iterator<T>() const
			{
            	return (random_access_iterator<T>(_ptr));
        	}

		private:
			pointer _ptr;
	};

	template <class T>
	bool operator==(const random_access_iterator<T> &l, const random_access_iterator<T> &r)
	{
		return (l.base() == r.base());
	}

	template <class T>
	bool operator!=(const random_access_iterator<T> &l, const random_access_iterator<T> &r)
	{
		return (l.base() != r.base());
	}

	template <class T>
	bool operator>=(const random_access_iterator<T> &l, const random_access_iterator<T> &r)
	{
		return (l.base() >= r.base());
	}

	template <class T>
	bool operator<=(const random_access_iterator<T> &l, const random_access_iterator<T> &r)
	{
		return (l.base() <= r.base());
	}

	template <class T>
	bool operator>(const random_access_iterator<T> &l, const random_access_iterator<T> &r)
	{
		return (l.base() > r.base());
	}

	template <class T>
	bool operator<(const random_access_iterator<T> &l, const random_access_iterator<T> &r)
	{
		return (l.base() < r.base());
	}

	template <class T>
	random_access_iterator<T> operator+
			(typename random_access_iterator<T>::difference_type n,
			const random_access_iterator<T> &it)
	{
		return (it + n);
	}

	template <class T>
	typename random_access_iterator<T>::difference_type operator-
			(const random_access_iterator<T> &l,
			const random_access_iterator<T> &r)
	{
		return (l.base() - r.base());
	}

	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator													iterator_type;
       		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
        	typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
        	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
        	typedef typename ft::iterator_traits<Iterator>::reference			reference;

			reverse_iterator()
				: _ptr(nullptr) {}

			reverse_iterator(iterator_type ptr)
				: _ptr(ptr) {}

			reverse_iterator(const reverse_iterator &ref)
				: _ptr(ref._ptr) {}

			~reverse_iterator()
				{}

			iterator_type base()
			{
				return (_ptr);
			}

			reference operator*()
			{
				iterator_type tmp = _ptr;
				return *(--tmp);
			}
			
			pointer operator->() const
			{
				return &(operator*());
			}

			reverse_iterator operator+(difference_type n) const
			{
				return reverse_iterator(_ptr - n);
			}

			reverse_iterator operator-(difference_type n) const
			{
				return reverse_iterator(_ptr + n);
			}

			reverse_iterator &operator++()
			{
				_ptr--;
				return (*this);
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				_ptr--;
				return (tmp);
			}

			reverse_iterator &operator--()
			{
				_ptr++;
				return (*this);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				_ptr++;
				return (tmp);
			}

			reverse_iterator &operator+=(difference_type n)
			{
				_ptr -= n;
				return (*this);
			}

			reverse_iterator &operator-=(difference_type n)
			{
				_ptr += n;
				return (*this);
			}

			reference operator[](difference_type n) const
			{
				return *(_ptr - n);
			}
		
		private:
			Iterator _ptr;
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> &l, const reverse_iterator<Iterator> &r)
	{
		return (l.base() == r.base());
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &l, const reverse_iterator<Iterator> &r)
	{
		return (l.base() != r.base());
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &l, const reverse_iterator<Iterator> &r)
	{
		return (l.base() >= r.base());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &l, const reverse_iterator<Iterator> &r)
	{
		return (l.base() <= r.base());
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &l, const reverse_iterator<Iterator> &r)
	{
		return (l.base() > r.base());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &l, const reverse_iterator<Iterator> &r)
	{
		return (l.base() < r.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+
			(typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator> &it)
	{
		return (it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-
			(const reverse_iterator<Iterator> &l,
			const reverse_iterator<Iterator> &r)
	{
		return (l.base() - r.base());
	}



}

#endif