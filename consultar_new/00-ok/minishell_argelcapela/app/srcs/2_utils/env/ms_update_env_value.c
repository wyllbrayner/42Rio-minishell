/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_update_env_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:39:40 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/08 07:03:32 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	update_env_value(t_env *env, char *key, char *value)
{
	while (env)
	{
		if ((ft_strncmp(key, env->key, ft_strlen(key)) == 0) && \
			(env->key != NULL && env->value != NULL))
		{
			ft_free_ptr((void *) &env->value);
			env->value = ft_strdup(value);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
