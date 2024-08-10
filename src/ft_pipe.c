/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiniz <jodiniz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:48:23 by jodiniz           #+#    #+#             */
/*   Updated: 2023/03/16 23:52:01 by jodiniz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

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

int	is_builtin(t_minishell *sh, t_node *temp)
{
	if (sh->head->infile != 0)
		dup_infile_last(sh->head);
	if (sh->head->outfile != 0)
		dup_outfile_last(sh->head);
	if (ft_select_way(sh, temp))
		return (1);
	return (0);
}

void	check_pipe(t_minishell *shell)
{
	int		size;
	t_node	*tmp;

	tmp = shell->head;
	size = 0;
	ft_init_path(shell);
	organize_command(tmp, shell->path);
	ft_free_minishell_double_aux(shell->path);
	shell->path = NULL;
	organize_file_in(tmp);
	organize_file_out(tmp);
	size = count_pipes(shell);
	if (size == 0)
	{
		ft_interpreter(shell, tmp);
		if (is_builtin(shell, tmp))
			ft_start_command(shell, tmp);
	}
	else
		execute_pipe_command(tmp, shell, size);
	restore_fd(shell);
}

void	execute_pipe_command(t_node *temp, t_minishell *sh, int size)
{
	int	prevpipe;
	int	i;

	i = 0;
	prevpipe = dup(STDIN_FILENO);
	while (temp)
	{
		ft_init_path(sh);
		ft_isexec(sh, temp);
		ft_interpreter(sh, temp);
		if (temp->command != 0 && i < size)
		{
			execute_command(&prevpipe, temp, sh);
			i++;
		}
		else if (temp->command == 1 && i >= size)
			ft_last(prevpipe, temp, sh);
		ft_free_minishell_double_aux(sh->path);
		sh->path = NULL;
		temp = temp->next;
	}
}
