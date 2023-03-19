/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_j.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiniz <jodiniz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:42:51 by jodiniz           #+#    #+#             */
/*   Updated: 2023/03/16 17:41:55 by jodiniz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

void	restore_fd(t_minishell *sh)
{
	dup2(sh->bkp_fd_in, 0);
	dup2(sh->bkp_fd_out, 1);
}

bool	ft_access(char *cmd, char **path)
{
	char	*tmp;
	char	*com;

	if (cmd && path)
	{
		while (*path)
		{
			tmp = ft_strjoin(*path, "/");
			com = ft_strjoin(tmp, cmd);
			free(tmp);
			if (access(com, X_OK | F_OK) == 0)
			{
				free(com);
				return (1);
			}
			free(com);
			path++;
		}
	}
	return (0);
}

int	file_swap_in(t_node **temp, t_node **find, bool *flag)
{
	if ((*find)->prev)
		*find = (*find)->prev;
	else
		return (1);
	while (*find)
	{
		if ((*find)->first_cmd[0] == '|' || (*find)->prev == NULL)
		{
			*flag = 1;
			break ;
		}
		if ((*find)->first_cmd[0] == '<' && (*find)->next)
		{
			(*temp)->infile = (*find)->next->redirect_file_fd;
			*flag = 1;
			break ;
		}
		*find = (*find)->prev;
	}
	return (0);
}

int	file_swap_out(t_node **temp, t_node **find, bool *flag)
{
	if ((*find)->prev)
		*find = (*find)->prev;
	else
		return (1);
	while (*find)
	{
		if ((*find)->first_cmd[0] == '|' || (*find)->prev == NULL)
		{
			*flag = 1;
			break ;
		}
		if ((*find)->first_cmd[0] == '>' && (*find)->next)
		{
			(*temp)->outfile = (*find)->next->redirect_file_fd;
			*flag = 1;
			break ;
		}
		*find = (*find)->prev;
	}
	return (0);
}
