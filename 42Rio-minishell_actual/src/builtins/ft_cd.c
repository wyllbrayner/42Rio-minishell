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

//static void	ft_builtin_cd_aux_0(t_minishell *sh, t_node *node, char *str);
//static void	ft_builtin_cd_aux_1(t_minishell *sh, t_node *node);
static void	ft_builtin_cd_aux_3(t_minishell *sh, char *str);
//static void	ft_builtin_cd_aux_3(t_minishell *sh, t_node *node, char *str);
/*
void	ft_builtin_cd(t_minishell *sh, t_node *node)
{
	long	i;
	long	status;
//	printf("Dentro da ft_builtin_cd | Início\n");

	i = 0;
	status = TRUE;
	while (node->cmd[i])
		i++;
//	printf("Dentro da ft_builtin_cd | i: %ld\n", i);
	if (i >= 3)
	{
//		printf("Dentro da ft_builtin_cd | i: %ld mais de um parâmetro\n", i);
		sh->ret = -9;
		sh->erro = node->cmd[2];	
	}
	else
	{
		if (i == 2)
		{
			ft_single_and_double_quotes(sh, node, "cd ", &status);
//			printf("token: %s | cmd[0]: %s | cmd[1]: %s | cmd[2]: %s | status: %i!!!!\n", node->token, node->cmd[0], node->cmd[1], node->cmd[2], status);
		}
		if (status)
		{
			if (i == 1)
			{	
//				printf("Apenas ''!!!!\n");
				ft_builtin_cd_aux_0(sh, node, "cd $HOME");
				if (sh->ret < 0)
					return ;
//				printf("Apenas '' token: %s | cmd[0]: %s | cmd[1]: %s | cmd[2]: %s !!!!\n", node->token, node->cmd[0], node->cmd[1], node->cmd[2]);
			}
			else if (node->cmd[1][0] == '~')
			{
				if (ft_strlen(node->cmd[1]) == 1)
				{
//					printf("Apenas '~'!!!!\n");
					ft_builtin_cd_aux_0(sh, node, "cd $HOME");
					if (sh->ret < 0)
						return ;
//					printf("Apenas '~' token: %s | cmd[0]: %s | cmd[1]: %s | cmd[2]: %s !!!!\n", node->token, node->cmd[0], node->cmd[1], node->cmd[2]);
				}
				else
				{
					sh->tmp5 = ft_substr(node->cmd[1], 1, (ft_strlen(node->cmd[1]) - 1));
//					printf("substr de node->cmd[1]: %s\n", sh->tmp5);
					ft_builtin_cd_aux_0(sh, node, "cd $HOME");
					if (sh->ret < 0)
						return ;
					sh->tmp1 = ft_strjoin(node->token, sh->tmp5);
					ft_free_minishell_single_aux(sh->tmp5);
					sh->tmp5 = NULL;
					ft_builtin_cd_aux_2(sh, node);
//					printf("'~ + alguma coisa' token: %s | cmd[0]: %s | cmd[1]: %s | cmd[2]: %s !!!!\n", node->token, node->cmd[0], node->cmd[1], node->cmd[2]);
				}
			}
			else if (node->cmd[1][0] == '$')
			{
				sh->tmp0 = ft_substr(node->token, 0, ft_strchr_i(node->token, '/'));
				sh->tmp5 = ft_substr(node->cmd[1], ft_strchr_i(node->cmd[1], '/'), (ft_strlen(node->cmd[1]) - ft_strchr_i(node->cmd[1], '/')));
				if (!sh->tmp0 || !sh->tmp5)
				{
					ft_free_minishell_single_aux(sh->tmp0);
					sh->tmp0 = NULL;
					ft_free_minishell_single_aux(sh->tmp5);
					sh->tmp5 = NULL;
					return;
				}
				if (ft_strchr_i(node->cmd[1], '/') == 0)
				{
//					printf("Apenas '$var'!!!!\n");
					ft_builtin_cd_aux_0(sh, node, node->token);
					if (sh->ret < 0)
						return ;
//					printf("Apenas '$var' token: %s | cmd[0]: %s | cmd[1]: %s | cmd[2]: %s !!!!\n", node->token, node->cmd[0], node->cmd[1], node->cmd[2]);
				}
				else
				{
//					printf("Apenas '$var'!!!!\n");
					ft_builtin_cd_aux_0(sh, node, sh->tmp0);
					if (sh->ret < 0)
						return ;
					sh->tmp1 = ft_strjoin(node->token, sh->tmp5);
					ft_builtin_cd_aux_2(sh, node);
//					printf("Apenas '$var' + alguma coisa token: %s | cmd[0]: %s | cmd[1]: %s | cmd[2]: %s !!!!\n", node->token, node->cmd[0], node->cmd[1], node->cmd[2]);
				}
				ft_free_minishell_single_aux(sh->tmp5);
				sh->tmp5 = NULL;
				ft_free_minishell_single_aux(sh->tmp0);
				sh->tmp0 = NULL;
			}
//			printf("tmp0: %s\n", sh->tmp0);
//			printf("tmp1: %s\n", sh->tmp1);
//			printf("tmp2: %s\n", sh->tmp2);
//			printf("tmp5: %s\n", sh->tmp5);
		}
		else
		{
			sh->ret = -7;
			sh->erro = node->cmd[1];
			sh->errno = 1;
		}
		sh->tmp0 = getcwd(NULL, 0);
		if (!sh->tmp0)
		{
//			printf("Dentro da ft_builtin_cd | getcwd retornou NULL (%s)\n", sh->tmp0);
			sh->ret = -3;
			return ;
		}
		else
		{
//			printf("Dentro da ft_builtin_cd | getcwd retornou ponteiro (%s)\n", sh->tmp0);
			if (chdir(node->cmd[1]) == -1)
			{
//				printf("Dentro da ft_builtin_cd | Apenas um parâmetro | chdir retornou -1\n");
				sh->ret = -7;
				sh->erro = node->cmd[1];
				sh->errno = 1;
			}
			else
			{
//				ft_builtin_cd_aux_3(sh, node, "export OLDPWD=");
				ft_builtin_cd_aux_3(sh, "export OLDPWD=");
				if (sh->ret < 0)
					return ;
///////////////////////////////////////////////////////////////////

				sh->tmp0 = getcwd(NULL, 0);
				if (!sh->tmp0)
				{
					sh->ret = -3;
					return ;
				}
//				printf("sh->tmp0 %s\n", sh->tmp0);
//				ft_builtin_cd_aux_3(sh, node, "export PWD=");
				ft_builtin_cd_aux_3(sh, "export PWD=");
				if (sh->ret < 0)
					return ;
			}
		}
	}
//	printf("Dentro da ft_builtin_cd | Fim\n");
}
*/

