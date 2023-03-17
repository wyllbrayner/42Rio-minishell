/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:14 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/15 16:07:55 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ms_init_history_loop(t_ms *ms, char **line,
					char **trim, int fd)
{
	while ((*line))
	{
		add_history((*trim));
		ms_add_history(ms, (*line));
		ft_free_ptr((void *) &(*line));
		(*line) = get_next_line(fd);
		ft_free_ptr((void *) &(*trim));
		(*trim) = ft_strtrim((*line), "\n");
	}
}

void	ms_init_history(t_ms *ms)
{
	int		fd;
	char	*line;
	char	*path;
	char	*tmp;
	char	*trim;

	tmp = ms_find_env_value(ms, "USER");
	ms->history_i = 1;
	path = ft_printf_to_var("/home/%s/.bash_history", tmp);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_to_fd(2, "miniheaven: 1: history: not found\n");
		ms->p->cmds->exit_code = 1;
	}
	line = get_next_line(fd);
	trim = ft_strtrim(line, "\n");
	ms_init_history_loop(ms, &line, &trim, fd);
	get_next_line(-1);
	ft_free_ptr((void *) &path);
	close(fd);
}
