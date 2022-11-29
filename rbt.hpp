/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:12:16 by zhliew            #+#    #+#             */
/*   Updated: 2022/11/29 19:28:44 by zhliew           ###   ########.fr       */
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
			typedef T											value;
			typedef Compare										value_compare;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef rbt_iterator<T>								iterator;
			typedef rbt_iterator<const T>						const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef std::size_t									size_type;
			typedef node<T>										tree_node;

			tree_node *find(tree_node *node, value &key) const
			{
				while (node)
				{
					if (_comp(node->value, key))
						node = node->left;
					else if (_comp(key, node->value))
						node = node->right;
					else
						return (node);
				}
				return (0);
			}

			tree_node *max_node(tree_node *node) const
			{
				if (node)
				{
					while (node->right)
						node = node->right;
				}
				return (node);
			}

			tree_node *min_node(tree_node *node) const
			{
				if (node)
				{
					while (node->left)
						node = node->left;
				}
				return (node);
			}

			void	rotate_left(tree_node *x)
			{
				tree_node *y = x->right;
				x->right = y->left;
				if (y->left)
					y->left->parent = x;
				y->parent = x->parent;
				if (!x->parent)
					this->_root = y;
				else if (x->parent->left == x)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void	rotate_right(tree_node *x)
			{
				tree_node *y = x->left;
				x->left = y->right;
				if (y->right)
					y->right->parent = x;
				y->parent = x->parent;
				if (!x->parent)
					this->_root = y;
				else if (x->parent->left == x)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->right = x;
				x->parent = y;
			}

			tree_node *get_root()
			{
				return (this->_root);
			}

		private:
			allocator_type	_alloc;
			value_compare	_comp;
			size_type		_height;
			tree_node		*_root;
	};
}

#endif