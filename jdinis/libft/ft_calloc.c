/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t qtd, size_t len)
{
	void	*ptr;

	if ((qtd >= INT_MAX) || (len >= INT_MAX))
		return (NULL);
	if (qtd == 0)
		qtd = 1;
	if (len == 0)
		len = 1;
	ptr = malloc(qtd * len);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (qtd * len));
	return (ptr);
}
