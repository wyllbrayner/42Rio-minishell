/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_parse_commands_utils3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:12 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/14 10:19:06 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	loose(t_cmd **curr_cmd)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_super_replace_all((*curr_cmd)->cmd_line, 16,
			">>", T_JOKER,
			T_JOKER, " >>",
			"<<", T_JOKER,
			T_JOKER, " <<",
			"<", T_JOKER,
			T_JOKER, " <",
			">", T_JOKER,
			T_JOKER, " >");
	tmp2 = trim_many_spaces(tmp, " ");
	(*curr_cmd)->cmd_line = tmp2;
	return (0);
}

void	pre_treats(t_cmd **curr_cmd)
{
	ft_mtx_free((void **)(*curr_cmd)->cmd_splited_by_space);
	loose(curr_cmd);
	(*curr_cmd)->cmd_splited_by_space = ft_split((*curr_cmd)->cmd_line, ' ');
	(*curr_cmd)->just_name = ft_strdup((*curr_cmd)->cmd_splited_by_space[0]);
}

int	can_execve(t_cmd **curr_cmd)
{
	int		fd;
	char	**str;
	int		exit_code;
	int		p[2];

	pipe(p);
	str = (char **) ft_calloc(2, sizeof(char *));
	str[0] = ft_strdup((*curr_cmd)->just_name);
	fd = fork();
	if (fd == 0)
	{
		dup2(p[1], 1);
		dup2(p[1], 2);
		if (execve((*curr_cmd)->path_and_name, str,
				(*curr_cmd)->my_prompt->ms->argv) == -1)
			exit(1);
		exit(0);
	}
	waitpid(fd, &exit_code, 0);
	close(p[0]);
	close(p[1]);
	ft_mtx_free((void **) str);
	if (WEXITSTATUS(exit_code) == 1)
		return (0);
	return (1);
}

//3b!
int	parse_path_execution(t_cmd **curr_cmd)
{
	char	*tmp;

	tmp = NULL;
	if ((is_input_command((*curr_cmd)->just_name))
		|| ((*curr_cmd)->args_amount > 1)
		|| ((*curr_cmd)->my_prompt->n_cmds > 1)
		|| can_execve(curr_cmd))
		return (0);
	tmp = ft_printf_to_var("%s %s", "/bin/bash", (*curr_cmd)->path_and_name);
	(*curr_cmd)->cmd_splited_by_space = \
ft_split(tmp, ' ');
	ft_free_ptr((void *) &tmp);
	ft_free_ptr((void *) &(*curr_cmd)->just_name);
	(*curr_cmd)->just_name = ft_strdup("/bin/bash");
	ft_free_ptr((void *) &(*curr_cmd)->path_and_name);
	(*curr_cmd)->path_and_name = ft_strdup("/bin/bash");
	return (0);
}
//export PATH="../tests/test_files:../tests/test_files2"
//bin1
