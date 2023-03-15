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


/*
    printf("tmp0: %s#\n", sh->tmp0);
    printf("tmp1: %s#\n", sh->tmp1);
    printf("tmp2: %s#\n", sh->tmp2);
    printf("tmp5: %s#\n", sh->tmp5);
    printf("Dentro da ft_expand_variable_0 - Início errnbr: %i\n", sh->errnbr);
*/
//        printf("Dentro do if   tmp0: %s#\n", sh->tmp0);
//            printf("Dentro do else   tmp0: %s#\n", sh->tmp0);
//            printf("Dentro do else, join de tmp5: %s# e tmp0: %s# em tmp1: %s#\n", sh->tmp5, sh->tmp0, sh->tmp1);
//        printf("Dentro do else, troca os ponteiros de tmp0: %s# e tmp1: %s#\n", sh->tmp0, sh->tmp1);
/*
    printf("Após os ifs\n");
    printf("tmp0: %s#\n", sh->tmp0);
    printf("tmp1: %s#\n", sh->tmp1);
    printf("tmp2: %s#\n", sh->tmp2);
    printf("tmp5: %s#\n", sh->tmp5);
*/
//    printf("Após colocar o histórico tmp0 v[0] recebe v[5] -> v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
//    printf("Andou até o próximo '$~/\' (espaço)'        -> v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
//            printf("é ~\n");
//            printf("é ~\n");
//    printf("malloca len: %ld posições a partir de: var[0]: %ld até var[5]: %ld -> tmp5: %s\n", (var[5] - var[0]), var[0], var[5], sh->tmp5);
//        printf("sh->tmp5 não conseguiu mallocar\n");
//    printf("join de tmp5: %s com = em tmp1: %s\n", sh->tmp5, sh->tmp1);
//        printf("sh->tmp1 não conseguiu mallocar\n");
//    printf("Antes de ft_unset_aux_1                        -> v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
//	ft_unset_aux_1(sh, &var[2], var[0], var[1], &var[3]);
//    printf("Após     ft_unset_aux_1                        -> v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
//        printf("ft_unset_aux_1 retornou true e tmp2: %s\n", sh->tmp2);
//            printf("ft_unset_aux_1 retornou false, mas tmp1 = $?=: %s\n", sh->tmp2);
//            printf("ft_unset_aux_1 retornou false, mas tmp5 = $?=: %s\n", sh->tmp5);
//            printf("ft_unset_aux_1 retornou false, malloca espaço: #%s#\n", sh->tmp2);
/*
    printf("Dentro da ft_expand_variable_0 - Fim\n");
    printf("tmp0: %s#\n", sh->tmp0);
    printf("tmp1: %s#\n", sh->tmp1);
    printf("tmp2: %s#\n", sh->tmp2);
    printf("tmp5: %s#\n", sh->tmp5);
*/

void	ft_expand_variable_0_aux_00(t_minishell *sh, t_node *node, long *var)
{
	sh->tmp0  = ft_substr(node->token, var[0], (var[5] - var[0]));
	if (!sh->tmp0)
	{
		ft_free_minishell_single_aux(sh->tmp5);
		sh->tmp5 = NULL;
		sh->ret = -3;
		sh->errnbr = errno;
		return ;
	}
	sh->tmp1 = ft_strjoin(sh->tmp5, sh->tmp0);
	ft_free_minishell_single_aux(sh->tmp0);
	sh->tmp0 = NULL;
	ft_free_minishell_single_aux(sh->tmp5);
	sh->tmp5 = NULL;
	if (!sh->tmp1)
	{
		sh->errnbr = errno;
		sh->ret = -3;
		return ;
	}
	sh->tmp0 = sh->tmp1;
	sh->tmp1 = NULL;
}

void	ft_expand_variable_0_aux_01(t_minishell *sh, t_node *node, long *var)
{
	if (!sh->tmp5)
	{
		sh->tmp0 = ft_substr(node->token, var[0], var[5]);
		if (!sh->tmp0)
		{
			sh->errnbr = errno;
			sh->ret = -3;
			return ;
		}
	}
	else
	{
		if (node->token[var[0]] != '$')
		{
			ft_expand_variable_0_aux_00(sh, node, var);
			if (sh->ret < 0)
				return ;
		}
		else
		{
			sh->tmp0 = sh->tmp5;
			sh->tmp5 = NULL;
			var[5] = var[0];
		}
	}
}

