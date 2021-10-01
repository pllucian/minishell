/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:39:17 by pllucian          #+#    #+#             */
/*   Updated: 2021/08/06 00:48:55 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int		len;

	len = 1;
	if (n < 0)
		len++;
	n /= 10;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	n1;
	int		len;
	char	*str;

	n1 = (long)n;
	if (n < 0)
		n1 *= -1;
	len = ft_len(n);
	str = (char *)(malloc(sizeof(char) * (len + 1)));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (!n1)
		str[len] = '0';
	while (n1)
	{
		str[len--] = n1 % 10 + '0';
		n1 /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
