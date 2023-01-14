/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_duplicated(t_token *tokens)
{
	size_t	index;

	index = -1;
	while (tokens[++index])
	{
		if (tokens[index] != LITERAL && tokens[index + 1] != LITERAL)
			return (FALSE);
	}
	return (TRUE);
}

static int	is_redir_in_quotes(int *q, char *s)
{
	size_t	i;
	int		quote;

	i = -1;
	quote = 0;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			*q = s[i];
			quote ++;
			continue ;
		}
		if (s[i] == *q)
		{
			*q = 0;
			quote ++;
		}
	}
	if (quote % 2 == 0 || quote == 0)
	{
		*q = 0;
		return (0);
	}
	return (-1);
}

static int	args_check(char *input)
{
	char	**args;
	size_t	index;
	int		q;

	args = ft_split(input, ' ');
	if (!args)
		return (FALSE);
	index = -1;
	q = 0;
	while (args[++index])
	{
		if (args[index + 1]
			&& (get_real_token(args[index]) != LITERAL
				&& get_real_token(args[index + 1]) != LITERAL)
			&& is_redir_in_quotes(&q, args[index]))
		{
			free_array(args);
			return (FALSE);
		}
	}
	free_array(args);
	return (TRUE);
}

int	check_redirections(t_token *tokens)
{
	size_t	index;

	index = -1;
	while (tokens[++index])
	{
		if (tokens[index] == REDIRECTION
			&& tokens[index + 2]
			&& tokens[index + 2] != LITERAL)
			return (FALSE);
	}
	return (TRUE);
}

int	syntaxer(char *input, t_token *tokens)
{
	int	result;

	result = TRUE;
	if ((tokens[0] != LITERAL && tokens[0] != REDIRECTION)
		|| tokens[tokens_length(tokens) - 1] != LITERAL
		|| !check_duplicated(tokens)
		|| !args_check(input)
		|| !check_redirections(tokens))
		result = FALSE;
	free(tokens);
	if (!result)
		errno = ENOTSUP;
	return (result);
}
