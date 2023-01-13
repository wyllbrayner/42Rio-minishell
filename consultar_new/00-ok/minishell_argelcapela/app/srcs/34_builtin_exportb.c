/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   34_builtin_exportb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:25 by acapela-          #+#    #+#             */
/*   Updated: 2022/11/30 12:01:18 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

char	**env_to_array(t_ms *ms)
{
	char	**arr;
	int		i;
	int		count;
	t_env	*tmp_env;

	tmp_env = ms->envs;
	count = 0;
	while (tmp_env)
	{
		count++;
		tmp_env = tmp_env->next;
	}
	arr = ft_calloc(count + 1, sizeof(char *));
	i = 0;
	tmp_env = ms->envs;
	while (tmp_env)
	{
		if (tmp_env->key != NULL && tmp_env->value != NULL)
		{
			arr[i] = ft_printf_to_var("%s=%s", tmp_env->key, tmp_env->value);
			i++;
		}
		tmp_env = tmp_env->next;
	}
	return (arr);
}
