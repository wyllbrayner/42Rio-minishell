/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 13:55:50 by paugusto          #+#    #+#             */
/*   Updated: 2021/11/30 17:52:39 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;
	char	x;

	ptr = (char *)s;
	x = (char)c;
	i = 0;
	if (x == '\0')
	{
		i = ft_strlen(ptr);
		return (&ptr[i]);
	}
	while (ptr[i] != '\0')
	{
		if (ptr[i] == x)
			return (&ptr[i]);
		i++;
	}
	ptr = NULL;
	return (ptr);
}
