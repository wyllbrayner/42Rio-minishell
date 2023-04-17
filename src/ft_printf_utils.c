/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/07/09 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libftprintf.h"

int	ft_putchar(char c)
{
	ft_putchar_fd(c, 2);
	return (1);
}

int	ft_putstr(char *str)
{
	if (!str)
	{
		ft_putstr_fd("(null)", 2);
		return ((int)ft_strlen("(null)"));
	}
	ft_putstr_fd(str, 2);
	return ((int)ft_strlen(str));
}

int	ft_putnbr(int nbr)
{
	char	*str;
	int		len;

	str = ft_itoa(nbr);
	len = ft_putstr(str);
	free(str);
	return (len);
}
