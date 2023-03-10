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

static void    ft_init_path(t_minishell *sh)
{
	long i;

	i = 0;
	while (sh->env[i])
	{
        if (ft_strncmp(sh->env[i], "PATH", 4) == 0)
        {
            sh->path = ft_split(sh->env[i] + 5, ':');
            if (!sh->path)
            {
                sh->ret = -3;
				sh->errnbr = errno;
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
		while(sh->path[i])
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
	return(0);
}

void	ft_start_command(t_minishell *sh, int *rato, t_node *node)
{
//	printf("Dentro da ft_start_command - Início\n");
	if (sh && rato)
	{
		ft_init_path(sh);
		if (sh->ret < 0)
			return ;
		ft_isexec(sh, node);
		ft_free_minishell_double_aux(sh->path);
		sh->path = NULL;
		if (sh->ret < 0)
			return;
		else
		{
	        sh->errnbr = 0;
			*rato = fork();
			if (*rato == 0)
			{
//				printf("Dentro da ft_start_command - Entrou no filho\n");
				if (execve(node->path, node->cmd, sh->env) == -1)
				{
//					printf("Dentro da ft_start_command - Erro na execve\n");
					sh->errnbr = errno;
				}
			}
			else
			{
//				printf("Dentro da ft_start_command - Entrou no pai\n");
				waitpid(*rato, NULL, 0);
//				printf("Dentro da ft_start_command - Saiu   do pai\n");
			}
			// waitpid(pid, NULL, 0);
		}
	}
//	printf("Dentro da ft_start_command - Fim\n");
}
/*
ls
cd
pwd
echo vamos expandir os retornos $?
cd $OLDPWD
echo vamos expandir os retornos $?
ls
echo vamos expandir os retornos $?
cd srs
echo vamos expandir os retornos $?
lss
echo vamos expandir os retornos $?
echo vamos expandir os retornos $?
ll | echo vamos expandir os retornos $? | echo vamos expandir os retornos $?
ls
cat Makefile
echo vamos expandir os retornos $?
cat Makefil
echo vamos expandir os retornos $?
exit







*/

/*
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

*/
