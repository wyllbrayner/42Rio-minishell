/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

extern t_signal	g_sig;

void	ft_free_minishell(t_minishell *sh, int status)
{
	t_node	*tmp;

	if (sh && (status == 1))
	{
		ft_free_minishell_single_aux(sh->line);
		sh->line = NULL;
		tmp = sh->head;
		ft_list_destroy(&tmp);
		ft_init_var_aux_one(sh);
	}
	if (sh && (status == 2))
	{
		ft_free_minishell_double_aux(sh->env);
		sh->env = NULL;
		ft_free_minishell_double_aux(sh->path);
		sh->path = NULL;
		ft_init_var_aux_two(sh);
	}
}

void	ft_free_minishell_single_aux(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	ft_free_minishell_double_aux(char **str_double)
{
	long	i;

	if (str_double)
	{
		i = 0;
		while (str_double[i])
		{
			ft_free_minishell_single_aux(str_double[i]);
			str_double[i] = NULL;
			i++;
		}
		free(str_double);
		str_double = NULL;
	}
}

void	ft_free_minishell_close_fd(int *file_fd, long amount_fd)
{
	long	i;

	i = 0;
	if (file_fd && amount_fd != 0)
	{
		if (amount_fd > 1)
			amount_fd = 1;
		while (i < amount_fd)
		{
			if (file_fd[i] != -1)
			{
				if (close(file_fd[i]) == -1)
					g_sig.errnbr = errno;
			}
			i++;
		}
		free(file_fd);
		file_fd = NULL;
	}
}
