/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_parse_commands_utils4.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:12 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/19 19:48:10 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	try_find_cmd_path_using_access(t_cmd *curr_cmd)
{
	char	*path;
	char	**s_path;
	int		i;
	char	*test_this_cmd;

	path = ms_find_env_value(curr_cmd->my_prompt->ms, "PATH");
	if (path == NULL)
		return (0);
	s_path = ft_split(path, ':');
	i = -1;
	while (s_path[++i])
	{
		test_this_cmd = ft_printf_to_var("%s/%s",
				s_path[i], curr_cmd->just_name);
		if (try_find_cmd_path_using_access_aux(curr_cmd, \
test_this_cmd, s_path))
			return (1);
	}
	ft_mtx_free((void **) s_path);
	return (0);
}

typedef struct s_not_dir
{
	char	**levels;
	int		i;
	char	*path;
	int		len;
	char	*tmp;
}	t_not_dir;

int	is_not_a_dir_aux(t_cmd *curr_cmd, t_not_dir *ndir)
{
	if (is_file(ndir->path) && ((ndir->i < ndir->len)))
	{
		ft_pf_error("%s: %s: Not a directory\n", \
"miniheaven", curr_cmd->just_name);
		curr_cmd->exit_code = 126;
		curr_cmd->can_execute = 0;
		set_exit_code(curr_cmd->my_prompt->ms, curr_cmd, 126);
		ft_free_ptr((void *) &ndir->path);
		ft_free_ptr((void *) &ndir->tmp);
		ft_mtx_free((void **) ndir->levels);
		return (1);
	}
	++ndir->i;
	ft_free_ptr((void *) &ndir->tmp);
	ndir->tmp = ft_printf_to_var("%s/%s", ndir->path, \
ndir->levels[ndir->i]);
	ft_free_ptr((void *) &ndir->path);
	ndir->path = ft_strdup(ndir->tmp);
	return (0);
}

int	is_not_a_dir_aux2(t_cmd *curr_cmd, t_not_dir *ndir)
{
	ndir->path = ft_substr(curr_cmd->just_name, 0, \
ft_indexof(curr_cmd->just_name, '/'));
	while (ndir->i <= ndir->len)
	{
		if (is_not_a_dir_aux(curr_cmd, ndir))
		{
			ft_free_ptr((void *) &ndir);
			return (1);
		}
	}
	return (0);
}

int	is_not_a_dir(t_cmd *curr_cmd)
{
	t_not_dir	*ndir;

	ndir = (t_not_dir *)ft_calloc(1, sizeof(t_not_dir));
	ndir->levels = ft_split(curr_cmd->just_name, '/');
	ndir->i = -1;
	ndir->len = ft_mtx_size((void **) ndir->levels) - 1;
	if (ndir->len <= 1)
	{
		ft_mtx_free((void **) ndir->levels);
		ft_free_ptr((void *) &ndir);
		return (0);
	}
	if (is_not_a_dir_aux2(curr_cmd, ndir))
		return (1);
	ft_free_ptr((void *) &ndir->path);
	ft_mtx_free((void **) ndir->levels);
	ft_free_ptr((void *) &ndir);
	return (0);
}

int	ms_parse_commands_aux(t_cmd *curr_cmd, int *c)
{
	parse_input_output(curr_cmd);
	if (curr_cmd->my_prompt->ms->force_stop)
	{
		curr_cmd->my_prompt->ms->force_stop = 0;
		*c = *c + 1;
		return (1);
	}
	return (0);
}
