/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	which_token(char *input, size_t i)
{
	char	c;
	char	n;

	c = input[i];
	n = input[i + 1];
	if (c == '&' && (!n || n != '&'))
		return (0);
	if (c == '&' && (input[i + 2] || input[i + 2] != '&'))
		return (1);
	if (c == '|' && (!n || n != '|'))
		return (2);
	if (c == '|' && (input[i + 2] || input[i + 2] != '|'))
		return (3);
	if ((c == '>' && (!n || n != '<'))
		|| (c == '<' && (!n || n != '>'))
		|| (c == '>' && (input[i + 2] || input[i + 2] != '>'))
		|| (c == '<' && (input[i + 2] || input[i + 2] != '<')))
		return (4);
	return (-1);
}

t_token	get_token(char *input, size_t i)
{
	if (input[i] == ';')
		return (SEMI_COLON);
	else if (which_token(input, i) == 0)
		return (AMPERSAND);
	else if (which_token(input, i) == 1)
		return (AND);
	else if (which_token(input, i) == 2)
		return (PIPE);
	else if (which_token(input, i) == 3)
		return (OR);
	else if (which_token(input, i) == 4)
		return (REDIRECTION);
	return (LITERAL);
}
