/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*undest;
	unsigned char	*unsrc;

	undest = (unsigned char *)dest;
	unsrc = (unsigned char *)src;
	if (unsrc < undest)
	{
		while (len > 0)
		{
			ft_memcpy(undest + (len - 1), unsrc + (len - 1), 1);
			len--;
		}
	}
	else
		ft_memcpy(undest, unsrc, len);
	return (dest);
}
