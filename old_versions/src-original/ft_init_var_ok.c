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

static void    ft_init_var_aux_env(t_minishell *sh, char **envp, long i);

void    ft_init_var(t_minishell *sh, char **envp)
{
    long    i;

    if (sh && envp)
    {
        ft_init_var_aux_one(sh);
        ft_init_var_aux_two(sh);
        i = 0;
        while (envp[i])
            i++;
        sh->env = (char **)malloc(sizeof(char *) * (++i));
        if (!sh->env)
        {
            sh->errnbr = errno;
            sh->ret = -3;
        }
        else
            ft_init_var_aux_env(sh, envp, i);
    }
    else
        sh->ret = -1;
}

void    ft_init_var_aux_one(t_minishell *sh)
{
//    printf("Dentro da init_var_aux_one ret: %i \n", sh->ret);
    sh->ret = 0;
    sh->line = NULL;
    sh->parse_str = NULL;
    sh->erro = NULL;
    sh->head = NULL;
    sh->head_tmp = NULL;
    ft_bzero(sh->caract, (sizeof(char) * 4));
    sh->tmp0 = NULL;
    sh->tmp1 = NULL;
    sh->tmp2 = NULL;
    sh->tmp3 = NULL;
    sh->tmp4 = NULL;
    sh->tmp5 = NULL;
    sh->s_int = TRUE;
}

void    ft_init_var_aux_two(t_minishell *sh)
{
//    printf("Dentro da init_var_aux_two \n");
//        sh->cwd = NULL;
        sh->running = TRUE;
        sh->env = NULL;
        sh->path = NULL;
        sh->errnbr = 0;
//        sh->errno = -42; /// retirar antes de entregar ou após mapear os códigos e saída
//    printf("Dentro da init_var_aux_two errnbr: %i\n", sh->errnbr);
}

static void    ft_init_var_aux_env(t_minishell *sh, char **envp, long i)
{
    --i;
    sh->env[i] = NULL;
    while ((--i >= 0) && (sh->ret == 0))
    {
        sh->env[i] = ft_strdup(envp[i]);
        if (!sh->env[i])
        {
            sh->errnbr = errno;
            sh->ret = -3;
            return ;
        }
//        printf("Dentro da init_var_aux_env: env[%ld]: %s\n", i, sh->env[i]);
    }
}

/*
static void    ft_init_var_aux_env(t_minishell *sh, char **envp, long i)
{
    --i;
    sh->env[i] = NULL;
    while ((--i >= 0) && (sh->ret == 0))
    {
        sh->env[i] = ft_strdup(envp[i]);
        if (!sh->env[i])
        {
            sh->ret = -3;
            return ;
        }
        /// realocar essa parte para a função acesse
        else
        {
            if (ft_strncmp(sh->env[i], "PATH", 4) == 0)
            {
                sh->path = ft_split(sh->env[i] + 5, ':');
                if (!sh->path)
                {
                    sh->ret = -3;
                    return ;
                }
            }
        }
    }
}
*/
