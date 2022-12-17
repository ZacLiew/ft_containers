/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:34:46 by zhliew            #+#    #+#             */
/*   Updated: 2022/12/17 20:18:07 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
// #include "vector.hpp"
// #include <vector>
#include "map.hpp"
#include <map>
#include "vector.hpp"
#include <vector>
#include <list>

int main()
{
    ft::map<int, std::string> mp;
	ft::map<int, std::string>::reverse_iterator it;
	ft::map<int, std::string>::reverse_iterator end;

	mp[42] = "fgzgxfn";
	mp[25] = "funny";
	mp[80] = "hey";
	it = mp.rbegin();
	end = mp.rend();
	for (; it != end; it++)
	{
		std::cout << "key: " << it->first << " | value: " << it->second << std::endl;
	}
	end--;
	std::cout << end->first << std::endl;
}