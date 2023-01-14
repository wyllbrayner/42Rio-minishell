/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:00:20 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/08 07:03:58 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<_minishell.h>

int	ms_is_in_env(t_ms *ms, const char *key)
{
	t_env	*aux;

	aux = ms->envs;
	while (aux)
	{
		if (ft_strncmp(key, aux->key, ft_strlen(key)) == 0)
			return (1);
		aux = aux->next;
	}
	aux = ms->aux_envs;
	while (aux)
	{
		if (ft_strncmp(key, aux->key, ft_strlen(key)) == 0)
			return (1);
		aux = aux->next;
	}
	return (0);
}
