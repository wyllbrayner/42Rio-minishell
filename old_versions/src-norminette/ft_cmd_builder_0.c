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

// exit | echo -n "''cat |o|.c '|' cat > |o|.c e test de envio''"
// ls -la Makefile libminishell.a | exit

static void	ft_cmd_builder_aux_1(t_minishell *sh, char *cmd);
static void	ft_cmd_builder_aux_2(t_minishell *sh, long *var);
static void	ft_cmd_builder_aux_3(t_minishell *sh, long *var);

// 01234567
// ls > ser
//    printf("Dentro da cmd builder-> Início\n");
//    printf("line->: %s\n", sh->line);
//  var[0] = 0;         //    i = 0;
//  var[1] = 0;         //    start = 0;
//  var[2] = 0;         //    dquote = 0;
//  var[3] = 0;         //    squote = 0;
//		var[4] = (var[0] - var[1]);   // len = (i - start);
//    printf("Dentro da cmd builder -> Fim (ret: sh->ret: %i)\n", sh->ret);

void	ft_cmd_builder(t_minishell *sh)
{
	long	var[5];

	ft_cmd_builder_init_var(sh->caract, "|><", var);
	while (sh->line[var[0]])
	{
		ft_cmd_builder_aux_2(sh, var);
		if (sh->ret < 0)
			return ;
		ft_cmd_builder_aux_3(sh, var);
		if (sh->ret < 0)
			return ;
		var[1] = var[0];
		while (sh->line[var[0]] && (ft_strchr("><", sh->line[var[0]])))
			var[0]++;
	}
	ft_bzero(sh->caract, (sizeof(char) * 4));
}

//  | | ls NOK
// printf("Dentro da init cmd aux_1 -> Início: cmd: #%s#\n", cmd);
// printf("Dentro da init cmd aux_1 -> Início: trim(cmd): #%s#\n", sh->tmp0);
// ft_print_list(sh->head);
// printf("Dentro da init cmd aux_1 -> Fim\n");
static void	ft_cmd_builder_aux_1(t_minishell *sh, char *cmd)
{
	if (!cmd)
	{
		sh->ret = -3;
		sh->errnbr = errno;
		return ;
	}
	sh->tmp0 = ft_strtrim(cmd, " ");
	ft_free_minishell_single_aux(cmd);
	cmd = NULL;
	if (sh->tmp0 && *sh->tmp0)
	{
		ft_list_add_last(&sh->head, ft_node_create(sh->tmp0));
		ft_free_minishell_single_aux(sh->tmp0);
		sh->tmp0 = NULL;
	}
	else if (!sh->tmp0 || !*sh->tmp0)
	{
		ft_free_minishell_single_aux(sh->tmp0);
		sh->tmp0 = NULL;
	}
}

static void	ft_cmd_builder_aux_2(t_minishell *sh, long *var)
{
	ft_cmd_builder_aux_0(sh, &var[0], &var[3], &var[2]);
	var[4] = (var[0] - var[1]);
	if (var[4])
	{
		ft_cmd_builder_aux_1(sh, ft_substr(sh->line, var[1], var[4]));
		if (sh->ret < 0)
			return ;
	}
	if (sh->line[var[0]] == '|')
	{
		ft_cmd_builder_aux_1(sh, ft_strdup("|"));
		if (sh->ret < 0)
			return ;
		var[0]++;
	}
	else if (ft_strncmp(&sh->line[var[0]], "<<", 2) == 0)
	{
		ft_cmd_builder_aux_1(sh, ft_strdup("<<"));
		if (sh->ret < 0)
			return ;
		var[0] = var[0] + 2;
	}
}

static void	ft_cmd_builder_aux_3(t_minishell *sh, long *var)
{
	if (ft_strncmp(&sh->line[var[0]], "<", 1) == 0)
	{
		ft_cmd_builder_aux_1(sh, ft_strdup("<"));
		if (sh->ret < 0)
			return ;
		var[0]++;
	}
	else if (ft_strncmp(&sh->line[var[0]], ">>", 2) == 0)
	{
		ft_cmd_builder_aux_1(sh, ft_strdup(">>"));
		if (sh->ret < 0)
			return ;
		var[0] = var[0] + 2;
	}
	else if (ft_strncmp(&sh->line[var[0]], ">", 1) == 0)
	{
		ft_cmd_builder_aux_1(sh, ft_strdup(">"));
		if (sh->ret < 0)
			return ;
		var[0]++;
	}
}
