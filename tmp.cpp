/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:54:39 by zhliew            #+#    #+#             */
/*   Updated: 2022/11/02 12:36:26 by zhliew           ###   ########.fr       */
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
#include <vector>         // std::vector

int main (void) {
  try {
    // vector throws a length_error if resized above max_size
    std::vector<int> myvector;
    myvector.resize(myvector.max_size()+1);
  }
  catch (const std::length_error& le) {
	  std::cerr << "Length error: " << le.what() << '\n';
  }
  return 0;
}