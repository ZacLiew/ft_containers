/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:54:39 by zhliew            #+#    #+#             */
/*   Updated: 2022/11/03 19:18:52 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// class tmp
// {
// 	private:
// 		int i;

// 	public:
// 		tmp(int x, int y) : i(x + y)
// 		{
// 			std::cout << i << std::endl;
// 		}
// };

// int main()
// {
// 	// for (int j = 0; j <= 8; j++)
// 	// {
// 	// 	for (int i = 0; i <= 4 - abs(4 - j); i++)
// 	// 		std::cout << "#";
// 	// 	std::cout << "\n";
// 	// }
// 	tmp a(1, 2);
// 	return (0);
// }

#include <iostream>       // std::cerr
#include <stdexcept>      // std::length_error
#include "vector.hpp"         // std::vector

int main (void) {

  ft::vector<int> second (4,100);                       // four ints with value 100

  std::cout << second[0] << std::endl;
  return 0;
}