void	ft_expand_variable_0_aux_02(t_minishell *sh, t_node *node, long *var)
{
	if (node->token[var[5]])
	{
		if (node->token[var[5]] != '~')
			var[5]++;
	}
	var[0] = var[5];
	while (node->token[var[5]] && !(ft_strchr("/$~\'", node->token[var[5]])) \
		&& !ft_isspace(node->token[var[5]]))
	    var[5]++;
	if ((var[0] == var[5]) && (node->token[var[5]] == '~') && \
							(node->token[(var[5] - 1)] == ' '))
	{
		if (!node->token[(var[5] + 1)])
			sh->tmp5 = ft_strdup("HOME");
		else if (((node->token[(var[5] + 1)] == ' ') || \
				(node->token[(var[5] + 1)] == '/')))
			sh->tmp5 = ft_strdup("HOME");
	}
	else
		sh->tmp5 = ft_substr(node->token, var[0], (var[5] - var[0]));
}

void	ft_expand_variable_0_aux_03(t_minishell *sh)
{
	if (!sh->tmp5)
	{
		ft_free_minishell_single_aux(sh->tmp0);
		sh->tmp0 = NULL;
		sh->ret = -3;
		sh->errnbr = errno;
		return ;
	}
	sh->tmp1 = ft_strjoin(sh->tmp5, "=");
	ft_free_minishell_single_aux(sh->tmp5);
	sh->tmp5 = NULL;
	if (!sh->tmp1)
	{
		ft_free_minishell_single_aux(sh->tmp0);
		sh->tmp0 = NULL;
		sh->ret = -3;
		sh->errnbr = errno;
		return ;
	}
}

void	ft_expand_variable_0_aux_04(t_minishell *sh, long *var)
{
	var[1] = ft_strlen(sh->tmp1);
	var[0] = 0;
	var[3] = FALSE;
	ft_unset_aux_1(sh, var);
	if (var[3])
	{
		var[4] = ft_strchr_i(sh->env[var[2]], '=');
		sh->tmp5 = ft_substr(sh->env[var[2]], (var[4] + 1), \
		ft_strlen(sh->env[var[2]]) - var[4]);
	}
	else
	{
		if (ft_strncmp(sh->tmp1, "?=", 3) == 0)
			sh->tmp5 = ft_itoa(sh->errnbr);           
		else
			sh->tmp5 = ft_strdup("");
	}
	ft_free_minishell_single_aux(sh->tmp1);
	sh->tmp1 = NULL;
}

void	ft_expand_variable_0_aux_05(t_minishell *sh)
{
	if (!sh->tmp5)
	{
		ft_free_minishell_single_aux(sh->tmp0);
		sh->tmp0 = NULL;
		sh->ret = -3;
		sh->errnbr = errno;
		return ;
	}
	sh->tmp1 = ft_strjoin(sh->tmp0, sh->tmp5);
	ft_free_minishell_single_aux(sh->tmp0);
	sh->tmp0 = NULL;
	ft_free_minishell_single_aux(sh->tmp5);
	sh->tmp5 = NULL;
	if (!sh->tmp1)
	{
		sh->ret = -3;
		sh->errnbr = errno;
	}
	sh->tmp5 = sh->tmp1;
	sh->tmp1 = NULL;
}

void	ft_expand_variable_0(t_minishell *sh, t_node *node, long *var)
{
	ft_expand_variable_0_aux_01(sh, node, var);
	if (sh->ret < 0)
		return ;
	ft_expand_variable_0_aux_02(sh, node, var);
	ft_expand_variable_0_aux_03(sh);
	if (sh->ret < 0)
		return ;
	ft_expand_variable_0_aux_04(sh, var);
	ft_expand_variable_0_aux_05(sh);
	if (sh->ret < 0)
		return ;
}

