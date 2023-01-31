/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   23_parse_commands_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:12 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/14 17:31:52 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

t_cmd	*append_new_cmd_next(t_cmd *curr_cmd)
{
	curr_cmd->next = (t_cmd *) ft_calloc(1, sizeof(t_cmd));
	curr_cmd->next->prev = curr_cmd;
	curr_cmd = curr_cmd->next;
	curr_cmd->next = NULL;
	curr_cmd->can_execute = 1;
	return (curr_cmd);
}

int	is_input_command(char *name)
{
	if (ft_strnstr(name, "cat", ft_strlen(name)) || \
		ft_strnstr(name, "more", ft_strlen(name)) || \
		ft_strnstr(name, "less", ft_strlen(name)) || \
		ft_strnstr(name, "tail", ft_strlen(name)) || \
		ft_strnstr(name, "touch", ft_strlen(name)) || \
		ft_strnstr(name, "tr", ft_strlen(name)) || \
		ft_strnstr(name, "grep", ft_strlen(name)) || \
		ft_strnstr(name, "head", ft_strlen(name)) || \
		ft_strnstr(name, "tail", ft_strlen(name)) || \
		ft_strnstr(name, "wc", ft_strlen(name)))
	{
		g_ms->input_command_open = 1;
		return (1);
	}
	return (0);
}

int	is_dir(char *path)
{
	struct stat	*statbuf;
	int			is;

	statbuf = (struct stat *) ft_calloc(1, sizeof(struct stat));
	is = 0;
	stat(path, statbuf);
	is = S_ISDIR(statbuf->st_mode);
	ft_free_ptr((void *)&statbuf);
	if (is)
		return (1);
	else
		return (0);
}

int	is_file(const char *path)
{
	struct stat	*path_stat;

	path_stat = (struct stat *) ft_calloc(1, sizeof(struct stat));
	stat(path, path_stat);
	if (S_ISREG(path_stat->st_mode))
	{
		ft_free_ptr((void *) &path_stat);
		return (1);
	}
	ft_free_ptr((void *) &path_stat);
	return (0);
}

int	invalid_permission2(t_cmd **curr_cmd, char *path, char *subject)
{
	if (!is_file(path))
		return (0);
	if (can_read(path) == -1
		|| can_write(path) == -1
		|| can_execute(path) == -1)
	{
		ft_pf_error("%s: %s %s", subject, path, E_ACCESS);
		set_exit_code((*curr_cmd)->my_prompt->ms, (*curr_cmd), 126);
		return (1);
	}
	return (0);
}
