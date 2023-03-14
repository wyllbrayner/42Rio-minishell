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

void		ft_variable_expansion_aux(t_minishell *sh, t_node *node);
static void	ft_variable_expansion_aux_1(t_minishell *sh, t_node *n, long *var);
static void	ft_variable_expansion_aux_2(t_minishell *sh, long *var, long *len);

//    printf("Dentro da expansão de variáveis - Início\n");
//            printf("Nó: %s     possui %c\n", tmp->cmd[0], '$');
//        else
//        {
//            printf("Nó: %s não possui %c\n", tmp->cmd[0], '$');
//        }
//    printf("Dentro da expansão de variáveis - Fim\n");

void	ft_variable_expansion(t_minishell *sh)
{
	t_node	*tmp;

	tmp = sh->head;
	while (tmp)
	{
		if (ft_strchr_i(tmp->cmd[0], '$') != 0)
			ft_variable_expansion_aux(sh, tmp);
		tmp = tmp->next;
	}
}

//    printf("Dentro da expansão de variáveis_aux - Início\n");
//        printf("sh->tmp2: %s\n", sh->tmp2);
// printf("var[3]: %ld | var[2](i): %ld | env: %s\n", var[3], 
//var[2], sh->env[var[2]]);
//                printf("Não Mallocou\n");
//                printf("Mallocou %ld posições\n", len);
//                printf("sh->tmp1 ( antes): %s#\n", sh->tmp1);
//                printf("sh->env[%ld]: %s | caract: %ld\n", var[2], 
//sh->env[var[2]], caract);
//                printf("sh->tmp1 (depois): %s\n", sh->tmp1);
//        else
//            printf("Faça alguma coisa\n");
//        printf("Dentro da expansão de variáveis_aux - Fim\n");

static void	ft_variable_expansion_aux_1(t_minishell *sh, t_node *n, long *var)
{
	var[1] = ft_strlen(n->token);
	sh->tmp1 = ft_substr(n->token, (var[0] + 1), (var[1] - var[0] - 1));
	sh->tmp2 = ft_strjoin(sh->tmp1, "=");
	ft_free_minishell_single_aux(sh->tmp1);
	sh->tmp1 = NULL;
	sh->tmp1 = sh->tmp2;
	sh->tmp2 = NULL;
	var[3] = FALSE;
	ft_unset_aux_1(sh, var);
	ft_free_minishell_single_aux(sh->tmp1);
	sh->tmp1 = NULL;
}

static void	ft_variable_expansion_aux_2(t_minishell *sh, long *var, long *len)
{
	*len = ((var[0] + \
	(ft_strlen(sh->env[var[2]]) - ft_strchr_i(sh->env[var[2]], '='))));
	sh->tmp1 = (char *)malloc(sizeof(char) * *len);
	if (!sh->tmp1)
	{
		sh->errnbr = errno;
		sh->ret = -3;
	}
}

void	ft_variable_expansion_aux(t_minishell *sh, t_node *node)
{
	long	var[4];
	long	len;
	long	caract;

	var[0] = ft_strchr_i(node->token, '$');
	if (var[0])
	{
		ft_variable_expansion_aux_1(sh, node, var);
		if (var[3])
		{
			ft_variable_expansion_aux_2(sh, var, &len);
			if (sh->ret < 0)
				return ;
			else
			{
				sh->tmp1[--len] = '\0';
				ft_strlcpy(sh->tmp1, node->token, (var[0] + 1));
				caract = ft_strchr_i(sh->env[var[2]], '=');
				ft_strlcpy(sh->tmp1 + (var[0]), \
	sh->env[var[2]] + (caract + 1), ft_strlen(sh->env[var[2]]) - caract);
			}
		}
	}
}
