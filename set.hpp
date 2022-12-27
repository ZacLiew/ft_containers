/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:07:57 by zhliew            #+#    #+#             */
/*   Updated: 2022/12/27 20:23:07 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <iostream>
# include <memory>
# include "utils.hpp"
# include "iterators.hpp"
# include "rbt.hpp"
# include "pair.hpp"

namespace ft
{
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<const T> >
	class set
	{
		public:
			typedef T														key_type;
			typedef const T													value_type;
			typedef Compare													key_compare;
			typedef Compare													value_compare;
			typedef Alloc													allocator_type;
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
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef std::size_t												size_type;

			explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
				: _tree(comp, alloc), _key_comp(comp), _alloc(alloc) {}

			template <class InputIterator>
			set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
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

			set(const set& x)
				: _tree(x._tree), _key_comp(x._key_comp), _alloc(x._alloc) {}

			~set()
				{}

			set& operator= (const set& x)
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

			size_type erase(const value_type& val)
			{
				tree_node	*del = _tree.find(val);

		        if (!del)
                    return (0);		
		       	_tree.delete_node(del);
		        return (1);
			}

     		void erase(iterator first, iterator last)
			{
				iterator tmp = first;

				while (first != last)
				{
					tmp++;
					_tree.delete_node(first.base());
					first = tmp;
				}
			}

			void swap(set &x)
			{
				_tree.swap(x._tree);
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
				return (this->_key_comp);
			}

			iterator find(const value_type& val)
			{
				tree_node *tmp = _tree.find(val);

				if (tmp)
					return (iterator(tmp));
				return (this->end());
			}

			const_iterator find(const value_type& val) const
			{
				tree_node *tmp = _tree.find(val);

				if (tmp)
					return (iterator(tmp));
				return (this->end());
			}

			size_type count(const value_type& val) const
			{
				tree_node *tmp = _tree.find(val);

				if (tmp)
					return (1);
				return (0);
			}

			iterator lower_bound(const value_type& val) const
			{
				return (iterator(_tree.lower_bound(val)));
			}

			iterator upper_bound(const value_type& val) const
			{
				return (iterator(_tree.upper_bound(val)));
			}

			
			pair<iterator,iterator> equal_range(const value_type& val) const
			{
				return (ft::make_pair(lower_bound(val), upper_bound(val)));
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
	bool	operator==(const set<T, Alloc> &l, const set<T, Alloc> &r) 
	{
		if (l.size() != r.size())
			return (false);
		return (ft::equal(l.begin(), l.end(), r.begin()));
	};

	template <class T, class Alloc>
	bool	operator!=(const set< T, Alloc >& l, const set< T, Alloc >& r)
	{
		return !(l == r);
	}

	template <class T, class Alloc>
	bool	operator <(const set<T, Alloc> &l, const set<T, Alloc> &r)
	{
		return ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
	}

	template <class T, class Alloc>
	bool	operator <=(const set<T, Alloc> &l, const set<T, Alloc> &r)
	{
		return !(r < l);
	}

	template <class T, class Alloc>
	bool	operator >(const set<T, Alloc> &l, const set<T, Alloc> &r)
	{
		return r < l;
	}

	template <class T, class Alloc>
	bool	operator >=(const set<T, Alloc> &l, const set<T, Alloc> &r)
	{
		return !(l < r);
	}

	template <class T, class Alloc>
	void	swap(set<T, Alloc> &x, set<T, Alloc>  &y)
	{
		x.swap(y);
	}
}

#endif
