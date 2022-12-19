/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:34:46 by zhliew            #+#    #+#             */
/*   Updated: 2022/12/19 19:51:02 by zhliew           ###   ########.fr       */
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
	ft::map<int, std::string>::iterator it;

	mp[5] = "funny";
	mp[10] = "fgzgxfn";
	mp[8] = "fgzgxfn";
	mp[11] = "fgzgxfn";

	it = mp.begin();
	std::cout << it.base()->value.first << std::endl;
	std::cout << it.base()->left->value.first << std::endl;
	std::cout << it.base()->right->value.first << std::endl;
	std::cout << it.base()->parent->value.first << std::endl;
}