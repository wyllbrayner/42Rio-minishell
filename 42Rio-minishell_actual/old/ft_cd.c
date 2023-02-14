/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiniz <jodiniz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:06:38 by jodiniz           #+#    #+#             */
/*   Updated: 2023/01/24 16:06:38 by jodiniz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_minishell.h"

static void	ft_builtin_cd_aux_1(t_minishell *sh, t_node *node);

void	ft_builtin_cd(t_minishell *sh, t_node *node)
{
	long	i;
	int status;
	printf("Dentro da ft_builtin_cd | Início\n");

	i = 0;
	status = TRUE;
	while (node->cmd[i])
		i++;
	printf("Dentro da ft_builtin_cd | i: %ld\n", i);
	if (i >= 3)
	{
//		printf("Dentro da ft_builtin_cd | i: %ld mais de um parâmetro\n", i);
		sh->ret = -9;
		sh->erro = node->cmd[2];	
	}
	else
	{
		ft_single_and_double_quotes(sh, node, "cd ", &status);
		printf("token: %s | cmd[0]: %s | cmd[1]: %s | cmd[2]: %s | status: %i!!!!\n", node->token, node->cmd[0], node->cmd[1], node->cmd[2], status);
/*
//		printf("Dentro da ft_builtin_cd | i: %ld apenas um parâmetro\n", i);
		sh->tmp0 = getcwd(NULL, 0);
//		printf("Dentro da ft_builtin_cd | Apenas um parâmetro | passou da getcwd\n");
		if (!sh->tmp0)
		{
			printf("Dentro da ft_builtin_cd | Apenas um parâmetro | getcwd retornou NULL (%s)\n", sh->tmp0);
			sh->ret = -3;
			return ;
		}
		else
		{

			if (ft_strchr_i(node->token, '$') != 0)
			{
				printf("Dentro da ft_builtin_cd | Apenas um parâmetro | getcwd retornou ponteiro | node->cmd[1][0] é '$'\n");
				// se $OLDPWD, $PWD ou $HOME -> expandir para a variável correspondente!!!
				// else
				// sh->ret = -7;
				// sh->erro = variável correspondente já expandida!!!!!
			}
			if (chdir(node->cmd[1]) == -1)
			{
				printf("Dentro da ft_builtin_cd | Apenas um parâmetro | chdir retornou -1\n");
				sh->ret = -7;
				sh->erro = node->cmd[1];
				sh->errno = 1;
				ft_free_minishell_single_aux(sh->tmp0);
				sh->tmp0 = NULL;
			}
			else
			{
				printf("Dentro da ft_builtin_cd | Apenas um parâmetro | getcwd retornou ponteiro | else final\n");
				sh->tmp1 = ft_strjoin("export OLDPWD=", sh->tmp0);
				if (!sh->tmp1)
				{
					sh->ret = -3;
					ft_free_minishell_single_aux(sh->tmp0);
					sh->tmp0 = NULL;
					return ;
				}
				printf("sh->tmp1 %s\n", sh->tmp1);
				t_node *tmp = ft_node_create(sh->tmp1);
				printf("token:     %s\n", tmp->token);
				printf("first_cmd: %s\n", tmp->first_cmd);
				int i = 0;
				while (tmp->cmd[i])
				{
					printf("cmd[%i]: %s\n", i, tmp->cmd[i]);
					i++;
				}
				ft_free_minishell_single_aux(sh->tmp0);
				sh->tmp0 = NULL;
				ft_free_minishell_single_aux(sh->tmp1);
				sh->tmp1 = NULL;
				ft_builtin_export(sh, tmp);
				ft_list_destroy(&tmp);
				tmp = NULL;

///////////////////////////////////////////////////////////////////

				sh->tmp0 = getcwd(NULL, 0);
				if (!sh->tmp0)
				{
					sh->ret = -3;
					return ;
				}
				printf("sh->tmp0 %s\n", sh->tmp0);
				sh->tmp1 = ft_strjoin("export PWD=", sh->tmp0);
				if (!sh->tmp1)
				{
					sh->ret = -3;
					ft_free_minishell_single_aux(sh->tmp0);
					sh->tmp0 = NULL;
					return ;
				}
				printf("sh->tmp1 %s\n", sh->tmp1);
				tmp = ft_node_create(sh->tmp1);
				printf("token:     %s\n", tmp->token);
				printf("first_cmd: %s\n", tmp->first_cmd);
				i = 0;
				while (tmp->cmd[i])
				{
					printf("cmd[%i]: %s\n", i, tmp->cmd[i]);
					i++;
				}
				ft_free_minishell_single_aux(sh->tmp0);
				sh->tmp0 = NULL;
				ft_free_minishell_single_aux(sh->tmp1);
				sh->tmp1 = NULL;
				ft_builtin_export(sh, tmp);
				ft_list_destroy(&tmp);
				tmp = NULL;
			}
		}
*/
	}
	printf("Dentro da ft_builtin_cd | Fim\n");
}

static void	ft_builtin_cd_aux_1(t_minishell *sh, t_node *node)
{
	printf("Dentro da ft_builtin_cd_aux_1 | inicio\n");
	ft_builtin_cd_aux_2(sh, node);
	if (sh->ret < 0)
		return ;
	printf("Apenas '' token: %s | cmd[0]: %s | cmd[1]: %s | cmd[2]: %s !!!!\n", node->token, node->cmd[0], node->cmd[1], node->cmd[2]);

	ft_variable_expansion_aux(sh, node);
	if (sh->ret < 0)
		return ;				
	printf("Apenas '' %s após expansão de var!!!!\n", node->cmd[1]);
	ft_builtin_cd_aux_2(sh, node);
	if (sh->ret < 0)
		return ;
	printf("Dentro da ft_builtin_cd_aux_1 | Fim\n");
}

void	ft_builtin_cd_aux_2(t_minishell *sh, t_node *node)
{
	printf("Dentro da ft_builtin_cd_aux_2 | inicio\n");

	ft_free_minishell_single_aux(node->token);
	node->token = NULL;
	node->token = sh->tmp1;
	sh->tmp1 = NULL;
	ft_free_minishell_double_aux(node->cmd);
	node->cmd = NULL;
	node->cmd = ft_split(node->token, ' ');
	if (!node->cmd)
	{
		sh->ret = -3;
		return ;						
	}
	printf("Dentro da ft_builtin_cd_aux_2 | Fim\n");
}

/*
void	ft_builtin_cd(t_minishell *sh, t_node *node)
{
	char	*str;
	int 	i;
	char	string[1024];
	int		j;

	j = 0;
	i = 3;
//	str = sh->line;
	str = node->token;
	while (str[i] == ' ')
		i++;
	while(str[i])
	{
		string[j] = str[i];
		j++;
		i++; 
	}
	chdir(string);
}
*/