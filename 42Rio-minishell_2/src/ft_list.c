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

static t_node	*ft_node_create(char **cmd)
{
	t_node	*node;

    printf("Dentro da node_create | inicio\n");
	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->cmd = (char **)malloc(sizeof(char *) * 2);
	if (!node->cmd)
		return (NULL);
	node->cmd[0] = cmd[0];
	node->cmd[1] = cmd[1];
//	node->cmd = cmd;
	node->prev = NULL;
	node->next = NULL;
    printf("Dentro da node_create | fim\n");
	return (node);
}

t_list	*ft_list_create(void)
{
//    printf("Dentro da list_create | inicio\n");
	t_list	*l;
//    printf("Dentro da list_create | ponteiro da list %p (pré malloc)\n", l);

	l = (t_list *)malloc(sizeof(t_list));
	if (!l)
		return (NULL);
	l->begin = NULL;
	l->end = NULL;
	l->size = 0;
//    printf("Dentro da list_create | ponteiro da list %p (pós malloc)\n", l);
//    printf("Dentro da list_create | fim\n");
	return (l);
}

static bool	ft_list_is_empty(const t_list *l)
{
	return ((l->size) == 0);
}

void ft_list_add_last_2(t_node **head, t_node *node)
{
	t_node *head_int;

	if (*head && node)
	{
		head_int = *head;
		while (head_int->next)
		{
			head_int = head_int->next;
		}
		head_int->next = node;
		no->prev = head_int;
	}
}

void ft_list_destroy(t_node **head)
{
	t_node *head_int;
	t_node *tmp;

	head_int = *head;
	if (head_int)
	{
		tmp = NULL;
		while (head_int)
		{
			tmp = head_int;
			head_int = head_int->next;
			ft_free_minishell_double_aux(tmp->cmd);
			free(tmp);
			tmp = NULL;
		}
	}
}

void	ft_list_add_last(t_list *l, char **cmd)
{
	t_node	*p;

	p = ft_node_create(cmd);
	if (!p)
		exit(-1);
	if (ft_list_is_empty(l))
	{
		l->begin = p;
		l->end = p;
	}
	else
	{
		l->end->next = p;
		p->prev = l->end;
		l->end = p;
	}
	l->size++;
}

void	ft_list_destroy(t_list **l_ref)
{
	t_list	*l;
	t_node	*p;
	t_node	*tmp;
    printf("Dentro da list_destroy | inicio\n");
	l = *l_ref;
	if (l)
	{
		p = l->begin;
		tmp = NULL;
		printf("Dentro da list_destroy | vai entrar no loop\n");
		while (p != NULL)
		{
		    printf("Dentro da list_destroy | entrou no loop para liberar o nó\n");
			tmp = p;
			p = p->next;
		    printf("Dentro da list_destroy | entrou no loop para liberar o nó | vai chamar a free double para tmp->cmd\n");
			ft_free_minishell_double_aux(tmp->cmd);
		    printf("Dentro da list_destroy | entrou no loop para liberar o nó | retornou  da free double para tmp->cmd\n");
			free(tmp);
		    printf("Dentro da list_destroy | entrou no loop para liberar o nó | vai chamar a free para tmp\n");
			tmp = NULL;
		    printf("Dentro da list_destroy | entrou no loop para liberar o nó | liberou a memória de tmp\n");
		}
		printf("Dentro da list_destroy | saiu do loop\n");
//		printf("Dentro da list_destroy | vai liberar a lista\n");
//		free(l);
//		printf("Dentro da list_destroy | lista liberada\n");
//		*l_ref = NULL;
    	printf("Dentro da list_destroy | fim\n");
	}
}