/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiniz <jodiniz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:23:51 by jodiniz           #+#    #+#             */
/*   Updated: 2023/03/17 13:35:54 by jodiniz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

extern t_signal	g_sig;

void	ft_init_path(t_minishell *sh)
{
	long	i;

	i = 0;
	while (sh->env[i])
	{
		if (ft_strncmp(sh->env[i], "PATH", 4) == 0)
		{
			sh->path = ft_split(sh->env[i] + 5, ':');
			if (!sh->path)
			{
				sh->ret = -3;
				g_sig.errnbr = errno;
				return ;
			}
		}
		i++;
	}
}

char	*ft_access_command(t_minishell *sh, t_node *node)
{
	long	i;

	i = 0;
	if (node->first_cmd && sh->path)
	{
		while (sh->path[i])
		{
			sh->tmp0 = ft_strjoin(sh->path[i], "/");
			sh->tmp1 = ft_strjoin(sh->tmp0, node->first_cmd);
			ft_free_minishell_single_aux(sh->tmp0);
			sh->tmp0 = NULL;
			if (access(sh->tmp1, X_OK | F_OK) == 0)
			{
				return (sh->tmp1);
			}
			ft_free_minishell_single_aux(sh->tmp1);
			sh->tmp1 = NULL;
			i++;
		}
	}
	return (0);
}

static void	infile_or_outfile(t_minishell *sh)
{
	if (sh->head->infile != 0)
		dup_infile_last(sh->head);
	if (sh->head->outfile != 0)
		dup_outfile_last(sh->head);
}

static void	ft_start_command_aux0(t_minishell *sh, t_node *node)
{
	pid_t	pid;
	int		status;

	if (node->command == 1 || node->first_cmd[0] != '<')
	{
		pid = fork();
		if (pid == 0)
		{
			infile_or_outfile(sh);
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			if (execve(node->path, node->cmd, sh->env) == -1)
				g_sig.errnbr = errno;
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				g_sig.errnbr = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				g_sig.errnbr = 128 + WTERMSIG(status);
		}
	}
}

void	ft_start_command(t_minishell *sh, t_node *node)
{
	if (sh)
	{
		ft_init_path(sh);
		if (sh->ret < 0)
			return ;
		if (node->first_cmd[0] != '<')
			ft_isexec(sh, node);
		ft_free_minishell_double_aux(sh->path);
		sh->path = NULL;
		if (sh->ret < 0)
			return ;
		else
		{
			ft_start_command_aux0(sh, node);
		}
	}
}
