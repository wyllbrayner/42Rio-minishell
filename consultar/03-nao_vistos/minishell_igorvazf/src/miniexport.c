/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexport.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:15:30 by paugusto          #+#    #+#             */
/*   Updated: 2022/01/07 12:32:57 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	copy_var(t_env *env, char *str)
{
	t_nodenv	*aux;
	char		**var;

	var = ft_split(str, '=');
	aux = env->begin;
	while (aux != NULL)
	{
		if (ft_strcmp(aux->key, var[0]))
			aux = aux->next;
		else
		{
			free(aux->content);
			if (var[1])
				aux->content = ft_strdup(var[1]);
			else
				aux->content = ft_strdup("");
			minifree(var);
			return ;
		}
	}
	push_env(env, var[0], var[1]);
	minifree(var);
}

void	miniexport(t_env *env, t_node *node)
{
	int			j;

	j = 0;
	if (node->str[1])
	{
		while (node->str[1][j] != '=' && node->str[1][j])
			j++;
		if (node->str[1][j] != '=' || j <= 0
			|| (!ft_isalpha(node->str[1][0]) && node->str[1][0] != '_'))
		{
			g_return = 1;
			return ;
		}
		copy_var(env, node->str[1]);
	}
	else
		print_env(env);
	g_return = 0;
}
