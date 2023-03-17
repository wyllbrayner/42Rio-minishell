/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   26_execute_commands_utils_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/17 15:58:19 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	is_builtin(char *curr_cmd)
{
	if (curr_cmd == NULL)
		return (0);
	else if (ft_strncmp(curr_cmd, "history", ft_strlen(curr_cmd)) == 0)
		return (1);
	else if (ft_strncmp(curr_cmd, "exit", ft_strlen(curr_cmd)) == 0)
		return (1);
	else if (ft_strncmp(curr_cmd, "echo", ft_strlen(curr_cmd)) == 0)
		return (1);
	else if (ft_strncmp(curr_cmd, "pwd", ft_strlen(curr_cmd)) == 0)
		return (1);
	else if (ft_strncmp(curr_cmd, "cd", ft_strlen(curr_cmd)) == 0)
		return (1);
	else if (ft_strncmp(curr_cmd, "export", ft_strlen(curr_cmd)) == 0)
		return (1);
	else if (ft_strncmp(curr_cmd, "unset", ft_strlen(curr_cmd)) == 0)
		return (1);
	else if (ft_strncmp(curr_cmd, "env", ft_strlen(curr_cmd)) == 0)
		return (1);
	else
		return (0);
}

void	execute_builtin(t_ms *ms, t_cmd *curr_cmd, t_p *prompt)
{
	char	*name;

	name = curr_cmd->just_name;
	if (ft_strncmp(name, "exit", 4) == 0)
		ms_exit(ms, curr_cmd);
	else if (ft_strncmp(name, "echo", 4) == 0)
		ms_echo(ms, curr_cmd, prompt);
	else if (ft_strncmp(name, "pwd", 3) == 0)
		ms_pwd(ms, curr_cmd, prompt);
	else if (ft_strncmp(name, "cd", 2) == 0)
		ms_cd(ms, curr_cmd, prompt);
	else if (ft_strncmp(name, "export", 6) == 0)
		ms_export(ms, curr_cmd);
	else if (ft_strncmp(name, "unset", 5) == 0)
		ms_unset(ms, curr_cmd, prompt);
	else if (ft_strncmp(name, "env", 3) == 0)
		ms_env(ms, curr_cmd, prompt);
}

static int	pipe_fd(t_cmd *curr_cmd, int tmp_fd[])
{
	pipe(tmp_fd);
	curr_cmd->input_fd = tmp_fd[0];
	return (tmp_fd[1]);
}

int	bridge_builtion_other_cmds(t_cmd *curr_cmd, t_p *prompt, int *clo)
{
	int		tmp_fd[2];
	int		aux;

	if ((curr_cmd->index == (prompt->args_amount - 1)) \
	&& curr_cmd->output_fd > 0)
		aux = curr_cmd->output_fd;
	else if (curr_cmd->index == (prompt->args_amount - 1))
		aux = 1;
	else
	{
		aux = pipe_fd(curr_cmd, tmp_fd);
		*clo = 1;
	}
	return (aux);
}

char	**ft_mtx_replace_all_special(char **mtx, t_cmd *curr_cmd)
{
	char	**n_mtx;
	char	*e_code;

	e_code = last_cmd_exit_code(curr_cmd);
	n_mtx = NULL;
	n_mtx = ft_super_mtx_replace_all(mtx, 8,
			T_HEREDOC, "<<",
			T_INPUT, "<",
			T_SPACE, " ",
			T_EXIT_CODE, e_code);
	return (n_mtx);
}
