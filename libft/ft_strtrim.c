/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:55:49 by pllucian          #+#    #+#             */
/*   Updated: 2021/08/05 22:05:07 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*p;
	const char	*p_begin;
	const char	*p_end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	p_begin = s1;
	p_end = s1 + ft_strlen(s1);
	while (ft_strchr(set, *p_begin) && p_begin != p_end)
		p_begin++;
	while (ft_strrchr(set, *p_end) && p_begin != p_end)
		p_end--;
	if (p_begin == p_end)
		return (ft_strdup(""));
	p = (char *)malloc(sizeof(char) * (p_end - p_begin + 2));
	if (!p)
		return (NULL);
	ft_strlcpy(p, p_begin, p_end - p_begin + 2);
	return (p);
}
