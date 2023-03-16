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

//    printf("Dentro da ft_isexec: token: %s ; first: %s ; ft_strchr: %s\n", 
//node->token, node->first_cmd, ft_strchr("/", node->first_cmd[0]));
//        printf("É um executável!!!\n");
//        printf("É um executável!!! %s\n", node->path);
//            printf("Não mallocou!!!\n");
//        printf("node->path: %s\n", node->path);
//        printf("É um binário com endereço absoluto!!!\n");
//        printf("nenhuma das anteriores!!!\n");
//        printf("Verifica se possui acesso!!!\n");
//        printf("node->path: não tem acesso a: %s\n", node->path);
//    printf("node->path:     tem acesso a: %s\n", node->path);

static void	ft_isexec_aux0(t_minishell *sh, t_node *node);
static void	ft_isexec_aux1(t_minishell *sh, t_node *node);
static void	ft_isexec_aux2(t_minishell *sh, t_node *node);

void	ft_isexec(t_minishell *sh, t_node *node)
{
	if (node->first_cmd[0] == '.')
	{
		ft_isexec_aux0(sh, node);
		if (sh->ret < 0)
			return ;
	}
	else if (ft_strchr("/", node->first_cmd[0]))
	{
		ft_isexec_aux1(sh, node);
		if (sh->ret < 0)
			return ;
	}
	else
	{
		ft_isexec_aux2(sh, node);
		if (sh->ret < 0)
			return ;
	}
	if (access(node->path, X_OK | F_OK) == -1)
	{
		sh->ret = -7;
		sh->errnbr = 127;
		sh->erro = node->first_cmd;
	}
}

static void	ft_isexec_aux0(t_minishell *sh, t_node *node)
{
	if ((int)ft_strchr_i(node->token, '/') == -1)
	{
		sh->ret = -4;
		sh->errnbr = 127;
		sh->erro = node->first_cmd;
		return ;
	}
	node->path = ft_substr(node->first_cmd, 0, ft_strlen(node->first_cmd));
	if (!node->path)
	{
		sh->ret = -4;
		sh->errnbr = 127;
		sh->erro = node->first_cmd;
		return ;
	}
}

static void	ft_isexec_aux1(t_minishell *sh, t_node *node)
{
	node->path = ft_substr(node->first_cmd, 0, ft_strlen(node->first_cmd));
	if (!node->path)
	{
		sh->ret = -4;
		sh->errnbr = 127;
		sh->erro = node->first_cmd;
		return ;
	}
}

static void	ft_isexec_aux2(t_minishell *sh, t_node *node)
{
	node->path = ft_access_command(sh, node);
	if (!node->path)
	{
		sh->ret = -4;
		sh->errnbr = 127;
		sh->erro = node->first_cmd;
		return ;
	}
}
