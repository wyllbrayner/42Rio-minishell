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

//    printf("Dentro da ft_isexec: token: %s ; first: %s ; ft_strchr: %s\n", node->token, node->first_cmd, ft_strchr("/", node->first_cmd[0]));
//        printf("É um executável!!!\n");
//        printf("É um executável!!! %s\n", node->path);
//            printf("Não mallocou!!!\n");
//        printf("node->path: %s\n", node->path);
//        printf("É um binário com endereço absoluto!!!\n");
//        printf("nenhuma das anteriores!!!\n");
//        printf("Verifica se possui acesso!!!\n");
//        printf("node->path: não tem acesso a: %s\n", node->path);
//    printf("node->path:     tem acesso a: %s\n", node->path);
void	ft_isexec(t_minishell *sh, t_node *node)
{
	if (node->first_cmd[0] == '.')
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
	else if (ft_strchr("/", node->first_cmd[0]))
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
	else
	{
		node->path = ft_access_command(sh, node);
		sh->tmp1 = NULL;
		if (!node->path)
		{
			sh->ret = -4;
			sh->errnbr = 127;
			sh->erro = node->first_cmd;
			return ;
		}
	}
	if (access(node->path, X_OK | F_OK) == -1)
	{
		sh->ret = -7;
		sh->errnbr = 127;
		sh->erro = node->first_cmd;
		return ;
	}
}
/*
void ft_isexec(t_minishell *sh, t_node *node)
{
    printf("Dentro da ft_isexec: token: %s ; first: %s ; ft_strchr: %s\n", node->token, node->first_cmd, ft_strchr("/", node->first_cmd[0]));
    if (node->first_cmd[0] == '.')
    {
        node->is_exec = 1;
        printf("É um executável!!!\n");
        if ((int)ft_strchr_i(node->token, '/') == -1)
        {
            sh->ret = -8;   //pensar em um código de retorno para isto.
            return ;
        }
        printf("É um executável!!!\n");
        node->path = ft_substr(node->first_cmd, 0, ft_strlen(node->first_cmd));
        if (!node->path)
        {
            printf("Não mallocou!!!\n");
            sh->ret = -3;
            return ;
        }
		if (access(node->path, X_OK | F_OK) == -1)
		{
            printf("node->path: não tem acesso a: %s\n", node->path);
			sh->ret = -7;
			sh->erro = node->first_cmd;
            return ;
		}
        printf("node->path:     tem acesso a: %s\n", node->path);
    }
    else if (ft_strchr("/", node->first_cmd[0]))
    {
        node->is_exec = 2;
        node->path = ft_substr(node->first_cmd, 0, ft_strlen(node->first_cmd));
        printf("node->path: %s\n", node->path);
        printf("É um binário com endereço absoluto!!!\n");
        if (!node->path)
        {
            sh->ret = -3;
            return ;
        }
		if (access(node->path, X_OK | F_OK) == -1)
		{
            printf("node->path: não tem acesso a: %s\n", node->path);
			sh->ret = -7;
			sh->erro = node->first_cmd;
            return ;
		}
        printf("node->path:     tem acesso a: %s\n", node->path);
    }
    else
    {
        node->is_exec = 0;
        printf("nenhuma das anteriores!!!\n");
        printf("Verifica se possui acesso!!!\n");
        node->path = ft_access_command(sh, node);
        sh->tmp1 = NULL;
        if (!node->path)
        {
            printf("node->path: não tem acesso a: %s\n", node->path);
			sh->ret = -7;
			sh->erro = node->first_cmd;
            return ;
        }
        printf("node->path:     tem acesso a: %s\n", node->path);
    }
}
*/
