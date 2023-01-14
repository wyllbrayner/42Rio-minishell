/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/17 15:57:11 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static size_t	get_args_count(char **str)
{
	size_t	i;
	size_t	len;
	size_t	j;
	int		quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i])
	{
		j = -1;
		while (str[i][++j])
			is_in_quotes(&quote, str[i][j]);
		if (quote == 0)
			len++;
		i ++;
	}
	return (len);
}

int	get_quote_in_here(char *s)
{
	size_t	i;

	i = -1;
	if (!s)
		return (-1);
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
			return (i);
	}
	return (-1);
}

int	choose_quote(char *s)
{
	size_t	i;
	int		dq;
	int		q;

	i = -1;
	dq = 0;
	q = 0;
	while (s[++i])
	{
		if (s[i] == '\'')
			q ++;
		else if (s[i] == '"')
			dq ++;
	}
	if (q < dq)
		return (0);
	return (1);
}

int	is_quote_in_here(char *s)
{
	int		same_quote;
	int		quote;
	size_t	i;

	i = -1;
	quote = 0;
	if (!s)
		return (-1);
	while (s[++i])
	{
		if ((s[i] == '"' || s[i] == '\'') && quote % 2 == 0)
		{
			quote ++;
			same_quote = s[i];
			i ++;
		}
		if (s[i] == same_quote)
			quote ++;
	}
	if (quote % 2 == 0 || quote == 0)
		return (0);
	return (-1);
}

char	**parse_quotes(char *raw)
{
	char	**args;
	char	**split;

	split = ft_split(raw, ' ');
	args = malloc(sizeof(char *) * (get_args_count(split) + 1));
	if (!args)
	{
		free_array(split);
		return (NULL);
	}
	fill(args, split);
	free_array(split);
	return (args);
}
