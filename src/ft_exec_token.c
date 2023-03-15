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

static void	ft_exec_token_aux0(t_minishell *sh, t_node *head);
static void	ft_select_way(t_minishell *sh, t_node *node);

void	ft_exec_token(t_minishell *sh)
{
	t_node	*head;

	head = sh->head;
	while (head && (sh->ret == 0))
	{
		ft_exec_token_aux0(sh, head);
		head = head->next;
	}
}

static void	ft_exec_token_aux0(t_minishell *sh, t_node *head)
{
	if (head->first_cmd[0] != '|' && head->first_cmd[0] != '<' && \
		head->first_cmd[0] != '>')
	{
		ft_interpreter(sh, head);
		if (!head->prev)
		{
			ft_select_way(sh, head);
			if (sh->ret <= -4)
				ft_minishell_error(sh);
		}
		if (head->prev)
		{
			if (head->prev->first_cmd[0] != '<' && \
				head->prev->first_cmd[0] != '>')
			{
				ft_select_way(sh, head);
				if (sh->ret <= -4)
					ft_minishell_error(sh);
			}
		}
	}
}

//            printf("Chama a builtin echo\n");
//            printf("Chama a builtin cd\n");
//            printf("Chama a builtin pwd\n");
//            printf("Chamar a builtin export\n");
//            printf("Chamar a builtin unset\n");
//            printf("Chamar a builtin env\n");
//            printf("Chamar a builtin exit\n");
//            printf("Builtin NÃO IDENTIFICADA | procurar dentre as bin\n");
static void	ft_select_way(t_minishell *sh, t_node *node)
{
	int	rato;

	if (sh && node)
	{
		if (ft_strncmp(node->first_cmd, "echo", 5) == 0)
			ft_builtin_echo(sh, node);
		else if (ft_strncmp(node->first_cmd, "cd", 3) == 0)
			ft_builtin_cd(sh, node);
		else if (ft_strncmp(node->first_cmd, "pwd", 4) == 0)
			ft_builtin_pwd(sh);
		else if (ft_strncmp(node->first_cmd, "export", 7) == 0)
			ft_builtin_export(sh, node);
		else if (ft_strncmp(node->first_cmd, "unset", 6) == 0)
			ft_builtin_unset(sh, node);
		else if (ft_strncmp(node->first_cmd, "env", 4) == 0)
			ft_builtin_env(sh, node);
		else if (ft_strncmp(node->first_cmd, "exit", 5) == 0)
			ft_builtin_exit(sh, node);
		else
		{
			rato = 0;
			ft_start_command(sh, &rato, node);
			wait(NULL);
		}
	}
}
