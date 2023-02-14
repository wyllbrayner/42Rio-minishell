/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:06:38 by woliveir          #+#    #+#             */
/*   Updated: 2023/01/24 16:06:38 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

static void	ft_valid_quotes(t_minishell *sh, t_node *node, int *status, int c);
static void	ft_single_and_double_quotes_aux(t_minishell *sh, t_node *node, char *first, int *status, int c);

void	ft_single_and_double_quotes(t_minishell *sh, t_node *node, char *first, int *status)
{
	printf("Dentro da single_and_double_quotes | Início %s\n", first);
//	printf("token: %s | cmd[0]: %s | cmd[1]: %s | cmd[2]: %s!!!!\n", node->token, node->cmd[0], node->cmd[1], node->cmd[2]);
	ft_single_and_double_quotes_aux(sh, node, first, status, '\"');
	if (sh->ret < 0)
		return;
	ft_single_and_double_quotes_aux(sh, node, first, status, '\'');
	if (sh->ret < 0)
		return;

//	printf("Dentro da single_and_double_quotes | Após cd_aux_2 tmp1: %s\n", sh->tmp1);
	printf("Dentro da single_and_double_quotes | Fim\n");
}

void	ft_single_and_double_quotes_aux(t_minishell *sh, t_node *node, char *first, int *status, int c)
{
	printf("Dentro da single_and_double_quotes_aux | Início %s\n", first);
	ft_valid_quotes(sh, node, status, c);
	if (sh->ret < 0 || !sh->tmp1)
		return ;
//	printf("Dentro da single_and_double_quotes | Após valid quotes para %c tmp1: %s\n", c, sh->tmp1);
	sh->tmp2 = ft_strjoin(first, sh->tmp1);
	ft_free_minishell_single_aux(sh->tmp1);
	sh->tmp1 = NULL;
	if (!sh->tmp2)
		return ;		
	sh->tmp1 = sh->tmp2;
	sh->tmp2 = NULL;
	ft_builtin_cd_aux_2(sh, node);
	if (sh->ret < 0)
		return ;
	printf("Dentro da single_and_double_quotes_aux | fim %s\n", first);
}

static void	ft_valid_quotes(t_minishell *sh, t_node *node, int *status, int c)
{
	printf("Dentro da quotes | Início\n");
	long	i;
	long	start;
	long	end;
	long	first;
	long	count;

	i = 0;
	start = 0;
	end = 0;
	first = TRUE;
	count = 0;

//	printf("Dentro da quotes | Início - status: %s | c: %c\n", node->cmd[1], c);
	while (node->cmd[1][i])
	{
		while (node->cmd[1][i] && (node->cmd[1][i] == c))
		{
			i++;
			count++;
		}
//		printf("Dentro da quotes | count: %ld\n", count);
		if (status && c == '\'')
		{
//			printf("Dentro da quotes | dentro do if status | count: %ld | Início - status: %i\n", count, *status);
			if (count % 2)
			{
				*status = FALSE;
//				printf("Dentro da quotes | dentro do if count: %ld | Início - status: %i\n", count, *status);
			}
			count = 0;
		}
		if (c == '\"')
			count = 0;
		start = i;
		while (node->cmd[1][i] && (node->cmd[1][i] != c))
			i++;
		end = i;
		if (end != start)
		{
			if (first)
			{
				sh->tmp1 = ft_substr(node->cmd[1], start, (end - start));
				if (!sh->tmp1)
				{
					sh->ret = -3;
					return ;
				}
				first = FALSE;
			}
			else
			{
				sh->tmp2 = ft_substr(node->cmd[1], start, (end - start));
				if (!sh->tmp2)
				{
					ft_free_minishell_single_aux(sh->tmp1);
					sh->tmp1 = NULL;
					sh->ret = -3;
					return ;
				}
				sh->tmp5 = ft_strjoin(sh->tmp1, sh->tmp2);
				ft_free_minishell_single_aux(sh->tmp1);
				sh->tmp1 = NULL;
				ft_free_minishell_single_aux(sh->tmp2);
				sh->tmp2 = NULL;
				if (!sh->tmp5)
				{
					sh->ret = -3;
					return ;
				}
				sh->tmp1 = sh->tmp5;
				sh->tmp5 = NULL;
			}
		}
		else
		{
			if (first)
				sh->tmp1 = ft_strdup(".");
		}
	}
	printf("Dentro da quotes | Fim\n");
}

// cd '"'''$HOME''"''
// cd '"'''$HOME''"''
// cd ''"''$HOME''"''
// cd '"''$HOME''"'
// cd '''$HOME'''
// cd ''$HOME''
// cd '$HOME'
// cd $HOME

// cd '"'''$HOME''"'' | cd '"'''$HOME''"'' | cd ''"''$HOME''"'' | cd '"''$HOME''"' | cd '''$HOME''' | cd ''$HOME'' | cd '$HOME' | cd $HOME
