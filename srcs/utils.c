/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 22:34:42 by pllucian          #+#    #+#             */
/*   Updated: 2021/10/01 00:35:32 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_arraylen(void **array)
{
	size_t		len;

	if (!array)
		return (0);
	len = 0;
	while (*array++)
		len++;
	return (len);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' \
		|| c == '\n' || c == '\v' \
		|| c == '\f' || c == '\r')
		return (c);
	return (0);
}

int	ft_strisspace(char *str)
{
	if (!str)
		return (0);
	while (*str == ' ' || *str == '\t' \
		|| *str == '\n' || *str == '\v' \
		|| *str == '\f' || *str == '\r')
		str++;
	if (!*str)
		return (1);
	return (0);
}

int	ft_strisdigit(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit((int)*str++))
			return (0);
	}
	return (1);
}

long long	ft_atoll(const char *nptr)
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
	if (sign == 1 && nbr > 9223372036854775807)
		return (-1);
	if (sign == -1 && nbr > 9223372036854775807)
		return (0);
	return ((long long)nbr * sign);
}
