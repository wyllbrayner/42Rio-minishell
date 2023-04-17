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

extern t_signal	g_sig;

static void	ft_valid_empty_cmd(t_minishell *sh);
static void	ft_valid_amount_of_quotes(t_minishell *sh);
static void	ft_heredoc(t_minishell *sh);

void	ft_parse(t_minishell *sh)
{
	ft_valid_empty_cmd(sh);
	if (sh->ret < 0)
		return ;
	add_history(sh->line);
	ft_valid_amount_of_quotes(sh);
	if (sh->ret < 0)
		return ;
	ft_valid_redirect(sh);
	if (sh->ret < 0)
		return ;
	ft_cmd_builder(sh);
	if (sh->ret < 0)
		return ;
	ft_valid_lexcal_cmd(sh);
	if (sh->ret < 0)
		return ;
	ft_redirect_builder(sh);
	if (sh->ret < 0)
		return ;
	ft_heredoc(sh);
	if (sh->ret < 0)
		return ;
}

static void	ft_valid_empty_cmd(t_minishell *sh)
{
	sh->tmp0 = ft_strtrim(sh->line, " ");
	if (!sh->tmp0)
	{
		g_sig.errnbr = errno;
		sh->ret = -3;
		return ;
	}
	if ((ft_strlen(sh->tmp0) == 0))
		sh->ret = -8;
	ft_free_minishell_single_aux(sh->line);
	sh->line = NULL;
	sh->line = sh->tmp0;
	sh->tmp0 = NULL;
}

static void	ft_valid_amount_of_quotes(t_minishell *sh)
{
	long	i;
	long	squote;
	long	dquote;

	i = 0;
	squote = 0;
	dquote = 0;
	while (sh->line[i])
	{
		if (sh->line[i] == '\'')
			squote++;
		else if (sh->line[i] == '\"')
			dquote++;
		i++;
	}
	if (!ft_valid_quote(squote, dquote))
		sh->ret = -5;
}

static void	ft_heredoc(t_minishell *sh)
{
	t_node	*head;

	head = sh->head;
	while (head && (sh->ret == 0))
	{
		if (head->first_cmd[0] != '|' && head->first_cmd[0] != '<' \
				&& head->first_cmd[0] != '>')
		{
			if (head->prev)
			{
				if (ft_strncmp(head->prev->first_cmd, "<<", 2) == 0)
				{
					ft_heredoc_builder(sh, head);
					if (sh->ret < 0)
						break ;
				}
			}
		}
		head = head->next;
	}
}
