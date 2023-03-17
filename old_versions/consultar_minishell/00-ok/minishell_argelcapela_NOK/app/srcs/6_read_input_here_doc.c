/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_read_input_here_doc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:42 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/05 19:40:00 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	here_doc_ctrl_c(int signal)
{
	if (g_ms->here_doc_open)
		ft_putstr_fd("\n", 1);
	exit(1);
	(void)signal;
}

void	get_stdin(t_cmd **curr_cmd)
{
	char	*stdin_str;

	signal(SIGINT, here_doc_ctrl_c);
	while (1)
	{
		stdin_str = readline("> ");
		if (!stdin_str)
		{
			ft_printf_to_fd(1, "miniheaven: warning: \
here-document at line %d delimited by end-of-file (wanted `%s')\n", \
		(*curr_cmd)->my_prompt->ms->here_document, (*curr_cmd)->symbol_path);
			exit(0);
		}
		else if (ft_strncmp(stdin_str, (*curr_cmd)->symbol_path,
				ft_strlen((*curr_cmd)->symbol_path)) == 0)
			break ;
		else
		{	
			ft_putstr_fd(stdin_str, g_ms->pipe_here_doc[1]);
			ft_putstr_fd("\n", g_ms->pipe_here_doc[1]);
		}
	}
	exit(0);
}

int	ms_here_doc(t_cmd **curr_cmd)
{
	int	fd_out;
	int	pid;
	int	exit_code;

	pipe(g_ms->pipe_here_doc);
	g_ms->here_doc_open = 1;
	fd_out = dup(STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		get_stdin(curr_cmd);
	waitpid(pid, &exit_code, 0);
	if (WEXITSTATUS(exit_code) == 1)
	{
		close(g_ms->pipe_here_doc[0]);
		close(g_ms->pipe_here_doc[1]);
		pipe(g_ms->pipe_here_doc);
	}
	close(g_ms->pipe_here_doc[1]);
	(*curr_cmd)->input_fd = g_ms->pipe_here_doc[0];
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	g_ms->here_doc_open = 0;
	g_ms->here_document += 1;
	return (0);
}
