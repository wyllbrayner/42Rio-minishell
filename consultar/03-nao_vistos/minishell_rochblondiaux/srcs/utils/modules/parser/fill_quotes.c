/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	nb_quotes(char *s, int quote)
{
	int		i;
	size_t	j;

	i = 0;
	j = -1;
	while (s[++j])
	{
		if (s[j] == quote)
			i ++;
	}
	return (i);
}

static char	*get_unquoted(char *arg, int quote)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	dest = malloc(sizeof(char) * (ft_strlen(arg)
				- nb_quotes(arg, quote) + 1));
	while (arg[++i])
	{
		if (arg[i] != quote)
			dest[++j] = arg[i];
	}
	dest[++j] = '\0';
	dest = ft_strtrim(dest, " ");
	return (dest);
}

static char	*fill_quotes(char **raw, char *args, size_t *i, int quote)
{
	quote = raw[*i][get_quote_in_here(raw[*i])];
	while (quote != 0 && raw[*i] && raw[*i + 1])
	{
		if (!args)
			args = ft_strjoin(raw[*i], " ");
		else
			args = ft_strjoin_properly(args,
					ft_strjoin(raw[*i], " "));
		if (get_quote_in_here(raw[*i + 1]) != -1)
		{
			args = ft_strjoin_properly(args,
					ft_strjoin(raw[*i + 1], " "));
			args = sup_quote(args);
			quote = 0;
		}
		*i += 1;
	}
	return (args);
}

char	*sup_quote(char *arg)
{
	char	*dest;
	int		quote;
	size_t	i;

	quote = -1;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '"' || arg[i] == '\'')
		{
			quote = arg[i];
			break ;
		}
	}
	if (quote == -1)
		return (arg);
	else
		dest = get_unquoted(arg, quote);
	free(arg);
	return (dest);
}

void	fill(char **args, char **raw)
{
	size_t	i;
	size_t	j;
	int		quote;

	i = -1;
	j = -1;
	quote = 0;
	while (raw[++i])
	{
		if (quote == 0 && is_quote_in_here(raw[i]) == 0)
			args[++j] = sup_quote(ft_strdup(raw[i]));
		else
		{
			j ++;
			args[j] = fill_quotes(raw, args[j], &i, quote);
		}
	}
	args[++j] = NULL;
}
