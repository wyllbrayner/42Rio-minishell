/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:29:55 by paugusto          #+#    #+#             */
/*   Updated: 2022/01/09 16:08:15 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*create_list(void)
{
	t_list	*list;

	list = (t_list *)ft_calloc(1, sizeof(t_list));
	list->begin = NULL;
	list->end = NULL;
	list->size = 0;
	return (list);
}

t_node	*create_node(char *str)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->str = ft_split(str, ' ');
	node->next = NULL;
	return (node);
}

void	push_node(t_list *list, char *str)
{
	t_node	*node;

	node = create_node(str);
	if (list->begin == NULL)
	{
		list->begin = node;
		list->end = node;
	}
	else
	{
		list->end->next = node;
		list->end = list->end->next;
	}
	list->size++;
}

void	free_list(t_list **list_ref)
{
	t_list	*list;
	t_node	*node;
	t_node	*aux;

	list = *list_ref;
	node = list->begin;
	aux = NULL;
	while (node != NULL)
	{
		aux = node;
		node = node->next;
		minifree(aux->str);
		free(aux);
	}
	free(list);
	*list_ref = NULL;
}
