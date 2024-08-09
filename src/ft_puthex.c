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

#include "../header/ft_minishell.h"

int	ft_puthex(unsigned int nbr, char *base, size_t t_base)
{
	char	*str;
	int		len;

	str = ft_nbr_to_str((unsigned long)nbr, base, t_base);
	len = ft_putstr(str);
	if (str)
		free(str);
	return (len);
}

int	ft_putpointer(void *nbr, char *base, size_t t_base)
{
	char	*str;
	int		len;

	str = ft_nbr_to_str((unsigned long)nbr, base, t_base);
	len = ft_putstr(str);
	if (str)
		free(str);
	return (len);
}
