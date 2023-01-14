/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	is_in_quotes(int *quote, char c)
{
	if (c == '"' && *quote != 2)
	{
		if (*quote == 1)
			*quote = 0;
		else
			*quote = 1;
	}
	else if (c == '\'' && *quote != 1)
	{
		if (*quote == 2)
			*quote = 0;
		else
			*quote = 2;
	}
}

static t_token	*tokenize(char *input)
{
	t_token	*tokens;
	size_t	i;
	size_t	j;
	int		quote;

	quote = 0;
	tokens = malloc(sizeof(int) * (ft_strlen(input) + 1));
	if (!tokens)
		return (NULL);
	i = -1;
	j = -1;
	while (input[++i])
	{
		is_in_quotes(&quote, input[i]);
		tokens[++j] = get_token(input, i);
		if (quote != 0)
			tokens[j] = LITERAL;
		if (tokens[j] == OR || tokens[j] == AND
			|| (input[i] == 60 && input[i + 1] == 60)
			|| (input[i] == 62 && input[i + 1] == 62))
			i++;
	}
	tokens[j + 1] = 0;
	return (tokens);
}

t_token	*lexer(t_app *app, char *input, int *result)
{
	t_token	*tokens;

	if (!input || !app)
	{
		*result = -2;
		return (NULL);
	}
	if (ft_strlen(input) == 0)
	{
		*result = -1;
		return (NULL);
	}
	tokens = tokenize(input);
	return (tokens);
}
