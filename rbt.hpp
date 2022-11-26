/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:12:16 by zhliew            #+#    #+#             */
/*   Updated: 2022/11/26 18:11:01 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

#include "iterators.hpp"
#include "utils.hpp"

namespace ft
{
	template <typename T>
	class node
	{
		public:

		typedef T	value_type;
		value_type	value;
		node		*left;
		node		*right;
		node		*parent;
		bool		isBlack;

		node()
			: value(0), left(0), right(0), parent(0), isBlack(false) {} 

		node(const node &ref)
			: value(ref.value), left(ref.left), right(ref.right),
			parent(ref.parent), isBlack(ref.isBlack) {} 

		~node()
			{}
		
		node &operator=(const node &ref)
		{
			value = ref.value;
			left = ref.left;
			right = ref.right;
			parent = ref.parent;
			isBlack = ref.isBlack;
			return (*this);
		}
	};

	template <typename T>
	class rbt_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category		iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference				reference;
			typedef ft::node<value_type>															tree_node;

			rbt_iterator()
				: _node(nullptr);
			
			rbt_iterator(tree_node *node)
				: _node(node) {}

			random_access_iterator(const rbt_iterator &ref)
				: _node(ref._node) {}

			~random_access_iterator()
				{}

			rbt_iterator &operator=(const rbt_iterator &ref)
			{
				if (this == &ref)
					return (*this);
				_node = ref._node;
				return (*this);
    		}

			reference &operator*()
			{
				return (_node->value);
			}

			pointer operator->() const
			{
            	return (&(_node->value));
        	}

			rbt_iterator &operator++()
			{
				if (!_node)
					return *this;
				else if (_node->right)
				{
					_node = _node->right
					while (_node && _node->left)
						_node = _node->left;
				}
				else if (_node = max_node(_node))
					_node = 0;
				else
				{
					while (_node->parent->right == _node)
						_node = _node->parent;
					_node = _node->parent;
				}
				return *this;
			}

			rbt_Iterator	operator++(int)
			{
				rbt_iterator tmp = *this;
				(*this)++;
				return (tmp);
			}

			rbt_Iterator	&operator--()
			{
				if (!_node)
					_node = max_node(_node);
				else if (_node->left)
				{
					_node = _node->left;
					while (_node->right)
						_node = _node->right;
				}
				else
				{
					while (_node->parent->left == _node)
						_node = _node->parent;
					_node = _node->parent;
				}
				return (*this);
			}

			rbt_Iterator	operator--(int)
			{
				rbt_iterator tmp = *this;
				(*this)--;
				return (tmp);
			}

			bool operator==(rbt_iterator const &ref) const
			{
				return (ref._node == _node);
			}

			bool operator!=(rbt_iterator const &it) const
			{
				return (ref._node != _node);
			}

			operator rbt_iterator<const T>() const
			{
            	return (rbt_iterator<const T>(_node));
        	}
		
		private:
			tree_node	_node;

			tree_node	max_node(tree_node node) const
			{
				if (node)
				{
					while (node->parent)
						node = node->parent;
					while (node->right)
						node = node->right;
				}
				return (node);
			}
	};

	template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class rbt
	{
		public:



		private:



	};
}

#endif