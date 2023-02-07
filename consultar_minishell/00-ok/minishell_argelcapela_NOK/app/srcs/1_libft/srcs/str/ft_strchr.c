/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:44:17 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/15 17:01:17 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

char	*ft_strchr(const char *str, int ch)
{
	while (*str)
	{
		if (*str == (unsigned char)ch)
			return ((char *)str);
		str++;
	}
	if ((unsigned char)ch == '\0')
		return ((char *)str);
	return (NULL);
}

int	ft_indexof(const char *str, int ch)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == (unsigned char)ch)
			return (i);
		str++;
		i++;
	}
	if ((unsigned char)ch == '\0')
		return (i);
	return (0);
}
