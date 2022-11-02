/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:59:38 by zhliew            #+#    #+#             */
/*   Updated: 2022/11/02 19:01:41 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{

	template<class T>
	void	swap(T &l, T &r)
	{
		T tmp = l;

		l = r;
		r = tmp;
	};
}

#endif