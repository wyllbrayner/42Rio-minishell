/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:10 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/09 17:15:31 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ms_init_env(t_ms *ms)
{
	int		i;
	int		equal_index;
	char	**envp;
	char	*key;
	char	*value;

	i = 0;
	envp = ms->envp;
	if (ms->envp != NULL)
	{
		while (envp[i])
		{
			equal_index = ft_str_indexof(envp[i], "=", ft_strlen(envp[i]));
			ft_free_ptr((void *) &ms->tmp);
			ms->tmp = ft_substr(envp[i], 0, equal_index);
			key = ms->tmp;
			value = envp[i] + equal_index + 1;
			if (key != NULL && value != NULL)
				ms_add_env(&ms->envs, key, value);
			i++;
		}
		ft_free_ptr((void *) &ms->tmp);
	}
}
