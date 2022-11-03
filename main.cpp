/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:34:46 by zhliew            #+#    #+#             */
/*   Updated: 2022/11/03 19:24:34 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <vector>

int main()
{
	std::vector<int> vc;

	std::cout << "max size: " << vc.max_size() <<std::endl;
	std::cout << "size: " << vc.size() <<std::endl;
	std::cout << "capacity: " << vc.capacity() <<std::endl;
	vc.resize(12);
	std::cout << "size: " << vc.size() <<std::endl;
	std::cout << "capacity: " << vc.capacity() <<std::endl;
	std::cout << "vector[0]: " << vc[0] <<std::endl;
	vc.push_back(1);
	std::cout << "size: " << vc.size() <<std::endl;
	std::cout << "vector[0]: " << vc[0] <<std::endl;
	std::cout << "vector back: " << vc.back() << std::endl; 
	std::cout << "size: " << vc.size() <<std::endl;
	std::cout << "vector[0]: " << vc[0] <<std::endl;
	std::cout << "vector back: " << vc.back() << std::endl;
	vc.resize(0);
	std::cout << vc.empty() << std::endl;
	return (0);
}