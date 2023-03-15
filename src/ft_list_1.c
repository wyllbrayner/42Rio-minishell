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

//	printf("Dentro da ft_list_add_last | inicio\n");
//	printf("Dentro da ft_list_add_last | entrou no if\n");
//	printf("Dentro da ft_list_add_last | entrou no else\n");
//	printf("Dentro da ft_list_add_last | entrou no else | dentro lo loop\n");
//	printf("Dentro da ft_list_add_last | fim\n");
void	ft_list_add_last(t_node **head, t_node *node)
{
	t_node	*head_int;

	if (!*head && node)
		*head = node;
	else
	{
		head_int = *head;
		while (head_int->next)
			head_int = head_int->next;
		head_int->next = node;
		node->prev = head_int;
	}
}

//	printf("Dentro da ft_print_list | inicio\n");
//	printf("Dentro da ft_print_list | fim\n");
void	ft_print_list(const t_node *node)
{
	t_node	*p;

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
}

//	printf("Dentro da ft_print_rev_list | inicio\n");
//	printf("Dentro da ft_print_rev_list | fim\n");
void	ft_print_rev_list(const t_node *node)
{
	t_node	*p;

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
}
