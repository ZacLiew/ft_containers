/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:46:13 by zhliew            #+#    #+#             */
/*   Updated: 2022/10/24 16:59:26 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>

namespace ft
{
	template <typename T>
	class VectorIterator
	{
		public:
			typedef typename T::value_type	value_type;
			typedef value_type*				ptr_type;
			typedef value_type const*		const_ptr_type;
			typedef value_type&				ref_type;
			typedef value_type const&		const_ref_type;

		protected:
			ptr_type ptr;

		public:
			VectorIterator()
				: ptr(nullptr) {}

			VectorIterator(ptr_type ptr)
				: ptr(ptr) {}

			VectorIterator(VectorIterator const& ref)
				: ptr(ref.ptr) {}

			VectorIterator& operator=(VectorIterator const &ref)
			{
				this->ptr = ref.ptr;
				return (*this);
			}

			virtual ~VectorIterator()
				{}

			VectorIterator& operator++()
			{
				this->ptr++;
				return (*this);
			}

			VectorIterator operator++(int)
			{
				VectorIterator tmp = *this;
				this->ptr++;
				return (tmp);
			}

			VectorIterator& operator--()
			{
				this->ptr--;
				return (*this);
			}

			VectorIterator operator--(int)
			{
				VectorIterator tmp = *this;
				this->ptr--;
				return (tmp);
			}

			ref_type operator[](int val)
			{
				return (*(this->p + val));
			}

			const_ref_type operator[](int val) const
			{
				return (*(this->p + val));
			}

			ref_type operator*()
			{
				return (*this->ptr);
			}

			const_ref_type operator*() const
			{
				return (*this->ptr);
			}

			ptr_type operator->()
			{
				return (this->ptr);
			}

			const_ptr_type operator->() const
			{
				return (this->ptr);
			}

			VectorIterator& operator+=(int val)
			{
				this->ptr += val;
				return (*this);
			}

			VectorIterator& operator-=(int val)
			{
				this->ptr -= val;
				return (*this);
			}

			VectorIterator operator+(int value) const
			{
				VectorItertor tmp(*this)

				this->ptr += value;
				return (tmp );
			}

			VectorIterator operator-(int value) const
			{
				VectorItertor tmp(*this)

				this->ptr -= value;
				return (tmp);
			}
	};

	template <typename T, typename Allocator = std::allocator<T> >
	class Vector
	{
		public:
			typedef T				value_type;
			typedef Allocator		allocator_type;
			typedef std::size_t		size_type;
			



		public:
			Vector() : container(NULL), capacity(0), size(0) {}
			Vector(unsigned long size, value_type const &val=value_type()) :
				container(NULL), capacity(0), size(0)
				{
					
				}
			Vector(Vector const &other) : 
			virtual ~Vector()
				{
					
				}

		private:
			value_type*				container
			unsigned long			size;
			unsigned long	capacity;
	};
}

#endif
