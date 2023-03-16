/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(long int nbr);
static void		ft_itoa_s(char *n_str, long int n_l, size_t l_it, int sg);

char	*ft_itoa(int n)
{
	long int	n_long;
	int			signal;
	size_t		len_int;
	char		*n_str;

	n_long = (long int)n;
	signal = 1;
	if (n_long < 0)
	{
		n_long *= -1;
		signal = -1;
	}
	len_int = ft_intlen(n_long);
	if (signal < 0)
		len_int++;
	n_str = (char *)malloc(sizeof(*n_str) * (len_int + 1));
	if (!(n_str))
		return (NULL);
	ft_itoa_s(n_str, n_long, len_int, signal);
	return (n_str);
}

static size_t	ft_intlen(long int nbr)
{
	size_t	size;

	size = 0;
	if (nbr == 0)
		size++;
	else
	{
		while (nbr != 0)
		{
			nbr /= 10;
			size++;
		}
	}
	return (size);
}

static void	ft_itoa_s(char *n_str, long int n_l, size_t l_it, int sg)
{
	n_str[l_it] = '\0';
	if (n_l == 0)
		n_str[--l_it] = '0';
	else
	{
		while (n_l != 0)
		{
			n_str[--l_it] = ((n_l % 10) + '0');
			n_l /= 10;
		}
		if (sg < 0)
			n_str[--l_it] = '-';
	}
}
