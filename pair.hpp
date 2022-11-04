/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:48:52 by zhliew            #+#    #+#             */
/*   Updated: 2022/11/04 15:13:31 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		public:
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;

			pair()
				: first(), second() {}

			template<class U, class V>
			pair(const pair<U, V> &pr)
				: first(p.first), second(p.second) {}

			pair(const first_type &a, const second_type &b)
				: first(a), second(b) {}
			
			~pair()
				{}
			
			pair &operator=(const pair& pr)
			{
				if (*this != p)
				{
					first = p.first;
					second = p.second;
				}
				return (*this);
			}
	};

	template <class T1, class T2>
	pair<T1,T2>	make_pair(T1 x, T2 y)
	{
		return(pair<T1, T2>(x, y));
	}

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T1, class T2>
	bool operator> (const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(lhs < rhs));
	}

}

#endif