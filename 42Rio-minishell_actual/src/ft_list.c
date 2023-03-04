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

t_node	*ft_node_create(char *cmd)
{
//	printf("Dentro da ft_node_create | inicio cmd: #%s#\n", cmd);
	t_node	*node;

	if (!cmd)
		return (NULL);
	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
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
	node->prev = NULL;
	node->next = NULL;
//	printf("Dentro da ft_node_create | fim\n");
	return (node);
}

void ft_list_add_last(t_node **head, t_node *node)
{
//	printf("Dentro da ft_list_add_last | inicio\n");
	t_node *head_int;

//	if (!*head && !node)
//	{
		if (!*head && node)
		{
//			printf("Dentro da ft_list_add_last | entrou no if\n");
			*head = node;
		}
		else
		{
//			printf("Dentro da ft_list_add_last | entrou no else\n");
			head_int = *head;
			while (head_int->next)
			{
//				printf("Dentro da ft_list_add_last | entrou no else | dentro lo loop\n");
				head_int = head_int->next;
			}
			head_int->next = node;
			node->prev = head_int;
		}
//	}
//	printf("Dentro da ft_list_add_last | fim\n");
}

void ft_list_destroy(t_node **head)
{
	t_node *head_int;
	t_node *tmp;

//	printf("Dentro da ft_list_destroy | inicio\n");
	head_int = *head;
	if (head_int)
	{
		tmp = NULL;
		while (head_int)
		{
			tmp = head_int;
			head_int = head_int->next;
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
			ft_free_minishell_close_fd(tmp->redirect_file_fd, tmp->redirect_file_fd_amount);
			tmp->redirect_file_fd = NULL;
			tmp->redirect_file_fd_amount = 0;
			free(tmp);
			tmp = NULL;
		}
	}
//	printf("Dentro da ft_list_destroy | fim\n");
}

void ft_print_list(const t_node *node)
{
//	printf("Dentro da ft_print_list | inicio\n");
    t_node *p;

    p = (t_node *)node;
    if (p)
    {
        printf("HEAD -> ");
        while (p)
        {
            printf("token: %s -> ", p->token);
            p = p->next;
        }
        printf("NULL\n");
    }
//	printf("Dentro da ft_print_list | fim\n");
}

void ft_print_rev_list(const t_node *node)
{
//	printf("Dentro da ft_print_rev_list | inicio\n");
    t_node *p;

    p = (t_node *)node;
    if (p)
    {
        while (p->next)
            p = p->next;
        printf("NULL -> ");
		while (p)
		{
            printf("token: %s -> ", p->token);
			p = p->prev;
		}	
        printf("HEAD\n");
    }
//	printf("Dentro da ft_print_rev_list | fim\n");
}

/*
void ft_print_rev_list(const t_minishell *sh)
{
//	printf("Dentro da ft_print_rev_list | inicio\n");
    t_node *p;

    p = sh->head;
    if (p)
    {
        while (p->next)
            p = p->next;
        printf("NULL -> ");
		while (p)
		{
            printf("token: %s -> ", p->token);
			p = p->prev;
		}	
        printf("HEAD\n");
    }
//	printf("Dentro da ft_print_rev_list | fim\n");
}
*/
