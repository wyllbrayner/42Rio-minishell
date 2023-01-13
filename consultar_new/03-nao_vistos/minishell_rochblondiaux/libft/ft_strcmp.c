/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:23:01 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:16 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_sensitive(const char *a, const char *b)
{
	int	i;

	if (!a || !b || ft_strlen(a) != ft_strlen(b))
		return (0);
	i = -1;
	while (a[++i])
	{
		if (a[i] != b[i])
			return (0);
	}
	return (1);
}

int	ft_strcmp(const char *a, const char *b)
{
	int	i;

	if (!a || !b || ft_strlen(a) != ft_strlen(b))
		return (0);
	i = -1;
	while (a[++i])
	{
		if (ft_tolower(a[i]) != ft_tolower(b[i]))
			return (0);
	}
	return (1);
}