void	ft_builtin_cd(t_minishell *sh, t_node *node)
{
	long	i;
	long	status;
	printf("Dentro da ft_builtin_cd | Início\n");

	i = 0;
	status = TRUE;
	while (node->cmd[i])
		i++;
//	printf("Dentro da ft_builtin_cd | i: %ld\n", i);
	if (i >= 3)
	{
//		printf("Dentro da ft_builtin_cd | i: %ld mais de um parâmetro\n", i);
		sh->ret = -9;
		sh->erro = node->cmd[2];	
	}
	else
	{
		if (i == 2)
		{
			ft_single_and_double_quotes(sh, node, "cd ", &status);
			printf("token: %s | cmd[0]: %s | cmd[1]: %s | cmd[2]: %s | status: %li!!!!\n", node->token, node->cmd[0], node->cmd[1], node->cmd[2], status);
		}
		if (!status)
		{
			sh->ret = -7;
			sh->erro = node->cmd[1];
			sh->errno = 1;
			return ;
		}
		sh->tmp0 = getcwd(NULL, 0);
		if (!sh->tmp0)
		{
//			printf("Dentro da ft_builtin_cd | getcwd retornou NULL (%s)\n", sh->tmp0);
			sh->ret = -3;
			return ;
		}
		else
		{
//			printf("Dentro da ft_builtin_cd | getcwd retornou ponteiro (%s)\n", sh->tmp0);
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
				ft_builtin_cd_aux_3(sh, "export OLDPWD=");
				if (sh->ret < 0)
					return ;
///////////////////////////////////////////////////////////////////
				sh->tmp0 = getcwd(NULL, 0);
				if (!sh->tmp0)
				{
					sh->ret = -3;
					return ;
				}
//				printf("sh->tmp0 %s\n", sh->tmp0);
				ft_builtin_cd_aux_3(sh, "export PWD=");
				if (sh->ret < 0)
					return ;
			}
		}
	}
	printf("Dentro da ft_builtin_cd | Fim\n");
}

