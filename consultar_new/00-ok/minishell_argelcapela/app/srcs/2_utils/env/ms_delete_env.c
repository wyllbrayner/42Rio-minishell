/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_delete_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:57:45 by acapela-          #+#    #+#             */
/*   Updated: 2022/11/11 16:43:59 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<_minishell.h>

static void	ms_delete_env_aux(t_env **envs, t_env **aux)
{
	if ((*aux)->next != NULL && (*aux)->prev == NULL)
	{
		(*aux) = (*aux)->next;
		(*aux)->prev = NULL;
		*envs = (*aux);
	}
	else if ((*aux)->next != NULL && (*aux)->prev != NULL)
	{
		(*aux)->prev->next = (*aux)->next;
		(*aux)->next->prev = (*aux)->prev;
	}
	else if ((*aux)->next == NULL && (*aux)->prev != NULL)
		(*aux)->prev->next = NULL;
	else
		*envs = NULL;
}

int	ms_delete_env(t_env **envs, char *key)
{
	t_env	*aux;
	t_env	*delete;

	aux = (*envs);
	while (aux)
	{
		if (ft_strncmp(aux->key, key, ft_strlen(aux->key)) == 0)
		{
			delete = aux;
			ms_delete_env_aux(envs, &aux);
			free(delete->key);
			free(delete->value);
			free(delete);
			return (1);
			break ;
		}
		aux = aux->next;
	}
	return (0);
}
