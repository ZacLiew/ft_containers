/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:59:38 by zhliew            #+#    #+#             */
/*   Updated: 2022/11/03 18:49:02 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
	template <bool Cond, class T = void>
	struct enable_if
		{};
	
	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <class T, T v>
	struct integral_constant
	{
		static const T					value = v;
		typedef T						value_type;
		typedef integral_constant<T,v>	type;

		operator T() const
		{
			return (v);
		}
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	template <class T>
	struct is_integral : public false_type
		{};

	template <class T> 
	struct is_integral<const T> : public is_integral<T>
		{};

	template <class T>
	struct is_integral<volatile const T> : public is_integral<T>
		{};

	template <class T>
	struct is_integral<volatile T> : public is_integral<T>
		{};

	template <>
	struct is_integral<unsigned char> : public true_type
		{};
	
	template <>
	struct is_integral<unsigned short> : public true_type
		{};

	template <>
	struct is_integral<unsigned int> : public true_type
		{};
	
	template <>
	struct is_integral<unsigned long> : public true_type
		{};
	
	template <>
	struct is_integral<unsigned long long> : public true_type
		{};
	
	template <>
	struct is_integral<signed char>		:	public true_type
		{};
	
	template <>
	struct is_integral<short> : public true_type
		{};
	
	template <>
	struct is_integral<int> : public true_type
		{};
	
	template <>
	struct is_integral<long> : public true_type
		{};
	
	template <>
	struct is_integral<long long> : public true_type
		{};
	
	template <>
	struct is_integral<char> : public true_type
		{};
	
	template <>
	struct is_integral<bool> : public true_type
		{};

	template <class InputIterator1, class InputIterator2> 
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
				return (false);
		}
		return (true);
	}
	
	template <class InputIterator1, class InputIterator2, class BinaryPredicate> 
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!pred(*first1, *first2))
				return (false);
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
	{
		for (; (first1 != last1); ++first1, ++first2)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		for (; (first1 != last1); ++first1, ++first2)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return (false);
			else if (comp(*first1, *first2))
				return (true);
		}
		return (first2 != last2);
	}

	template<class T>
	void	swap(T &l, T &r)
	{
		T tmp = l;

		l = r;
		r = tmp;
	}
}

#endif