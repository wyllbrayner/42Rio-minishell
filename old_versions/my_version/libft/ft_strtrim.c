/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_set(char const *str, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strret;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && (check_set(&s1[start], set)))
		start++;
	end = (ft_strlen(s1));
	while (end > start && (check_set(&s1[end - 1], set)))
		end--;
	strret = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!strret)
		return (NULL);
	i = 0;
	while (start < end)
		strret[i++] = s1[start++];
	strret[i] = '\0';
	return (strret);
}

static size_t	check_set(char const *str, char const *set)
{
	while (*set)
	{
		if (*str == *set)
			return (1);
		set++;
	}
	return (0);
}
