/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiniz <jodiniz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:23:51 by jodiniz           #+#    #+#             */
/*   Updated: 2023/03/15 18:10:30 by jodiniz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

void	dup_infile_last(t_node *temp)
{
	dup2(temp->infile[0], 0);
	close(temp->infile[0]);
}

void	dup_outfile_last(t_node *temp)
{
	dup2(temp->outfile[0], 1);
	close(temp->outfile[0]);
}

void	verify(t_node *temp, t_minishell *sh, char *cmd)
{
	if (temp->infile != 0)
		dup_infile_last(temp);
	if (temp->outfile != 0)
		dup_outfile_last(temp);
	if (ft_select_way(sh))
		execve(cmd, temp->cmd, NULL);
}

void	execute_command(int *i, t_node *temp, t_minishell *sh)
{
	char	*cmd;
	int		pipefd[2];
	pid_t	pid1;

	pipe (pipefd);
	cmd = ft_access_command(temp->first_cmd, sh->path);
	pid1 = fork();
	if (pid1 == 0)
	{
		close (pipefd[0]);
		dup2(pipefd[1], 1);
		dup2 (*i, STDIN_FILENO);
		verify(temp, sh, cmd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close (pipefd[1]);
		close (*i);
		*i = pipefd[0];
	}
	ft_free_minishell_single_aux(cmd);
}

void	ft_last(int i, t_node *temp, t_minishell *sh)
{
	pid_t	pid;
	char	*cmd;

	cmd = ft_access_command(temp->first_cmd, sh->path);
	pid = fork();
	if (pid == 0)
	{
		dup2 (i, STDIN_FILENO);
		if (temp->infile != 0)
			dup_infile_last(temp);
		if (temp->outfile != 0)
			dup_outfile_last(temp);
		if (ft_select_way(sh))
			execve(cmd, temp->cmd, NULL);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close (i);
		while (wait (NULL) != -1)
			;
	}
	ft_free_minishell_single_aux(cmd);
}