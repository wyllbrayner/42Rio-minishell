/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   36_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:45 by acapela-          #+#    #+#             */
/*   Updated: 2022/11/30 15:48:59 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ms_pwd(t_ms *ms, t_cmd *curr_cmd, t_p *prompt)
{
	char	cwd[4096];
	int		aux;
	int		clo;

	clo = 0;
	aux = bridge_builtion_other_cmds(curr_cmd, prompt, &clo);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ms->p->cmds->exit_code = 0;
		ft_putstr_fd(cwd, aux);
		ft_putstr_fd("\n", aux);
	}
	else
		ms->p->cmds->exit_code = 1;
	if (clo)
		close(aux);
}
