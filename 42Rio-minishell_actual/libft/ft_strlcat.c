/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(const char *str, size_t maxlen);

size_t	ft_strlcat(char *dest, const char *src, size_t len)
{
	size_t	lim_dest;

	lim_dest = ft_strnlen(dest, len);
	if (lim_dest == len)
		return (lim_dest + ft_strlen(src));
	return (lim_dest + ft_strlcpy((dest + lim_dest), src, (len - lim_dest)));
}

static size_t	ft_strnlen(const char *str, size_t maxlen)
{
	size_t	len_str;

	len_str = ft_strlen(str);
	if (len_str > maxlen)
		return (maxlen);
	return (len_str);
}
