/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiniz <jodiniz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:23:51 by jodiniz           #+#    #+#             */
/*   Updated: 2023/01/17 16:51:07 by jodiniz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

char	*ft_access_command(char *cmd, char **path)
{
	char	*tmp;
	char	*com;

	if (cmd && path)
	{
		while(*path)
		{
			tmp = ft_strjoin(*path, "/");
			com = ft_strjoin(tmp, cmd);
			free(tmp);
			if (access(com, X_OK | F_OK) == 0)
				return (com);
			free(com);
			path++;
		}
	}
	return(0);
}

void	ft_start_command(t_minishell *sh, int *rato, t_node *node)
{
	//int	pid;
	char 	*tmp;

	if (sh && rato)
	{
		tmp = ft_access_command(node->first_cmd, sh->path);
		if (!tmp)
		{
			sh->ret = -4;
			sh->erro = node->first_cmd;
			ft_minishell_error(sh);
			return ;
		}
		else
		{
			*rato = fork();
			if (*rato == 0)
			{
				execve(tmp, node->cmd, sh->env);
			}
			// waitpid(pid, NULL, 0);
		}
		ft_free_minishell_single_aux(tmp);
	}
}
