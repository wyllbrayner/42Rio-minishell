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

//    printf("Dentro da ft_interpreter - Início erronbr: %i\n", sh->errnbr);
//    printf("Dentro da ft_interpreter - Fim\n");
void		ft_expander_variable(t_minishell *sh, t_node *node);
static void	ft_expand_variable_cd(t_minishell *sh, t_node *node);

void	ft_interpreter(t_minishell *sh, t_node	*node)
{
	ft_expander_quote(sh, node);
	ft_expander_variable(sh, node);
}

//    printf("Dentro da ft_expander_variable - Início\n");
//    printf("token: #%s# e first_cmd: #%s#\n", node->token, node->first_cmd);
//        printf("Estender variável para cd: %s#\n", node->token);
//        printf("Estender variável para diferente de cd\n");
//    printf("Antes de 1° ft_expand_variable, node->token: %s\n", node->token);
//        printf("Após     ft_expand_variable, sh->tmp5     %s\n", sh->tmp5);
//    printf("Após  da 1º ft_expand_variable, node->token: %s\n", node->token);
//    printf("Dentro da ft_expander_variable - Fim\n");
void	ft_expander_variable(t_minishell *sh, t_node *node)
{
	sh->ret = 0;
	if (ft_strncmp(node->first_cmd, "cd", 2) == 0)
		ft_expand_variable_cd(sh, node);
	ft_expand_variable(sh, node);
	if (sh->tmp5)
	{
		sh->tmp1 = sh->tmp5;
		sh->tmp5 = NULL;
		ft_builtin_cd_aux_2(sh, node);
	}
}

static void	ft_expand_variable_cd(t_minishell *sh, t_node *node)
{
	long	i;

	i = 0;
	while (node->cmd[i])
		i++;
	if (i == 1)
	{
		sh->tmp1 = ft_strdup("cd $HOME");
		if (!sh->tmp1)
		{
			sh->errnbr = errno;
			sh->ret = -3;
			return ;
		}
		ft_builtin_cd_aux_2(sh, node);
		if (sh->ret < 0)
			return ;
	}
}
