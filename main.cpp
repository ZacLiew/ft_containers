/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:34:46 by zhliew            #+#    #+#             */
/*   Updated: 2022/11/30 16:18:52 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include "vector.hpp"
#include <vector>

int main()
{
	ft::vector<int> a(5, 10);
	ft::vector<int>	b(5, 10);
	
	std::cout << a[0] << '\n' << std::endl;
	a.insert(a.begin(), a.begin(), a.begin() + 3);
	std::cout << a[0] << std::endl;
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
	return (0);
}