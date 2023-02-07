/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17b_tokenizer_wildcard_utils_bonus_2.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 22:26:04 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/14 10:44:30 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ms_go_start(t_file **files)
{
	while (files && (*files) && (*files)->prev != NULL)
		*files = (*files)->prev;
}

void	pre_init_curr_cmd(t_ms *ms, t_p **curr_p,
t_cmd **curr_cmd, int c)
{
	(*curr_cmd)->my_prompt = (*curr_p);
	(*curr_cmd)->my_prompt->ms = ms;
	(*curr_cmd)->input_fd = 0;
	(*curr_cmd)->output_fd = 1;
	(*curr_cmd)->can_execute = 1;
	(*curr_cmd)->cmd_line = \
		ft_strdup((*curr_p)->this_p_line_splited_by_pipe[c]);
	(*curr_cmd)->cmd_line_pre_cat = \
		(*curr_p)->this_p_line_splited_by_pipe[c];
	glued(&(*curr_cmd));
	loose(&(*curr_cmd));
	(*curr_cmd)->cmd_splited_by_space = ft_split((*curr_cmd)->cmd_line, ' ');
	(*curr_cmd)->args_amount = \
ft_mtx_size((void **)(*curr_cmd)->cmd_splited_by_space);
}

int	try_find_cmd_path_using_access_aux(t_cmd *curr_cmd, \
char *test_this_cmd, char **s_path)
{
	if (access(test_this_cmd, X_OK) == 0
		|| access(test_this_cmd, R_OK) == 0)
	{
		ft_mtx_free((void **) s_path);
		curr_cmd->path_and_name = test_this_cmd;
		parse_path_execution(&curr_cmd);
		return (1);
	}
	ft_free_ptr((void *) &test_this_cmd);
	return (0);
}
