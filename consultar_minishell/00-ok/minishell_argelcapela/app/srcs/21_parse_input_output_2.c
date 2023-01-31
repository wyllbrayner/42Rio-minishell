/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_parse_input_output_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:19 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/19 19:18:14 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

//5!
char	*trim_many_spaces(char	*line, char *key)
{
	int		spaces;
	char	*remove;
	int		i;
	char	*tmp;

	tmp = NULL;
	spaces = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ' && (line[i + 1] && line[i + 1] == ' '))
		{
			while (line[i++] == ' ')
				spaces++;
			remove = ft_chr_to_str(' ', spaces);
			tmp = ft_str_replace(line, remove, key);
			ft_free_ptr((void *)&remove);
			line = ft_strdup(tmp);
			i = -1;
			spaces = 0;
			ft_free_ptr((void *)&tmp);
		}
	}
	ft_free_ptr((void *)&tmp);
	return (line);
}

//4!
int	test_access1(t_cmd **curr_cmd, char *path, char *subject)
{
	if (is_dir(path))
		return (1);
	if (invalid_permission1(curr_cmd, path, subject))
		return (1);
	return (0);
}

//3!
int	input(t_cmd **curr_cmd)
{
	int	fd;

	if (test_access1(curr_cmd, (*curr_cmd)->symbol_path, "miniheaven"))
		return (1);
	else
	{
		(*curr_cmd)->symbol_path = \
ft_super_replace_all((*curr_cmd)->symbol_path, 2, T_SPACE, " ");
		fd = open((*curr_cmd)->symbol_path, O_RDONLY);
		if (fd == -1 && !(*curr_cmd)->my_prompt->ms->force_stop)
		{
			ft_pf_error("miniheaven: %s %s",
				(*curr_cmd)->symbol_path, E_NOTDIR);
			set_exit_code((*curr_cmd)->my_prompt->ms, (*curr_cmd), 1);
			(*curr_cmd)->can_execute = 0;
			(*curr_cmd)->my_prompt->ms->force_stop = 1;
		}
		if ((*curr_cmd)->input_fd != 0)
			close((*curr_cmd)->input_fd);
		(*curr_cmd)->input_fd = fd;
	}
	return (0);
}

//2!
int	output(t_cmd **curr_cmd)
{
	int	fd;

	fd = 1;
	if (test_access1(curr_cmd,
			(*curr_cmd)->symbol_path, (*curr_cmd)->just_name))
		return (1);
	else
	{
		fd = output_fd(curr_cmd);
		if (fd == -1)
		{
			ft_pf_error("miniheaven: %s %s",
				(*curr_cmd)->symbol_path, E_NOTDIR);
			set_exit_code((*curr_cmd)->my_prompt->ms, (*curr_cmd), 1);
			(*curr_cmd)->can_execute = 0;
			return (1);
		}
		if ((*curr_cmd)->output_fd != 1)
			close ((*curr_cmd)->output_fd);
		(*curr_cmd)->output_fd = fd;
	}
	return (0);
}

//1!
typedef int	(*t_my_functions)(t_cmd **curr_cmd);

int	execute_symbol(t_cmd *curr_cmd, int type, char *cut)
{
	t_my_functions	f[4];

	curr_cmd->type = type;
	f[0] = output;
	f[1] = ms_here_doc;
	f[2] = output;
	f[3] = input;
	if ((*f[type])(&curr_cmd))
	{
		ft_free_ptr((void *) &cut);
		return (1);
	}
	return (0);
}
