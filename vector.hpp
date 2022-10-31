/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:46:13 by zhliew            #+#    #+#             */
/*   Updated: 2022/10/31 20:58:12 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include "iterators.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T														value_type;
			typedef Allocator												allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef ft::random_access_iterator<value_type>					iterator;
			typedef ft::random_access_iterator<const value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t													size_type;
			
			explicit vector(const allocator_type &alloc = allocator_type())
				: _alloc(alloc), _size(0), _capacity(0), _arr(nullptr) {}

			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
				: _size(0), _capacity(0), _alloc(alloc)
			{
				this->assign(n, val);
			}
	
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type())
				: _size(0), _capacity(0), _alloc(alloc)
			{
				this->assign(first, last);
			}

			vector(const vector &x)
				: _size(x._size), _capacity(x._capacity), _alloc(x._alloc)
			{
				_arr = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_arr + i, x[i]);
			}

			~vector()
			{
				this->clear();
				_alloc.deallocate(_arr, _capacity);
			}

			vector &operator=(const vector &x)
			{
				if (this != &x)
				{
					this->clear();
					this->assign(x.begin(), x.end());
				}
				return (*this);
			}

			iterator begin()
			{
				return (iterator(_arr));
			}
			
			const_iterator begin() const
			{
				return (const_iterator(_arr));
			}

			iterator end()
			{
				return (iterator(_arr + _size));
			}
			
			const_iterator end() const
			{
				return (const_iterator(_arr + _size));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->end()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->begin()));
			}

			size_type size() const
			{
				return (_size);
			}

			size_type max_size() const
			{
				return (_alloc.max_size());
			}

			void resize(size_type n, value_type val = value_type())
			{
				
			}
			
			size_type capacity() const
			{
				return (_capacity);
			}

			bool empty() const
			{
				return (_size == 0);
			}

		private:
			value_type		*_arr;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;
	};
}

#endif
