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

/*
void    ft_init_var(t_minishell *sh, char **envp)
{
    long    i;

    if (sh && envp)
    {
        i = 0;
        sh->ret = 0;
        sh->out_redirect = 0;
        sh->out_redirect_file = NULL;
        sh->out_redirect_file_fd = NULL;
        sh->out_redirect_file_fd_amount = 0;
        sh->in_redirect = 0;
        sh->in_redirect_file = NULL;
        sh->in_redirect_file_fd = NULL;
        sh->in_redirect_file_fd_amount = 0;
        sh->running = TRUE;
        sh->s_int = FALSE;
//        sh->cwd = NULL;
//        sh->buff[1024];
        sh->path = NULL;
        sh->line = NULL;
        sh->env = NULL;
        sh->parse_str = NULL;
        sh->erro = NULL;
        sh->head = NULL;
        sh->tmp1 = NULL;
        sh->tmp2 = NULL;
        sh->tmp3 = NULL;
        sh->tmp4 = NULL;
        while (envp[i])
            i++;
        sh->env = (char **)malloc(sizeof(char *) * (++i));
        if (!sh->env)
            sh->ret = -3;
        else
        {
            --i;
            sh->env[i] = NULL;
            while ((--i >= 0) && (sh->ret == 0))
            {
                sh->env[i] = ft_strdup(envp[i]);
                if (!sh->env[i])
                    sh->ret = -3;
                else
                {
                    if (ft_strncmp(sh->env[i], "PATH", 4) == 0)
                    {
                        sh->path = ft_split(sh->env[i] + 5, ':');
                        if (!sh->path)
                            sh->ret = -3;
                    }
                }
            }
        }
    }
    else
        sh->ret = -1;
}
*/


