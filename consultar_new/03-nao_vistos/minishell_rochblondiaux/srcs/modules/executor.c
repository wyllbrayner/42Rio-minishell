/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/17 14:07:01 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_commands(t_command **cmds)
{
	size_t	i;

	i = -1;
	cmds[0]->previous_cmd = NULL;
	while (cmds[++i])
	{
		if (i > 0)
			cmds[i]->previous_cmd = cmds[i - 1];
		if (i < commands_length(cmds))
			cmds[i]->next_cmd = cmds[i + 1];
	}
	cmds[i - 1]->next_cmd = NULL;
}

static int	has_permission(t_app *app, t_command *cmd)
{
	struct stat	statbuf;

	if (!lstat(cmd->executable, &statbuf))
	{
		if (statbuf.st_mode & S_IFREG)
		{
			if (statbuf.st_mode & S_IXUSR)
				return (TRUE);
			else
			{
				cmd->status = 126;
				error(app, PERMISSION_DENIED, cmd->name);
				return (FALSE);
			}
		}
		else
		{
			cmd->status = 1;
			error(app, cmd->name, IS_DIRECTORY);
			return (FALSE);
		}
	}
	if (access(cmd->executable, F_OK | X_OK) == FALSE)
		return (TRUE);
	return (TRUE);
}

static void	execute_command(t_app *app, t_command *cmd, t_pipe *pipe)
{
	if (!find_executable(app, cmd) && !is_builtin(cmd))
	{
		cmd->status = 127;
		error(app, cmd->name, COMMAND_NOT_FOUND);
		return ;
	}
	if (!has_permission(app, cmd))
		return ;
	if (is_builtin(cmd) && !ft_strcmp(cmd->name, "echo"))
		return (dispatch_builtins(app, cmd));
	if (!fork_cmd(app, cmd))
		return ;
	execute_native(app, cmd, pipe);
	cmd->status = cmd->p_status;
}

void	executor(t_app *app, t_command **cmds)
{
	int		i;
	t_pipe	*pipe;

	i = -1;
	check_for_env(app, cmds);
	init_commands(cmds);
	pipe = init_pipeline(app);
	if (!pipe)
		return ;
	while (cmds[++i])
	{
		if (cmds[i]->name && !cmds[i]->name[0])
			continue ;
		execute_command(app, cmds[i], pipe);
		app->last_exit = cmds[i]->status;
		app->exit = app->last_exit != 0;
		update_pipeline(app, pipe);
	}
	free(pipe);
}
