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

t_token	get_real_token(char *a)
{
	if (ft_strcmp_sensitive(a, "&"))
		return (AMPERSAND);
	if (ft_strcmp_sensitive(a, "&&"))
		return (AND);
	if (ft_strcmp_sensitive(a, "|"))
		return (PIPE);
	if (ft_strcmp_sensitive(a, "||"))
		return (OR);
	if (ft_strcmp_sensitive(a, ";"))
		return (SEMI_COLON);
	if (ft_strcmp_sensitive(a, ">")
		|| ft_strcmp_sensitive(a, "<")
		|| ft_strcmp_sensitive(a, ">>")
		|| ft_strcmp_sensitive(a, "<<"))
		return (REDIRECTION);
	return (LITERAL);
}

size_t	tokens_length(t_token *tokens)
{
	size_t	index;

	index = 0;
	while (tokens[index])
		index++;
	return (index);
}
