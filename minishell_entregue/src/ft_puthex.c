/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puthex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/07/09 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libftprintf.h"

static char	*ft_nbr_to_str(unsigned long n, char *base, size_t t_base);
static int	ft_nbrlen(unsigned long n, size_t t_base);

int	ft_puthex(unsigned int nbr, char *base, size_t t_base)
{
	char	*str;
	int		len;

	str = ft_nbr_to_str((unsigned long)nbr, base, t_base);
	len = ft_putstr(str);
	free(str);
	return (len);
}

int	ft_putpointer(void *nbr, char *base, size_t t_base)
{
	int				len;
	char			*str;

	str = ft_nbr_to_str((unsigned long)nbr, base, t_base);
	len = ft_putstr(str);
	free(str);
	return (len);
}

static int	ft_nbrlen(unsigned long n, size_t t_base)
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

static char	*ft_nbr_to_str(unsigned long n, char *base, size_t t_base)
{
	int		size;
	char	*hex;

	size = ft_nbrlen(n, t_base);
	hex = (char *)malloc(sizeof(char) * (size + 1));
	if (!hex)
		return (NULL);
	hex[size] = '\0';
	while (size != 0)
	{
		hex[(size--) - 1] = base[n % 16];
		n /= 16;
	}
	return (hex);
}
