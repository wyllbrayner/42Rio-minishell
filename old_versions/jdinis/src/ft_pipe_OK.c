/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiniz <jodiniz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:48:23 by jodiniz           #+#    #+#             */
/*   Updated: 2023/03/15 18:51:03 by jodiniz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

void	check_pipe(t_minishell *shell)
{
	int		size;
	t_node	*tmp;

	tmp = shell->head;
	size = 0;
	organize_command(tmp, shell->path);
	organize_file_in(tmp);
	organize_file_out(tmp);
	size = count_pipes(shell);
	if (size == 0)
	{
		if (is_builtin(shell))
			ft_start_command(shell);
	}
	else
		execute_pipe_command(tmp, shell, size);
	/// colocar função waitpid;
	restore_fd(shell);
}

//waitpid (*rato, &status, 0);  if (WIFEXITED(status))                    sh->errnbr = WEXITSTATUS(status);                if (WIFSIGNALED(status))                    sh->errnbr = 128 + WTERMSIG(status);

void	organize_command(t_node *temp, char **path)
{
	bool	after_redirect;

	after_redirect = false;
	while (temp)
	{
		if (is_redirect(&temp, &after_redirect))
			continue ;
		else if (after_redirect)
		{
			after_redirect = false;
			if (temp->next != NULL)
			{
				temp = temp->next;
				continue ;
			}
		}
		else if (prev_redirect(&temp))
			continue ;
		else
			temp->command = ft_access(temp->first_cmd, path);
		temp = temp->next;
	}
}

int	is_redirect(t_node **temp, bool *redirect)
{
	t_node	*tmp;

	tmp = *temp;
	if (tmp->first_cmd[0] == '<' || tmp->first_cmd[0] == '>')
	{
		*redirect = true;
		if (tmp->next != NULL)
		{
			tmp = tmp->next;
			*temp = tmp;
			return (1);
		}
	}
	*temp = tmp;
	return (0);
}

int	prev_redirect(t_node **temp)
{
	t_node	*tmp;

	tmp = *temp;
	if ((tmp->prev != NULL ) && (tmp->prev->first_cmd[0] == '<' || \
		tmp->prev->first_cmd[0] == '>'))
	{
		tmp->command = false;
		tmp = tmp->next;
		tmp = *temp;
		return (1);
	}
	tmp = *temp;
	return (0);
}

int	count_pipes(t_minishell *sh)
{
	t_node	*temp;
	int		size;

	size = 0;
	temp = sh->head;
	while (temp)
	{
		if (temp->first_cmd[0] == '|')
			size++;
		temp = temp->next;
	}
	return (size);
}

int	is_builtin(t_minishell *sh)
{
	if (sh->head->infile != 0)
		dup_infile_last(sh->head);
	if (sh->head->outfile != 0)
		dup_outfile_last(sh->head);
	if (ft_select_way(sh))
		return (1);
	return (0);
}

void	ft_start_command(t_minishell *sh)
{
	int		pid;
	char	*tmp;

	tmp = NULL;
	if (sh->head->first_cmd)
		tmp = ft_access_command(sh->head->first_cmd, sh->path);
	pid = fork();
	if (pid == 0)
	{
		if (sh->head->infile != 0)
			dup_infile_last(sh->head);
		if (sh->head->outfile != 0)
			dup_outfile_last(sh->head);
		execve(tmp, sh->head->cmd, sh->env);
	}
	waitpid (pid, NULL, 0);
	ft_free_minishell_single_aux(tmp);
}

void	execute_pipe_command(t_node *temp, t_minishell *sh, int size)
{
	int	prevpipe;
	int	i;

	i = 0;
	prevpipe = dup(STDIN_FILENO);
	while (temp)
	{
		if (temp->command != 0 && i < size)
		{
			execute_command(&prevpipe, temp, sh);
			i++;
		}
		else if (temp->command == 1 && i >= size)
			ft_last(prevpipe, temp, sh);
		temp = temp->next;
	}
}
