/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_builder_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

void	ft_cmd_builder_init_var(char *caract, char *str, long *var)
{
	ft_bzero(caract, (sizeof(char) * 4));
	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	var[3] = 0;
	ft_strlcpy(caract, str, (ft_strlen(str) + 1));
}

void	ft_cmd_builder_aux_0(t_minishell *sh, long *i, long *squote,
			long *dquote)
{
	while (sh->line[*i] && (!((ft_strchr(sh->caract, sh->line[*i]) && \
			ft_valid_quote(*squote, *dquote)))))
	{
		if (sh->line[*i] == '\'')
			*squote = *squote + 1;
		else if (sh->line[*i] == '\"')
			*dquote = *dquote + 1;
		*i = *i + 1;
	}
}
