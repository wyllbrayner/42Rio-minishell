/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_parse_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:12 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/19 19:31:46 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

//5!
int	decide_correct_error_message(t_cmd *curr_cmd)
{
	char	*e_code;

	e_code = last_cmd_exit_code(curr_cmd);
	curr_cmd->cmd_line = ft_super_replace_all(curr_cmd->cmd_line, 14,
			T_SPACE, " ",
			T_INPUT, "<",
			T_HEREDOC, "<<",
			T_OUTPUT1, ">",
			T_OUTPUT2, ">>",
			T_SUBSHELL, "()",
			T_EXIT_CODE, e_code);
	ft_free_ptr((void *) &e_code);
	if (ft_strnstr(curr_cmd->cmd_line, "/", ft_strlen(curr_cmd->cmd_line))
		|| ms_find_env_value(curr_cmd->my_prompt->ms, "PATH") == NULL)
		ft_pf_error("miniheaven: %s %s", curr_cmd->cmd_line, E_NOTDIR);
	else
		ft_pf_error("miniheaven: %s %s\n",
			curr_cmd->cmd_line, E_CMDNOTFOUND);
	set_exit_code(curr_cmd->my_prompt->ms, curr_cmd, 127);
	curr_cmd->can_execute = 0;
	curr_cmd->exit_code = 127;
	return (0);
}

//4!
int	parse_cmd_with_directory(t_cmd *curr_cmd)
{
	if (is_dir(curr_cmd->just_name))
	{
		ft_pf_error("%s: %s %s", "miniheaven", curr_cmd->just_name, E_ISDIR);
		curr_cmd->exit_code = 126;
		curr_cmd->can_execute = 0;
		set_exit_code(curr_cmd->my_prompt->ms, curr_cmd, 126);
		return (1);
	}
	else if (is_not_a_dir(curr_cmd))
		return (1);
	else if (access(curr_cmd->just_name, X_OK) == 0
		&& is_file(curr_cmd->just_name))
	{
		curr_cmd->path_and_name = ft_strdup(curr_cmd->cmd_splited_by_space[0]);
		return (1);
	}
	else if (invalid_permission1(&curr_cmd, NULL, NULL))
		return (1);
	return (0);
}

//3!
int	parse_cmd_path(t_cmd *curr_cmd)
{
	int	res;

	res = 0;
	if (*(curr_cmd->cmd_line) == '\0' || curr_cmd->cmd_line == NULL)
		return (1);
	pre_treats(&curr_cmd);
	if (!ft_strncmp(curr_cmd->cmd_line, T_SUBSHELL, ft_strlen(T_SUBSHELL)))
		return (0);
	if (is_builtin(curr_cmd->just_name))
		return (0);
	else if (ft_strrchr(curr_cmd->cmd_line, '/')
		&& parse_cmd_with_directory(curr_cmd))
		return (0);
	else if (try_find_cmd_path_using_access(curr_cmd))
		return (0);
	else
		decide_correct_error_message(curr_cmd);
	return (res);
}

//2!
int	if_cmd_is_subsh_enable_subsh_execution( \
t_p *curr_p, t_cmd *curr_cmd)
{
	char	*tmp;

	tmp = ft_strtrim(curr_cmd->cmd_line, " ");
	if ((ft_strncmp(tmp, T_SUBSHELL, ft_strlen(tmp)) == 0)
		&& curr_p->n_cmds > 1)
	{
		curr_cmd->cmd_line = ft_str_replace(curr_cmd->cmd_line,
				T_SUBSHELL, curr_p->subs[curr_p->i_subs].shell_line);
		curr_p->i_subs++;
		curr_cmd->subshell = 1;
	}
	ft_free_ptr((void *) &tmp);
	return (0);
}

//1!
int	ms_parse_commands(t_ms *ms, t_p *curr_p)
{
	t_cmd	*curr_cmd;
	int		c;

	c = 0;
	curr_p->cmds = (t_cmd *) ft_calloc (1, sizeof(struct s_cmd));
	curr_cmd = curr_p->cmds;
	while (c < curr_p->n_cmds)
	{
		if (c > 0)
			curr_cmd = append_new_cmd_next(curr_cmd);
		curr_cmd->index = c;
		pre_init_curr_cmd(ms, &curr_p, &curr_cmd, c);
		if (ms_parse_commands_aux(curr_cmd, &c))
			continue ;
		if (parse_cmd_path(curr_cmd)
			|| if_cmd_is_subsh_enable_subsh_execution(curr_p, curr_cmd))
			return (1);
		ft_free_ptr((void *) &curr_cmd->symbol_path);
		c++;
	}
	curr_p->i_subs = 0;
	return (0);
}