/*
static void	ft_builtin_cd_aux_0(t_minishell *sh, t_node *node, char *str)
{
	sh->tmp1 = ft_strdup(str);
//	printf("Dentro da ft_builtin_cd_aux_0 | inicio\n");
	if (!sh->tmp1)
	{
		sh->ret = -3;
		return ;
	}
	ft_builtin_cd_aux_1(sh, node);
	if (sh->ret < 0)
		return ;
//	printf("Dentro da ft_builtin_cd_aux_0 | Fim\n");
}

static void	ft_builtin_cd_aux_1(t_minishell *sh, t_node *node)
{
//	printf("Dentro da ft_builtin_cd_aux_1 | inicio\n");
	ft_builtin_cd_aux_2(sh, node);
	if (sh->ret < 0)
		return ;
//	printf("token: %s | cmd[0]: %s | cmd[1]: %s | cmd[2]: %s !!!!\n", node->token, node->cmd[0], node->cmd[1], node->cmd[2]);
	ft_variable_expansion_aux(sh, node);
	if (sh->ret < 0)
		return ;				
//	printf("Apenas '' %s após expansão de var!!!!\n", node->cmd[1]);
	ft_builtin_cd_aux_2(sh, node);
//	printf("Dentro da ft_builtin_cd_aux_1 | Fim\n");
}
*/

void	ft_builtin_cd_aux_2(t_minishell *sh, t_node *node)
{
//	printf("Dentro da ft_builtin_cd_aux_2 | inicio\n");

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
	ft_free_minishell_single_aux(node->first_cmd);
	node->first_cmd = NULL;
	node->first_cmd = ft_strdup(node->cmd[0]);
	if (!node->first_cmd)
	{
		sh->ret = -3;
		return ;
	}
//	printf("Dentro da ft_builtin_cd_aux_2 | Fim\n");
}

//static void	ft_builtin_cd_aux_3(t_minishell *sh, t_node *node, char *str)
static void	ft_builtin_cd_aux_3(t_minishell *sh, char *str)
{
				sh->tmp1 = ft_strjoin(str, sh->tmp0);
				if (!sh->tmp1)
				{
					sh->ret = -3;
					ft_free_minishell_single_aux(sh->tmp0);
					sh->tmp0 = NULL;
					return ;
				}
/*
				printf("sh->tmp1 %s\n", sh->tmp1);
*/
				sh->node_tmp = ft_node_create(sh->tmp1);
/*
				printf("token:     %s\n", sh->node_tmp->token);
				printf("first_cmd: %s\n", sh->node_tmp->first_cmd);
				int i = 0;
				while (sh->node_tmp->cmd[i])
				{
					printf("cmd[%i]: %s\n", i, sh->node_tmp->cmd[i]);
					i++;
				}
*/
				ft_free_minishell_single_aux(sh->tmp0);
				sh->tmp0 = NULL;
				ft_free_minishell_single_aux(sh->tmp1);
				sh->tmp1 = NULL;
				ft_builtin_export(sh, sh->node_tmp);
				ft_list_destroy(&sh->node_tmp);
				sh->node_tmp = NULL;
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