/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:34:46 by zhliew            #+#    #+#             */
/*   Updated: 2022/12/06 19:14:26 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
// #include "vector.hpp"
// #include <vector>
#include "map.hpp"


int main()
{
	// ft::vector<int> a(5, 10);
	// ft::vector<int>	b(5, 10);
	
	// std::cout << a[0] << '\n' << std::endl;
	// a.insert(a.begin(), a.begin(), a.begin() + 3);
	// std::cout << a[0] << std::endl;
	// std::vector<int>::iterator it = vc.begin();
	// std::vector<int>::iterator y = x.begin();
	// std::vector<float>::iterator tmp = f.begin();
	// if (it == y)
	// 	std::cout << "here" << std::endl;
	// f.push_back(1.1);
	// vc = f;
	// std::cout << "vector[0]: " << vc[0] <<std::endl;
	// std::cout << "max size: " << vc.max_size() <<std::endl;
	// std::cout << "size: " << vc.size() <<std::endl;
	// std::cout << "capacity: " << vc.capacity() <<std::endl;
	// vc.resize(12);
	// std::cout << "size: " << vc.size() <<std::endl;
	// std::cout << "capacity: " << vc.capacity() <<std::endl;
	// std::cout << "vector[0]: " << vc[0] <<std::endl;
	// vc.push_back(1);
	// std::cout << "size: " << vc.size() <<std::endl;
	// std::cout << "vector[0]: " << vc[0] <<std::endl;
	// std::cout << "vector back: " << vc.back() << std::endl; 
	// std::cout << "size: " << vc.size() <<std::endl;
	// std::cout << "vector[0]: " << vc[0] <<std::endl;
	// std::cout << "vector back: " << vc.back() << std::endl;
	// vc.resize(0);
	// std::cout << vc.empty() << std::endl;
	// std::map<int, int> mp;
  
    // // insert elements in random order
    // mp.insert(std::make_pair(12, 30));
    // mp.insert(std::make_pair(11, 10));
    // mp.insert(std::make_pair(15, 50));
    // mp.insert(std::make_pair(14, 40));
  
    // // when 11 is present
    // std::map<int,int>::iterator it = mp.upper_bound(11);
    // cout << "The upper bound of key 11 is ";
    // cout << (*it).first << " " << (*it).second << endl;
  
    // // when 13 is not present
    // it = mp.upper_bound(13);
    // cout << "The upper bound of key 13 is ";
    // cout << (*it).first << " " << (*it).second << endl;
  
    // // when 17 is exceeds the maximum key, so size
    //     // of mp is returned as key and value as 0.
    // it = mp.upper_bound(17);
    // // cout << "The upper bound of key 17 is ";
    // cout << (*it).first << " " << (*it).second;
	ft::map<int, int> m;
	// std::less<int> comp;
	// std::cout << comp(1, 1) << std::endl;
	return (0);
}