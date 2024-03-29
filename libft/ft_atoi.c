/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	signal;
	int	nbr;

	signal = 1;
	while (ft_isspace(*str) == 1)
		str++;
	if ((*str == '+') || (*str == '-'))
	{
		if (*str == '-')
			signal = -1;
		str++;
	}
	nbr = 0;
	while (ft_isdigit(*str))
	{
		nbr = (10 * nbr) + (*str - '0');
		str++;
	}
	return (nbr * signal);
}
