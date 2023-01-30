/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t len)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;
	size_t			j;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while ((s1[i]) && (i < len))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	j = 0;
	while ((s2[j]) && (j < len))
		j++;
	if (i != j)
		return (s1[i] - s2[i]);
	return (0);
}
