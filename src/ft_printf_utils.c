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

#include "../header/ft_minishell.h"

int	ft_putchar(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	if (!str)
	{
		ft_putstr_fd(STRNULL, 1);
		return ((int)ft_strlen(STRNULL));
	}
	ft_putstr_fd(str, 1);
	return ((int)ft_strlen(str));
}

int	ft_putnbr(int nbr)
{
	char	*str;
	int		len;

	str = ft_itoa(nbr);
	len = ft_putstr(str);
	if (str)
		free(str);
	return (len);
}

int	ft_nbrlen(unsigned long n, size_t t_base)
{
	int	i;

	if (t_base == 0)
		return (0);
	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= t_base;
		i++;
	}
	return (i);
}

char	*ft_nbr_to_str(unsigned long n, char *base, size_t t_base)
{
	int		size;
	char	*hex;

	size = ft_nbrlen(n, t_base);
	hex = (char *)ft_calloc(sizeof(char), (size + 1));
	if (!hex)
		return (NULL);
	if (n == 0)
		hex[0] = '0';
	while (size != 0)
	{
		hex[--size] = base[n % t_base];
		n /= t_base;
	}
	return (hex);
}
