/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t len)
{
	size_t	size_src;

	size_src = ft_strlen(src);
	if (len == 0)
		return (size_src);
	if ((size_src + 1) < len)
		ft_memcpy(dest, src, (size_src + 1));
	else
	{
		ft_memcpy(dest, src, (len - 1));
		dest[len - 1] = '\0';
	}
	return (size_src);
}
