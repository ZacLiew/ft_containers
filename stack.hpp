/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:26:12 by zhliew            #+#    #+#             */
/*   Updated: 2022/11/03 19:47:16 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

		explicit stack (const container_type& ctnr = container_type())
			: c(ctnr) {}

		bool empty() const
		{
			return (c.empty());
		}

		size_type size() const
		{
			return (c.size());
		}

		value_type& top()
		{
			return (c.back());
		}

		const value_type& top() const
		{
			return (c.back());
		}

		void push(const value_type& val)
		{
			c.push_back(val);
		}

		void pop()
		{
			c.pop_back();
		}

		template<class T, class Container>
        friend bool operator==(const ft::stack<T, Container> &lhs,
                               const ft::stack<T, Container> &rhs);

        template<class T, class Container>
        friend bool operator!=(const ft::stack<T, Container> &lhs,
                               const ft::stack<T, Container> &rhs);

        template<class T, class Container>
        friend bool operator<(const ft::stack<T, Container> &lhs,
                              const ft::stack<T, Container> &rhs);

        template<class T, class Container>
        friend bool operator<=(const ft::stack<T, Container> &lhs,
                               const ft::stack<T, Container> &rhs);

        template<class T, class Container>
        friend bool operator>(const ft::stack<T, Container> &lhs,
                              const ft::stack<T, Container> &rhs);

        template<class T, class Container>
        friend bool operator>=(const ft::stack<T, Container> &lhs,
                               const ft::stack<T, Container> &rhs);

		private:
			container_type	c;
	};

	template<class T, class Container>
	bool operator==(const ft::stack<T, Container> &lhs,
					const ft::stack<T, Container> &rhs)
	{
		return (lhs.c == rhs.c);
	}

	template<class T, class Container>
	bool operator!=(const ft::stack<T, Container> &lhs,
					const ft::stack<T, Container> &rhs)
	{
		return (lhs.c != rhs.c);
	}

	template<class T, class Container>
	bool operator<(const ft::stack<T, Container> &lhs,
					const ft::stack<T, Container> &rhs)
	{
		return (lhs.c < rhs.c);
	}

	template<class T, class Container>
	bool operator<=(const ft::stack<T, Container> &lhs,
					const ft::stack<T, Container> &rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template<class T, class Container>
	bool operator>(const ft::stack<T, Container> &lhs,
					const ft::stack<T, Container> &rhs)
	{
		return (lhs.c > rhs.c);
	}

	template<class T, class Container>
	bool operator>=(const ft::stack<T, Container> &lhs,
					const ft::stack<T, Container> &rhs)
	{
		return (lhs.c >= rhs.c);
	}

}

#endif