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

char	*access_command(char *cmd, char **str)
{
	char	*tmp;
	char	*com;
	while(*str)
	{
		tmp = ft_strjoin(*str, "/");
		com = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(com, X_OK | F_OK) == 0)
		{
			return (com);
		}
		free(com);
		str++;
	}
	return(0);
}

void	start_command(t_minishell *sh, int *rato)
{
	//int	pid;
	char 	*tmp;
	
	tmp = access_command(sh->parse_str[0], sh->path);
	if (!tmp)
	{
		printf("Command not found\n");
	}
	else
	{
		*rato = fork();
		if (*rato == 0)
		{
			printf("Startou filho\n");
			execve(tmp, &sh->parse_str[0], NULL);
		}
		printf("pai continuou\n");
		// waitpid(pid, NULL, 0);
	}
	free(tmp);
}
/*
void	start_command(t_minishell *sh, int *rato)
{
	// int	pid;
	char 	*tmp;
	char	*i;
	
	tmp = access_command(sh->parse_str[0], sh->path);
	i = tmp;
	free(tmp);
	tmp = i;
	if (!tmp)
	{
		printf("Command not found\n");
	}
	else
	{
		*rato = fork();
		if (*rato == 0)
		{
			printf("Startou filho\n");
			execve(tmp, &sh->parse_str[0], NULL);
		}
		printf("pai continuou\n");
		// waitpid(pid, NULL, 0);
	}	
}
*/