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

void ft_isexec(t_minishell *sh, t_node *node)
{
    printf("Dentro da ft_isexec: token: %s ; first: %s ; ft_strchr: %s\n", node->token, node->first_cmd, ft_strchr("/", node->first_cmd[0]));
    if (node->first_cmd[0] == '.')
    {
        node->is_exec = 1;
        printf("É um executável!!!\n");
        if ((int)ft_strchr_i(node->token, '/') == -1)
        {
            sh->ret = -20;   //pensar em um código de retorno para isto.
            return ;
        }
        printf("É um executável!!!\n");
        node->path = ft_substr(node->token, 1, (ft_strlen(node->token) - 1));
        if (!node->path)
        {
            printf("Não mallocou!!!\n");
            sh->ret = -3;
            return ;
        }
        int ret = access(node->path, X_OK | F_OK);
		if (ret == -1)
		{
            printf("node->path: access retornou: %i e não tem acesso a: %s\n", ret, node->path);
            sh->ret = -20;   //pensar em um código de retorno para isto.
            return ;
		}
        printf("node->path: access retornou: %i e     tem acesso a: %s\n", ret, node->path);
        printf("É um executável!!!\n");
        printf("node->path: %s\n", node->path);
    }
    else if (ft_strchr("/", node->first_cmd[0]))
    {
        node->is_exec = 2;
        node->path = ft_substr(node->token, 0, ft_strlen(node->token));
        printf("node->path: %s\n", node->path);
        printf("É um binário com end absoluto!!!\n");
        if (!node->path)
        {
            sh->ret = -3;
            return ;
        }
		if (access(node->path, X_OK | F_OK) == -1)
		{
            printf("node->path: não tem acesso a: %s\n", node->path);
            sh->ret = -20;   //pensar em um código de retorno para isto.
            return ;
		}
        printf("node->path:     tem acesso a: %s\n", node->path);
    }
    else
    {
        node->is_exec = 0;
        printf("nenhuma das anteriores!!!\n");
    }
    sh->ret = 0; /// retirar após os testes.
}