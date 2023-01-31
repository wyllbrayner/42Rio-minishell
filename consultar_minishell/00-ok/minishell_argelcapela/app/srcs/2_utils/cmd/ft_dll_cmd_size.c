/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dll_cmd_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 06:44:31 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/18 17:18:29 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_dll_cmd_size(t_dll *stack)
{
	int	i;

	i = 1;
	if (stack == NULL)
		return (0);
	while (stack->next != NULL)
	{
		stack = stack->next;
		i++;
	}
	return (i);
}
