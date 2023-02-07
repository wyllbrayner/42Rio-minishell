/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_ocurrence.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:49:55 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/07 17:58:06 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

int	ft_first_ocurrence(char *str, int ch)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)ch)
			return (i);
		i++;
	}
	if ((char)ch == '\0')
		return (i - 1);
	return (-1);
}
