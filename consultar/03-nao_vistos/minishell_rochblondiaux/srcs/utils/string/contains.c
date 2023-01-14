/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_contains_delim(char *input)
{
	size_t	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '<' && input[i + 1] == '<'
			&& input[i + 2] && input[i + 2] != '<')
			return (TRUE);
	}
	return (FALSE);
}

size_t	ft_contains(char *s, char c)
{
	size_t	j;
	size_t	l;

	j = -1;
	l = 0;
	while (s[++j])
	{
		if (s[j] == c)
			l++;
	}
	return (l);
}
