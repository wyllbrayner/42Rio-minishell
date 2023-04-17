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

static t_node	*ft_node_create_aux_0(char *cmd);
static t_node	*ft_node_create_aux_1(t_node *node);
static void		ft_list_destroy_aux0(t_node *tmp);

t_node	*ft_node_create(char *cmd)
{
	t_node	*node;

	node = NULL;
	if (!cmd)
		return (NULL);
	node = ft_node_create_aux_0(cmd);
	if (!node)
		return (NULL);
	node = ft_node_create_aux_1(node);
	if (!node)
		return (NULL);
	return (node);
}

static t_node	*ft_node_create_aux_0(char *cmd)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
	{
		g_sig.errnbr = errno;
		return (NULL);
	}
	node->token = ft_strdup(cmd);
	if (!node->token)
	{
		free(node);
		node = NULL;
		return (NULL);
	}
	node->cmd = ft_split(cmd, ' ');
	if (!node->cmd)
	{
		ft_free_minishell_single_aux(node->token);
		node->token = NULL;
		free(node);
		node = NULL;
		return (NULL);
	}
	return (node);
}

static t_node	*ft_node_create_aux_1(t_node *node)
{
	node->first_cmd = ft_strdup(node->cmd[0]);
	if (!node->first_cmd)
	{
		ft_free_minishell_double_aux(node->cmd);
		node->cmd = NULL;
		ft_free_minishell_single_aux(node->token);
		node->token = NULL;
		free(node);
		node = NULL;
		return (NULL);
	}
	node->path = NULL;
	node->redirect_file = NULL;
	node->redirect_file_fd = NULL;
	node->redirect_file_fd_amount = 0;
	node->command = FALSE;
	node->infile = NULL;
	node->outfile = NULL;
	node->i = NULL;
	node->status = NULL;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	ft_list_destroy(t_node **head)
{
	t_node	*head_int;
	t_node	*tmp;

	head_int = *head;
	if (head_int)
	{
		tmp = NULL;
		while (head_int)
		{
			tmp = head_int;
			head_int = head_int->next;
			ft_list_destroy_aux0(tmp);
			free(tmp);
			tmp = NULL;
		}
	}
}

static void	ft_list_destroy_aux0(t_node *tmp)
{
	ft_free_minishell_single_aux(tmp->token);
	tmp->token = NULL;
	ft_free_minishell_double_aux(tmp->cmd);
	tmp->cmd = NULL;
	ft_free_minishell_single_aux(tmp->first_cmd);
	tmp->first_cmd = NULL;
	ft_free_minishell_single_aux(tmp->path);
	tmp->path = NULL;
	ft_free_minishell_double_aux(tmp->redirect_file);
	tmp->redirect_file = NULL;
	if (tmp->redirect_file_fd)
		ft_free_minishell_close_fd(tmp->redirect_file_fd, \
		tmp->redirect_file_fd_amount);
	tmp->redirect_file_fd = NULL;
	tmp->redirect_file_fd_amount = 0;
	tmp->command = FALSE;
	tmp->infile = NULL;
	tmp->outfile = NULL;
	tmp->i = NULL;
	tmp->status = NULL;
}
