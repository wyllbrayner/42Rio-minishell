/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/09 18:50:13 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	update_status(t_command *cmd)
{
	if (WIFEXITED(cmd->p_status))
		cmd->p_status = WEXITSTATUS(cmd->p_status);
	if (!WIFSIGNALED(cmd->p_status))
		return ;
	cmd->p_status = WTERMSIG(cmd->p_status);
}

void	handle_delims(t_app *app, t_command *cmd)
{
	int		fd;
	char	*c;

	c = delimit_all(app, cmd);
	if (ft_strcmp(c, "jas2ASSD66aS6gg56q6ev3as3dxx6v6cxv565"))
	{
		fd = open(c, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink(c);
	}
	else if (c)
	{
		reset_cmd(app, cmd, c);
		free (c);
	}
}

static void	handle_redirections(t_command *cmd, t_pipe *pipe)
{
	close(pipe->in);
	if (cmd->input_fd > 0)
	{
		dup2(cmd->input_fd, STDIN_FILENO);
		close(cmd->input_fd);
	}
	close(pipe->out);
	if (cmd->output_fd > 0)
	{
		dup2(cmd->output_fd, STDOUT_FILENO);
		close(cmd->output_fd);
	}
}

static char	**normed(t_app *app, t_command *cmd, t_pipe *pipe)
{
	char	**env;

	env = format_env(app);
	if (is_a_delim(cmd->redirections) == 1)
		handle_delims(app, cmd);
	enable_signal(app);
	dup2(pipe->backup, 0);
	if (cmd->next_token == PIPE && cmd->next_cmd)
		dup2(pipe->out, STDOUT_FILENO);
	handle_redirections(cmd, pipe);
	return (env);
}

void	execute_native(t_app *app, t_command *cmd, t_pipe *pipe)
{
	char	**env;

	if (cmd->pid == 0)
	{
		env = normed(app, cmd, pipe);
		if (is_builtin(cmd))
			dispatch_builtins(app, cmd);
		else
			execve(cmd->executable, get_executable_args(cmd), env);
		exit(1);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(cmd->pid, &cmd->p_status, 0);
		disable_signal(app);
		close(pipe->out);
		update_status(cmd);
		if (is_builtin(cmd))
			cmd->p_status = cmd->status;
		pipe->backup = pipe->in;
	}
}
