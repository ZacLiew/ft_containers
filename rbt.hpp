/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:12:16 by zhliew            #+#    #+#             */
/*   Updated: 2022/11/30 21:30:29 by zhliew           ###   ########.fr       */
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
			typedef node<value_type>																tree_node;

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
			typedef T											value_type;
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

			tree_node *create_node(value_type const &val, tree_node *parent)
			{
				tree_node *new_node = _alloc.allocate(1);
				_alloc.construct(&(new_node->value), val);
				new_node->left = NULL;
				new_node->right = NULL;
				new_node->parent = parent;
				return (new_node);
			}

			void	del_node(tree_node *node)
			{
				if (node)
				{
					if (node->value)
						_alloc.destroy(&(node->value))
					_alloc.deallocate(node, 1);
				}
			}
			
			tree_node *find(tree_node *node, value_type &key) const
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

			void	balance_insert(tree_node *node)
			{
				tree_node *tmp;
				while (node->parent->isBlack == false)
				{
					if (node->parent == node->parent->parent->right)
					{
						tmp = node->parent->parent->left;
						if (tmp->isBlack == false)
						{
							tmp->isBlack = true;
							node->parent->isBlack = true;
							node->parent->parent->isBlack = false;
							node = node->parent->parent;
						}
						else
						{
							if (node == node->parent->left)
							{
								node = node->parent;
								rotate_right(node);
							}
							node->parent->isBlack = true;
							node->parent->parent->isBlack = false;
							rotate_left(node->parent->parent);
						}
					}
					else
					{
						tmp = node->parent->parent->right;
						if (tmp->isBlack == false)
						{
							tmp->isBlack = true;
							node->parent->isBlack = true;
							node->parent->parent->isBlack = false;
							node = node->parent->parent;
						}
						else
						{
							if (node == node->parent->right)
							{
								node = node->parent;
								rotate_left(node);
							}
							node->parent->isBlack = true;
							node->parent->parent->isBlack = false;
							rotate_right(node->parent->parent);
						}
					}
					if (node == _root)
						break;
				}
				_root->isBlack = true;
			}

			bool insert(tree_node *new_node)
			{
				if (!_root)
				{
					_root = new_node;
					new_node->isBlack = true;
				}
				else
				{
					tree_node *tmp = _root;
					while (tmp)
					{
						if (!_comp(tmp->value, new_node->value) && !_comp(new_node->value, tmp->value))
						{
							del_node(new_node);
							return (false);
						}
						else if (_comp(tmp->value, new_node->value))
						{
							if (tmp->right)
								tmp = tmp->right;
							else
							{
								tmp->right = new_node;
								new_node->parent = tmp;
								break;
							}
						}
						else
						{
							if (tmp->left)
								tmp = tmp->left;
							else
							{
								tmp->left = new_node;
								new_node->parent = tmp;
								break;
							}
						}
					}
				}
				new_node->isBlack = false;

				return (true);
			}

			void	delete_node(tree_node *node)
			{
				bool	isBlack_original = node->isBlack;

				if ()
			}

		private:
			allocator_type	_alloc;
			value_compare	_comp;
			size_type		_height;
			tree_node		*_root;
			tree_node		*_NIL_NODE;
	};
}

#endif