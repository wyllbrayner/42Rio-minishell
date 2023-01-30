/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
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
