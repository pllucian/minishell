/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 11:49:45 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/01 19:30:21 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int					sign;
	unsigned long long	nbr;

	sign = 1;
	nbr = 0;
	while (*nptr == '\t' || *nptr == '\n' || *nptr == '\v' \
	|| *nptr == '\f' || *nptr == '\r' || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while ('0' <= *nptr && *nptr <= '9')
		nbr = nbr * 10 + *nptr++ - '0';
	if (sign == 1 && nbr > 2147483647)
		return (-1);
	if (sign == -1 && nbr > 2147483648)
		return (0);
	return ((int)nbr * sign);
}
