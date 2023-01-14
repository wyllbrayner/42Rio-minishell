/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

size_t	count_commands(char *input)
{
	size_t	index;
	size_t	count;
	int		q;

	index = -1;
	count = 1;
	q = 0;
	while (input[++index])
	{
		if (input[index] == q)
			q = 0;
		if ((input[index] == '"' || input[index] == '\'') && q == 0)
			q = input[index];
		if (is_separator(input, index) && q == 0)
			count++;
	}
	return (count);
}

static int	strchr_sep(char *s, int m)
{
	size_t	i;
	int		q;

	if (!s)
		return (-1);
	i = -1;
	q = 0;
	while (s[++i])
	{
		if (s[i] == q)
			q = 0;
		else if ((s[i] == '"' || s[i] == '\'') && q == 0)
			q = s[i];
		if ((s[i] == '|' || s[i] == '&' || s[i] == ';') && q == 0)
		{
			if (m && s[i + 1] && (s[i + 1] == '|' || s[i + 1] == '&'))
				return (i + 1);
			return (i);
		}
	}
	return (i);
}

char	**parse_raw_commands(char *raw)
{
	char	**cmds;
	size_t	i;
	size_t	j;
	size_t	cmds_c;

	cmds_c = count_commands(raw);
	cmds = malloc(sizeof(char *) * (cmds_c + 1));
	if (!cmds)
		return (NULL);
	i = -1;
	j = 0;
	while (raw[++i] && j < cmds_c)
	{
		cmds[j] = ft_substr(raw, i, strchr_sep(&raw[i], 0));
		j ++;
		i += strchr_sep(&raw[i], 1) - 1;
		if (raw[i + 1] && (raw[i + 1] == '|' || raw[i + 1] == '&'))
			i++;
		if (!raw[i])
			break ;
	}
	cmds[j] = NULL;
	return (cmds);
}
