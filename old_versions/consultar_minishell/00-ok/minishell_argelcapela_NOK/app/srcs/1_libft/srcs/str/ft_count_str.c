/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 01:23:51 by argel             #+#    #+#             */
/*   Updated: 2022/11/06 16:17:26 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_count_str(char *str, char *c)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (ft_strncmp(str + i, c, ft_strlen(c)) == 0)
		{
			i += ft_strlen(c);
			n++;
		}
		i++;
	}
	return (n);
}
