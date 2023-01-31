/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:07:40 by ldatilio          #+#    #+#             */
/*   Updated: 2022/08/27 04:33:20 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	signal_handler(int signum)
{
	(void)signum;
	if (g_msh.here_doc == 1)
	{
		close (STDIN_FILENO);
		g_msh.error = 1;
		write (1, "\n", 1);
	}
	else if (g_msh.pid != 0)
	{
		kill(g_msh.pid, SIGKILL);
		write (1, "\n", 1);
	}
	else
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_msh.exit_code = 130;
}

void	signal_exit(int signum)
{
	write (1, "\n", 1);
	free_all();
	exit(signum);
}
