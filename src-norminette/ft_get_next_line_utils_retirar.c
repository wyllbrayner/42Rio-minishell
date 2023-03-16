/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:07:29 by woliveir          #+#    #+#             */
/*   Updated: 2022/07/20 23:28:33 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/get_next_line.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy_gnl(void *dest, const void *src, size_t len)
{
	unsigned char		*destcast;
	unsigned char		*srccast;
	size_t				i;

	if ((dest == NULL) && (src == NULL) && (len > 0))
		return (NULL);
	destcast = (unsigned char *)dest;
	srccast = (unsigned char *)src;
	i = 0;
	while (i < len)
	{
		destcast[i] = srccast[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlcpy_gnl(char *dest, const char *src, size_t len)
{
	size_t	size_src;

	size_src = ft_strlen_gnl(src);
	if (len == 0)
		return (size_src);
	if ((size_src + 1) < len)
		ft_memcpy_gnl(dest, src, (size_src + 1));
	else
	{
		ft_memcpy_gnl(dest, src, (len - 1));
		dest[len - 1] = '\0';
	}
	return (size_src);
}

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	char	*joins;
	size_t	size_s1;
	size_t	size_s2;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	size_s1 = ft_strlen_gnl(s1);
	size_s2 = ft_strlen_gnl(s2);
	joins = (char *)malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	if (!(joins))
		return (NULL);
	ft_strlcpy_gnl(joins, s1, (size_s1 + 1));
	ft_strlcpy_gnl((joins + size_s1), s2, (size_s2 + 1));
	free(s1);
	return (joins);
}

char	*ft_strchr_gnl(const char *str, int c)
{
	if (!str)
		return (0);
	while (*str != (unsigned char)c)
	{
		if (!(*str))
			return (0);
		str++;
	}
	return ((char *)str);
}
