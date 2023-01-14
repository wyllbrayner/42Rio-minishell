/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/17 15:57:18 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	should_ignore(char *i, size_t start, size_t end)
{
	int		q;
	size_t	index;

	q = 0;
	index = -1;
	if (index - start == 1)
		return (TRUE);
	while (i[++index] && index <= end)
	{
		is_in_quotes(&q, i[index]);
		if (index == start)
			return (q == 2);
	}
	return (FALSE);
}

static char	*get_remaining(char *i, int *i1)
{
	size_t	start;
	size_t	index;

	start = ft_strchr(&i[*i1], '$');
	if (start > 0)
		start += *i1;
	if (start == 0 || i[start + 1] == '?')
	{
		(*i1)++;
		return (NULL);
	}
	index = start;
	while (i[++index] && ft_isalnum(i[index]))
		;
	if (should_ignore(i, start, index))
	{
		(*i1) += ft_strchr(&i[start], '$') + 1;
		return (NULL);
	}
	(*i1) += (index - start);
	return (ft_substr(i, start, index - start));
}

static int	solo_env(t_app *app, char **input)
{
	size_t	i;
	size_t	j;

	j = -1;
	while (input[++j])
	{
		i = 0;
		if (input[j][i] != '$' || get_env(app, input[j]))
		{
			free_array(input);
			return (FALSE);
		}
		while (input[j][++i])
		{
			if (input[j][i] == ' ' || input[j][i] == '$')
			{
				free_array(input);
				return (FALSE);
			}
		}
	}
	free_array(input);
	return (TRUE);
}

static char	*add_quotes(char *value)
{
	char	*dest;
	size_t	i;
	size_t	j;
	int		q;

	i = -1;
	j = -1;
	dest = malloc(sizeof(char) * (ft_strlen(value) + 3));
	if (!dest)
		return (NULL);
	q = choose_quote(value);
	if (q == 1)
		dest[++i] = '"';
	else
		dest[++i] = '\'';
	while (value[++j])
		dest[++i] = value[j];
	dest[++i] = dest[0];
	dest[++i] = '\0';
	return (dest);
}

char	*expand_env_vars(t_app *app, char *input)
{
	char	*t;
	char	*key;
	char	*value;
	int		index;

	index = 0;
	if (solo_env(app, ft_split(input, ' ')) == TRUE)
		return (NULL);
	t = ft_strdup(input);
	key = get_remaining(t, &index);
	while (t[index])
	{
		if (key)
		{
			value = add_quotes(get_env(app, &key[1]));
			if (!value)
				value = "";
			reset_str(&t, replace_first(t, key, value));
			free(key);
		}
		key = get_remaining(t, &index);
	}
	free(key);
	return (t);
}
