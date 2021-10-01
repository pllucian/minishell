/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:18:05 by pllucian          #+#    #+#             */
/*   Updated: 2021/08/05 22:05:37 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		little_len;

	if (*little)
	{
		little_len = ft_strlen(little);
		while (1)
		{
			while (big)
			{
				if (!len-- || !*big)
					return (NULL);
				if (*big++ == *little)
					break ;
			}
			if (little_len > len + 1)
				return (NULL);
			if (!ft_memcmp(big, little + 1, little_len - 1))
				break ;
		}
		big--;
	}
	return ((char *)big);
}
