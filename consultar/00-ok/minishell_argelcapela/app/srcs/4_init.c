/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:07 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/13 15:16:27 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	print_banner(void)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open("srcs/3_banner", O_RDONLY);
	while (i < 33)
	{
		line = get_next_line(fd);
		if (line != NULL)
			ft_printf("%s%s%s", BOLD_YELLOW, line, END_COLOR);
		ft_free_ptr((void *) &line);
		i++;
	}
	close(fd);
}

static void	ms_init_aux(t_ms *ms)
{
	ms->is_aux_env = 0;
	ms->slt_splited_by_connectors = NULL;
	ms->readline_var = NULL;
	ms->p = NULL;
	ms->connectors_index = 0;
	ms->connectors_amount = 0;
	ms->connectors_order = NULL;
	ms->no_path = 0;
	ms->here_doc_open = 0;
	ms->here_document = 0;
	ms->str_export = NULL;
	ms->hdoc = 0;
	ms->input_command_open = 0;
	ms->breakline = 0;
	ms->force_stop = 0;
}

void	ms_init(t_ms *ms, int argc, char **argv, char **envp)
{
	ms->argc = argc;
	ms->argv = argv;
	ms->envp = envp;
	ms->exit_code = 0;
	ms->history = NULL;
	ms->envs = NULL;
	ms->p_amount = 1;
	ms->history_i = 0;
	ms->has_double_quotes = 0;
	ms->has_single_quotes = 0;
	ms->exit = 0;
	ms_init_aux(ms);
	ms_init_env(ms);
}
