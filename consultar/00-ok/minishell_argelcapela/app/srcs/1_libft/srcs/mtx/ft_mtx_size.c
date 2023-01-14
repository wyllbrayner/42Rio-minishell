/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtx_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:37:17 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/01 01:31:31 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_mtx_size(void **matrix)
{
	int	size;

	size = 0;
	if (matrix == NULL)
		return (size);
	while (matrix[size])
		size++;
	return (size);
}
