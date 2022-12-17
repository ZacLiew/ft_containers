/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:56:33 by zhliew            #+#    #+#             */
/*   Updated: 2022/12/17 20:20:54 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <memory>
# include "utils.hpp"
# include "iterators.hpp"
# include "rbt.hpp"
# include "pair.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
			class															value_compare;
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef ft::pair<const key_type, mapped_type>					value_type;
			typedef Compare													key_compare;
			typedef Allocator												allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef ft::rbt<value_type, value_compare, allocator_type>		rbtree;
			typedef ft::node<value_type>									tree_node;
			typedef typename rbtree::iterator								iterator;
			typedef typename rbtree::const_iterator							const_iterator;
			typedef typename rbtree::reverse_iterator						reverse_iterator;
			typedef typename rbtree::const_reverse_iterator					const_reverse_iterator;
			// typedef ft::rbt<value_type, value_compare, allocator_type>		rbtree;
			// typedef ft::node<value_type>									tree_node;
			// typedef typename ft::rbt_iterator<value_type>					iterator;
			// typedef typename ft::rbt_iterator<const value_type> 			const_iterator;
			// typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			// typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef std::size_t												size_type;

			class value_compare
			{
				friend class map;
				
				protected:
					Compare comp;
					value_compare (Compare c)
						: comp(c) {}  // constructed with map's comparison object
				
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					
					bool operator()(const value_type &x, const value_type &y) const
					{
						return comp(x.first, y.first);
					}
			};

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _tree(comp, alloc), _key_comp(comp), _alloc(alloc) {}

			template<class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _tree(comp, alloc), _key_comp(comp), _alloc(alloc)
			{
				while (first != last)
				{
					_tree.insert(*first);
					first++;
				}
				tree_node *node = _tree.get_root();
				while (node->left != _tree.get_nil())
					node = node->left;
				node = _tree.get_root();
				while (node->right != _tree.get_nil())
					node = node->right;
			}

			map(map const& x)
				: _tree(x._tree), _key_comp(x._key_comp), _alloc(x._alloc) {}

			~map()
				{}

			map& operator=(map const &x)
			{
				if (this != &x)
				{
					_tree = x._tree;
					_key_comp = x._key_comp;
					_alloc = x._alloc;
				}
				return (*this);
			}

			iterator begin()
			{
				return (iterator(_tree.min_node(_tree.get_root())));
			}
			
			const_iterator begin() const
			{
				return (iterator(_tree.min_node(_tree.get_root())));
			}

			iterator end()
			{
				return (iterator(_tree.get_nil()));
			}
			
			const_iterator end() const
			{
				return (iterator(_tree.get_nil()));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(_tree.get_nil()));
			}
			
			const_reverse_iterator rbegin() const
			{
				return (reverse_iterator(_tree.get_nil()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator rend() const
			{
				return (reverse_iterator(this->begin()));
			}

			bool empty() const
			{
				return (_tree.empty());
			}

			size_type size() const
			{
				return (_tree.size());
			}

			size_type max_size() const
			{
				return (_tree.max_size());
			}

			mapped_type &operator[](const key_type& k)
			{
				mapped_type &tmp = (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
				return (tmp);
				// return ((*((this->insert(ft::make_pair(k,mapped_type()))).first)).second);
			}

			ft::pair<iterator,bool> insert(const value_type& val)
			{
				bool res = _tree.insert(_tree.create_node(val));
				tree_node *tmp = _tree.find(val);
				return (ft::pair<iterator, bool>(iterator(tmp), res));
			}

			iterator insert(iterator position, const value_type& val)
			{
				(void)position;
				_tree.insert(_tree.create_node(val));
				tree_node *tmp = _tree.find(val);
				return (iterator(tmp));
			}

			template<class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					_tree.insert(*first);
					first++;
				}
			}

			void erase(iterator position)
			{
				_tree.delete_node(position.base());
			}

			size_type erase(const key_type& k)
			{
				tree_node	*del = _tree.find(ft::make_pair(k, mapped_type()));

		        if (!del)
                    return (0);		
		       	_tree.delete_node(del);
		        return (1);
			}

     		void erase(iterator first, iterator last)
			{
				while (first != last)
				{
					_tree.delete_node(first.base());
					first++;
				}
			}

			void swap(map& x)
			{
				ft::swap(_tree, x._tree);
				ft::swap(_alloc, x._alloc);
				ft::swap(_key_comp, x._key_comp);
			}

			void clear()
			{
				_tree.clear(_tree.get_root());
			}

			key_compare key_comp() const
			{
				return (this->_key_comp);
			}

			value_compare value_comp() const
			{
				return (value_compare(this->_key_comp));
			}

			iterator find(const key_type& k)
			{
				tree_node *tmp = _tree.find(ft::make_pair(k, mapped_type()));

				if (tmp)
					return (iterator(tmp));
				return (this->end());
			}
			
			const_iterator find(const key_type& k) const
			{
				tree_node *tmp = _tree.find(ft::make_pair(k, mapped_type()));

				if (tmp)
					return (iterator(tmp));
				return (this->end());
			}

			size_type count(const key_type& k) const
			{
				tree_node *tmp = _tree.find(ft::make_pair(k, mapped_type()));

				if (tmp)
					return (1);
				return (0);
			}

			iterator lower_bound(const key_type& k)
			{
				return (iterator(_tree.lower_bound(ft::make_pair(k, mapped_type()))));
			}
			
			const_iterator lower_bound(const key_type& k) const
			{
				return (iterator(_tree.lower_bound(ft::make_pair(k, mapped_type()))));
			}

			iterator upper_bound(const key_type& k)
			{
				return (iterator(_tree.upper_bound(ft::make_pair(k, mapped_type()))));
			}
			
			const_iterator upper_bound(const key_type& k) const
			{
				return (iterator(_tree.upper_bound(ft::make_pair(k, mapped_type()))));
			}
			
			pair<iterator,iterator> equal_range(const key_type& k)
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			pair<const_iterator,const_iterator> equal_range(const key_type& k) const
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			allocator_type get_allocator() const
			{
				return (this->_alloc);
			}
		
		private:
			rbtree			_tree;
			key_compare		_key_comp;
			allocator_type	_alloc;
	};

	template <class T, class Alloc>
	bool	operator==(const map<T, Alloc> &l, const map<T, Alloc> &r) 
	{
		if (l.size() != r.size())
			return (false);
		return (ft::equal(l.begin(), l.end(), r.begin()));
	};

	template <class T, class Alloc>
	bool	operator!=(const map< T, Alloc >& l, const map< T, Alloc >& r)
	{
		return !(l == r);
	}

	template <class T, class Alloc>
	bool	operator <(const map<T, Alloc> &l, const map<T, Alloc> &r)
	{
		return ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
	}

	template <class T, class Alloc>
	bool	operator <=(const map<T, Alloc> &l, const map<T, Alloc> &r)
	{
		return !(r < l);
	}

	template <class T, class Alloc>
	bool	operator >(const map<T, Alloc> &l, const map<T, Alloc> &r)
	{
		return r < l;
	}

	template <class T, class Alloc>
	bool	operator >=(const map<T, Alloc> &l, const map<T, Alloc> &r)
	{
		return !(l < r);
	}

	template <class T, class Alloc>
	void	swap(map<T, Alloc> &x, map<T, Alloc>  &y)
	{
		x.swap(y);
	}
}

#endif
