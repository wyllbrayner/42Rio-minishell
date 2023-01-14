/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:07 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/08 08:20:54 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	update_env_values(t_ms *ms, t_cmd *curr_cmd, \
	char **cmd, int aux)
{
	char		pwd[999];
	char		*oldpwd;
	char		*line;

	oldpwd = ms_find_env_value(ms, "PWD");
	if (oldpwd)
	{
		if (chdir(cmd[1]) == -1)
		{
			line = ft_printf_to_var("miniheaven: cd: %s:\
 No such file or directory\n", cmd[1]);
			ft_putstr_fd(line, aux);
			ms->p->cmds->exit_code = 1;
			set_exit_code(curr_cmd->my_prompt->ms, curr_cmd, 1);
			ft_free_ptr((void *) &line);
		}
		else
		{
			getcwd(pwd, 999);
			update_env_value(ms->envs, "OLDPWD", oldpwd);
			update_env_value(ms->envs, "PWD", pwd);
		}
	}
}

void	update_env_value_according_arg_aux(t_ms *ms,
char **cmd, t_cmd *curr_cmd, int aux)
{
	char		*line;
	char		pwd[999];

	if (!cmd[1] || !ft_strncmp(cmd[1], "~", ft_strlen(cmd[1]))
		|| !ft_strncmp(cmd[1], "--", 2))
	{
		chdir(getenv("HOME"));
		update_env_value(ms->envs, "OLDPWD", getenv("PWD"));
		update_env_value(ms->envs, "PWD", getenv("HOME"));
	}
	else if (!ft_strncmp(cmd[1], "-", ft_strlen(cmd[1])))
	{
		line = ft_printf_to_var("%s\n", ms_find_env_value(ms, "OLDPWD"));
		ft_putstr_fd(line, aux);
		chdir(ms_find_env_value(ms, "OLDPWD"));
		getcwd(pwd, 999);
		update_env_value(ms->envs, "OLDPWD", ms_find_env_value(ms, "PWD"));
		update_env_value(ms->envs, "PWD", pwd);
		ft_free_ptr((void *) &line);
	}
	else
		update_env_values(ms, curr_cmd, cmd, aux);
}

static int	update_env_value_according_arg(t_ms *ms, \
t_cmd *curr_cmd, int aux)
{
	char		**cmd;

	cmd = curr_cmd->cmd_splited_by_space;
	if (ft_mtx_size((void **) cmd) > 2)
	{
		ft_putstr_fd("miniheaven: cd: too many arguments\n", aux);
		return (1);
	}
	update_env_value_according_arg_aux(ms, cmd, curr_cmd, aux);
	return (0);
}

void	ms_cd(t_ms *ms, t_cmd *curr_cmd, t_p *prompt)
{
	int		aux;
	int		clo;
	char	*line;

	clo = 0;
	aux = bridge_builtion_other_cmds(curr_cmd, prompt, &clo);
	if (!ms_is_in_env(ms, "HOME"))
	{
		line = ft_printf_to_var("%s", EHNOTSET);
		ft_putstr_fd(line, aux);
		ms->p->cmds->exit_code = 1;
		set_exit_code(curr_cmd->my_prompt->ms, curr_cmd, 1);
		ft_free_ptr((void *) &line);
	}
	else
	{
		if (!ms_is_in_env(ms, "OLDPWD"))
			ms_add_env(&ms->envs, "OLDPWD", ms_find_env_value(ms, "HOME"));
		if (update_env_value_according_arg(ms, curr_cmd, aux))
			set_exit_code(curr_cmd->my_prompt->ms, curr_cmd, 1);
	}
	if (clo)
		close(aux);
}
