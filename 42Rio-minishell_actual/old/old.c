/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

//void new_line_handler(void)
//{
//    printf("New Line created\n");
//}
//new_line_handler(); // na main!!

/*
void ft_sigint_handler(int sig)
{
    sh.s_int = 1;
    write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
*/

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
