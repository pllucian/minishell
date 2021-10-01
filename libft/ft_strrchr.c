/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:02:38 by pllucian          #+#    #+#             */
/*   Updated: 2021/10/03 17:52:50 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*p;

	if (!s)
		return (NULL);
	if (!*s)
		return (NULL);
	p = s + ft_strlen(s) - 1;
	while (p != s && *p != (char)c)
		p--;
	if (*p == (char)c)
		return ((char *)p);
	else
		return (NULL);
}