//    printf("Dentro da ft_expand_variable - Início (token: %s)\n", node->token);
//            printf("Chama    a expand_variable_0 - v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
//            printf("Retorna da expand_variable_0 - v[0]: %ld; v[1]: %ld; v[2]: %ld; v[3]: %ld; v[4]: %ld; v[5]: %ld; v[6]: %ld\n", var[0], var[1], var[2], var[3], var[4], var[5], var[6]);
//    printf("Dentro da ft_expand_variable - Fim (token: %s)\n", node->token);

void	ft_expand_variable_1_aux_00(t_node *node, long *var)
{
	while (node->token[var[5]] && !(ft_strchr("$~", node->token[var[5]])))
	{
		if (node->token[var[5]] == '\'')
		{
			if (var[6])
				var[6] = 0;
			else
				var[6] = TRUE;
		}
		var[5]++;
	}
}

void	ft_expand_variable_1_aux_01(t_minishell *sh, t_node *node, long *var)
{
	if (node->token[var[5]] && var[6])
	{
		while (node->token[var[5]] && node->token[var[5]] != '\'')
			var[5]++;
		var[6] = FALSE;
	}
	else
	{
		ft_expand_variable_0(sh, node, var);
		if (sh->ret < 0)
			return ;
		var[0] = var[5];
		if (node->token[var[5]] == '\'')
		{
			if (var[6])
				var[6] = 0;
			else
				var[6] = TRUE;
		}
	}
}

void	ft_expand_variable_1_aux_02(t_node *node, long *var)
{
	if (node->token[var[5]])
	{
		if (node->token[var[5]] != '~')
			var[5]++;
		else
		{
			var[5]++;
			var[0] = var[5];
		}
	}
}


void	ft_expand_variable(t_minishell *sh, t_node *node)
{
	long	var[7] = {0};

	var[0] = 0;
	var[5] = 0;
	var[6] = FALSE;
	while (node->token[var[5]] && !ft_isspace(node->token[var[5]]))
		var[5]++;
	while (node->token[var[5]] && ft_isspace(node->token[var[5]]))
		var[5]++;
	while (node->token[var[5]])
	{
		ft_expand_variable_1_aux_00(node, var);
		ft_expand_variable_1_aux_01(sh, node, var);
		if (sh->ret < 0)
			return ;
		ft_expand_variable_1_aux_02(node, var);
	}
}

void	ft_expand_variable_cd(t_minishell *sh, t_node *node)
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

//    printf("Dentro da ft_interpreter - Início erronbr: %i\n", sh->errnbr);
//    printf("Dentro da ft_interpreter - Fim\n");
void	ft_interpreter(t_minishell *sh, t_node	*node)
{
	ft_expander_quote(sh, node);
	ft_expander_variable(sh, node);
}

/*
//  export      TEST='$HOME'$PATH $PROJ 
    long    start;  // var[0];
    long    end;    // var[1];
    long    i_env;  // var[2];
    long    status; // var[3];
    long    len;        // var[4];
    long    j;          // var[5];
    long    quote;      // var[6];
// echo eu: $USER em: $PATH ou: ~ , falo: $LANG
//  echo      TEST='$HOME'$PATH$PROJ 
//  echo      TEST='$HOME'$PROJ $PATH 
//  echo      TEST=$?$HOME'$PROJ' $PATH
//  echo      TEST='$HOME'$PATH' ' $USER
//  echo      TEST=$?$HOME'$PROJ' '$PATH'''
//  echo    $HOME~ TEST='$HOME'  $PATH' ' ~ $USER // loop infinito
//  ls $HOME~ ~/projetos   
// ls "$HOME" | exit | echo "sair daqui | agora"
// echo "'''''$HOME'''''" | e''xi''t | echo "'''sair daqui | agora'''" | ls "''''$HOME''''"/PROJETOS
// tmp0 = null
// tmp1 = null
// tmp2 = null
// tmp5 = ls /home/wyllbrayner /projetosNULL
//                    [0]
//                    [5]
//  00000000001111111111222222
//  01234567890123456789012345
//  ls $HOME~ /projetos 
*/
