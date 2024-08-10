/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

size_t	ft_strchr_i(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] != (unsigned char)c)
	{
		if (!str[i])
			return (0);
		i++;
	}
	return (i);
}

int	ft_valid_quote(long squote, long dquote)
{
	if (!(squote % 2) && !(dquote % 2))
		return (1);
	else
		return (0);
}
