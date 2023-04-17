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

void	ft_redirect_builder_aux_0(t_minishell *sh, t_node *node);
void	ft_redirect_builder_aux_1(t_minishell *sh, t_node *node, int type);
void	ft_redirect_builder_aux_1_0(int j, t_minishell *sh, t_node *node, \
		int type);

void	ft_redirect_builder(t_minishell *sh)
{
	t_node	*head;

	head = sh->head;
	while (head && (sh->ret == 0))
	{
		if (head->first_cmd[0] != '|' && head->first_cmd[0] != '<' && \
				head->first_cmd[0] != '>')
		{
			if (head->prev)
			{
				if ((ft_strncmp(head->prev->first_cmd, "<", 2) == 0) || \
						(ft_strncmp(head->prev->first_cmd, ">", 2) == 0) || \
						(ft_strncmp(head->prev->first_cmd, ">>", 3) == 0))
				{
					ft_redirect_builder_aux_0(sh, head);
					if (sh->ret < 0)
						break ;
				}
			}
		}
		head = head->next;
	}
}

void	ft_redirect_builder_aux_0(t_minishell *sh, t_node *node)
{
	node->redirect_file = ft_split(node->token, ' ');
	if (!node->redirect_file)
	{
		sh->ret = -3;
		g_sig.errnbr = errno;
		return ;
	}
	while (node->redirect_file[node->redirect_file_fd_amount])
		node->redirect_file_fd_amount++;
	node->redirect_file_fd = (int *)malloc(sizeof(int) * \
			node->redirect_file_fd_amount);
	if (!node->redirect_file_fd)
	{
		sh->ret = -3;
		g_sig.errnbr = errno;
		return ;
	}
	if (ft_strncmp(node->prev->token, ">", 2) == 0)
		ft_redirect_builder_aux_1(sh, node, 1);
	else if (ft_strncmp(node->prev->token, ">>", 3) == 0)
		ft_redirect_builder_aux_1(sh, node, 2);
	else if (ft_strncmp(node->prev->token, "<", 2) == 0)
		ft_redirect_builder_aux_1(sh, node, 3);
}

void	ft_redirect_builder_aux_1(t_minishell *sh, t_node *node, int type)
{
	int	j;

	j = 0;
	while (node->redirect_file[j])
	{
		if (j > 0)
		{
			sh->ret = -7;
			sh->erro = node->redirect_file[j];
			g_sig.errnbr = 1;
			return ;
		}
		ft_redirect_builder_aux_1_0(j, sh, node, type);
		if (sh->ret < 0)
			return ;
		j++;
	}
}

void	ft_redirect_builder_aux_1_0(int j, t_minishell *sh, t_node *node, \
		int type)
{
	if (type == 1)
		node->redirect_file_fd[j] = \
		open(node->redirect_file[j], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (type == 2)
		node->redirect_file_fd[j] = \
		open(node->redirect_file[j], O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (type == 3)
		node->redirect_file_fd[j] = \
		open(node->redirect_file[j], O_RDONLY);
	if (node->redirect_file_fd[j] == -1)
	{
		if (errno == EACCES)
			sh->ret = -12;
		else
			sh->ret = -7;
		sh->erro = node->redirect_file[j];
		g_sig.errnbr = 1;
	}
}
