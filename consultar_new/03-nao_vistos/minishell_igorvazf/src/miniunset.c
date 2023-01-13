/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniunset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 00:26:24 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/31 21:19:07 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	miniunset(t_env *env, t_node *node, t_nodenv *aux, t_nodenv *prev)
{
	while (aux != NULL && node->str[1])
	{
		if (ft_strcmp(aux->key, node->str[1]))
		{
			if (aux == env->begin && prev == env->begin)
				aux = aux->next;
			else
			{
				aux = aux->next;
				prev = prev->next;
			}
		}
		else
		{
			prev->next = aux->next;
			free(aux->key);
			free(aux->content);
			free(aux);
			aux = prev->next;
			break ;
		}
	}
	g_return = 0;
}
