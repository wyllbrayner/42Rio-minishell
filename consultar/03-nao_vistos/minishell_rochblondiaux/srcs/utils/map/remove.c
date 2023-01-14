/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/17 13:59:55 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	free_target(t_env *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

int	remove_map_element(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	if (!tmp && ft_strcmp_sensitive(tmp->key, key))
	{
		*env = tmp->next;
		free_target(tmp);
		return (1);
	}
	while (tmp && !ft_strcmp_sensitive(tmp->key, key))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (1);
	prev->next = tmp->next;
	free_target(tmp);
	return (0);
}
