/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   32_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:34 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/02 19:38:31 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	ms_print_env(t_ms *ms, int aux)
{
	char	*line;
	t_env	*env;

	env = ms->envs;
	while (env)
	{
		if (env->key != NULL && env->value != NULL)
		{
			line = ft_printf_to_var("%s=%s\n", env->key, env->value);
			ft_putstr_fd(line, aux);
			ft_free_ptr((void *) &line);
		}
		env = env->next;
	}
}

void	ms_env(t_ms *ms, t_cmd *curr_cmd, t_p *prompt)
{
	int		aux;
	int		clo;

	clo = 0;
	aux = bridge_builtion_other_cmds(curr_cmd, prompt, &clo);
	ms_print_env(ms, aux);
	ms->p->cmds->exit_code = EXIT_SUCCESS;
	if (clo)
		close(aux);
}
