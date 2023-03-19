/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

//    printf("Dentro da init var -> Início\n");
//    printf("Dentro da init var -> Fim\n");
void	ft_cmd_builder_init_var(char *caract, char *str, long *var)
{
	ft_bzero(caract, (sizeof(char) * 4));
	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	var[3] = 0;
	ft_strlcpy(caract, str, (ft_strlen(str) + 1));
}

// 01 ls
// || ls OK
// 012 ls
// | | ls NOK
// ls < do_ls_< | cat < doc_cat_< | ls >> doc_ls_>> | ls > doc_ls_>
// printf("Dentro da init cmd aux_0 -> Início (i: %li, sq: %li, dq: %ld, 
//caract: %s)\n", *i, *squote, *dquote, sh->caract);
// printf("Dentro da init cmd aux_0 -> Fim (i: %li, sq: %li, dq: %ld, 
//caract: %s)\n", *i, *squote, *dquote, sh->caract);
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
