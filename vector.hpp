/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:46:13 by zhliew            #+#    #+#             */
/*   Updated: 2022/11/30 21:30:03 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include "utils.hpp"
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
			typedef std::size_t												size_type;
			
			explicit vector(const allocator_type &alloc = allocator_type())
				: _alloc(alloc), _size(0), _capacity(0), _arr(nullptr) {}

			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
				: _size(0), _capacity(0), _alloc(alloc)
			{
				this->assign(n, val);
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
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
				if (this->_capacity != 0)
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
				if (n < _size)
				{
					for (size_type i = _size; i > n; i--)
						_alloc.destroy(&_arr[i - 1]);
				}
				if (n > _size)
				{
					if (n > _capacity)
						this->reserve(_increase_capacity(n));
					for (size_type i = _size; i < n; i++)
						_alloc.construct(&_arr[i], val);
				}
				_size = n;
			}
			
			size_type capacity() const
			{
				return (_capacity);
			}

			bool empty() const
			{
				return (_size == 0);
			}

			void reserve(size_type n)
			{
				if (n > this->max_size())
					throw std::length_error("vector::_M_fill_insert");
				if (n > _capacity)
				{
					value_type *new_arr = _alloc.allocate(n);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(&new_arr[i], _arr[i]);
					this->clear();
					if (this->_capacity != 0)
						_alloc.deallocate(_arr, _capacity);
					_arr = new_arr;
					_capacity = n;
				}
			}

			reference operator[](size_type n)
			{
				return (_arr[n]);
			}

			const_reference operator[](size_type n) const
			{
				return (_arr[n]);
			}

			reference at(size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("Out of range");
				return (_arr[n]);
			}
			
			const_reference at(size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("Out of range");
				return (_arr[n]);
			}

			reference front()
			{
				return (_arr[0]);
			}
			
			const_reference front() const
			{
				return (_arr[0]);
			}

			reference back()
			{
				return (_arr[_size - 1]);
			}
			
			const_reference back() const
			{
				return (_arr[_size - 1]);
			}

			value_type* data()
			{
				return (_arr);
			}
			
			const value_type* data() const
			{
				return (_arr);
			}

			template <class InputIterator> 
			void assign(InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				size_type n = last - first;

				this->clear();
				if (n > _capacity)
					this->reserve(_increase_capacity(n));
				for (size_type i = 0; i < n; i++)
					_alloc.construct(&_arr[i], *first++);
				_size = n;
			}

			void assign(size_type n, const value_type& val)
			{
				this->clear();
				if (n > _capacity)
					this->reserve(_increase_capacity(n));
				for (size_type i = 0; i < n; i++)
					_alloc.construct(&_arr[i], val);
				_size = n;
			}

			void push_back(const value_type& val)
			{
				if (_size == _capacity)
					this->reserve(_increase_capacity(_size + 1));
				_alloc.construct(&_arr[_size], val);
				_size++;
			}

			void pop_back()
			{
				_alloc.destroy(&_arr[_size - 1]);
				_size--;
			}

			iterator insert(iterator position, const value_type& val)
			{
				size_type i = position - this->begin();

				this->insert(position, 1, val);
				return (this->begin() + i);
			}

    		void insert(iterator position, size_type n, const value_type& val)
			{
				size_type	i = position - this->begin();

				if (_size + n > _capacity)
					this->reserve(_increase_capacity(_size + n));
				for (size_type back = n + _size - 1; back > i + n - 1; back--)
				{
					_alloc.construct(&_arr[back], _arr[back - n]);
					_alloc.destroy(&_arr[back - n]);
				}
				for (size_type j = 0; j < n; j++)
					_alloc.construct(&_arr[j + i], val);
				_size += n;
			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				size_type	i = position - this->begin();
				size_type	n = last - first;

				if (_size + n > _capacity)
					this->reserve(_increase_capacity(_size + n));
				for (size_type back = n + _size - 1; back > i + n - 1; back--)
				{
					_alloc.construct(&_arr[back], _arr[back - n]);
					_alloc.destroy(&_arr[back - n]);
				}
				for (size_type j = 0; j < n; j++)
					_alloc.construct(&_arr[j + i], *first++);
				_size += n;
			}

			iterator erase(iterator position)
			{
				size_type	val = position - begin();

				_alloc.destroy(&_arr[val]);
				_size--;
				for (size_type i = val; i < _size; i++)
				{
					_alloc.construct(&_arr[i], &_arr[i + 1]);
					_alloc.destroy(&_arr[i + 1]);
				}
				return (position);
			}
			
			iterator erase(iterator first, iterator last)
			{
				size_type	val = first - begin();
				size_type	n = last - first;

				for (iterator tmp = first; tmp != last; tmp++)
					_alloc.destroy(&(*tmp));
				_size -= n;
				for (size_type i = val; i < _size; i++)
				{
					_alloc.construct(&_arr[i + n], &_arr[i + n + 1]);
					_alloc.destroy(&_arr[i + n + 1]);
				}
				return (first);
			}

			void swap(vector& x)
			{
				if (*this == x)
					return;
				ft::swap(_arr, x._arr);
				ft::swap(_capacity, x._capacity);
				ft::swap(_size, x._size);
				ft::swap(_alloc, x._alloc);
			}

			void clear()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_arr[i]);
				_size = 0;
			}

			allocator_type get_allocator() const
			{
				return (_alloc);
			}

		private:
			value_type		*_arr;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

			size_type	_increase_capacity(size_type n)
			{
				size_type cap = 1;

				while (cap < n)
					cap *= 2;
				return (cap);
			}
	};

	template<class T, class Alloc>
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
        if (lhs.size() != rhs.size())
			return (false);
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template<class T, class Alloc>
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
        return !(lhs == rhs);
    }

    template<class T, class Alloc>
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) 
	{
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template<class T, class Alloc>
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
        return (rhs < lhs);
    }

    template<class T, class Alloc>
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
        return (lhs == rhs || lhs < rhs);
    }

    template<class T, class Alloc>
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
        return (lhs == rhs || lhs > rhs);
    }

    template<class T, class Alloc>
    void swap(ft::vector<T, Alloc> &lhs, ft::vector<T, Alloc> &rhs)
	{
        lhs.swap(rhs);
    }
}

#endif
