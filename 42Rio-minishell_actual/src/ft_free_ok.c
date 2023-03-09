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
// ls > sair1 | cat Makefile | exit 100 | echo retorno da execução $? .
void ft_free_minishell(t_minishell *sh, int status)
{
    t_node *tmp;

//	printf("Dentro da ft_free_minishell | inicio errnbr: %i\n", sh->errnbr);
    if (sh && (status == 1))
    {
//    	printf("Dentro da ft_free_minishell | dentro do if\n");
        ft_free_minishell_single_aux(sh->line);
        sh->line = NULL;
//    	printf("Dentro da ft_free_minishell | dentro do if | chama a double para parse_str\n");
        ft_free_minishell_double_aux(sh->parse_str);
        sh->parse_str = NULL;
//    	printf("Dentro da ft_free_minishell | dentro do if | chama a list_destroy para tmp = sh->head\n");
        tmp = sh->head;
        ft_list_destroy(&tmp);
//	printf("Dentro da ft_free_minishell | intermediário errnbr: %i\n", sh->errnbr);
        ft_init_var_aux_one(sh);
    }
    if (sh && (status == 2))
    {
//    	printf("Dentro da ft_free_minishell | dentro do else | inicio\n");
        ft_free_minishell_double_aux(sh->env);
        sh->env = NULL;
        ft_free_minishell_double_aux(sh->path);
        sh->path = NULL;
        ft_init_var_aux_two(sh);
    }
//	printf("Dentro da ft_free_minishell | fim errnbr: %i\n", sh->errnbr);
}

extern t_minishell sh;
void ft_free_minishell_single_aux(char *str)
{
//	printf("Dentro da ft_single_aux | inicio\n");
    if (str)
    {
//      	printf("Dentro da ft_single_aux | dentro do if | libera str %s\n", str);
        free(str);
//        sh.errnbr = errno;
//     	printf("Dentro da ft_single_aux | dentro do if | aponta str para NULL %s\n", str);
        str = NULL;

//      	printf("Dentro da ft_single_aux | dentro do if | após apontar str para NULL %s\n", str);
    }
//	printf("Dentro da ft_single_aux | fim\n");
}

void ft_free_minishell_double_aux(char **str_double)
{
//	printf("Dentro da ft_double_aux | inicio\n");
    long    i;

    if (str_double)
    {
        i = 0;
//    	printf("Dentro da ft_double_aux | dentro do if\n");
//    	printf("Dentro da ft_double_aux | dentro do if | str_double[0]: %s\n", str_double[0]);
//    	printf("Dentro da ft_double_aux | dentro do if | str_double[1]: %s\n", str_double[1]);
        while (str_double[i])
        {
//        	printf("Dentro da ft_double_aux | dentro do if | dentro do loop | chama a single aux para %s\n", str_double[i]);
            ft_free_minishell_single_aux(str_double[i]);
            str_double[i] = NULL;
            i++;
        }
//     	printf("Dentro da ft_double_aux | dentro do if | libera str_double\n");
        free(str_double);
//        sh.errnbr = errno;
//     	printf("Dentro da ft_double_aux | dentro do if | aponta str_double para NULL\n");
        str_double = NULL;
    }
//	printf("Dentro da ft_double_aux | fim\n");
}

void ft_free_minishell_close_fd(int *file_fd, long amount_fd)
{
        long i;
//        printf("Dentro da ft_free_minishell_close_fd amount_fd: %ld | início\n", amount_fd);

        i = 0;
        if (file_fd && amount_fd != 0)
        {
                if (amount_fd > 1)
                        amount_fd = 1;
                while (i < amount_fd)
                {
                        if (file_fd[i] != -1)
                        {
                            if (close(file_fd[i]) == -1)
                                    sh.errnbr = errno;
                        }
                        i++;
                }
                free(file_fd);
//                sh.errnbr = errno;
                file_fd = NULL;
        }
//	printf("Dentro da ft_free_minishell_close_fd | fim\n");
}

/*
void ft_free_minishell_close_fd(int *file_fd, long amount_fd)
{
        long i;
        printf("Dentro da ft_free_minishell_close_fd amount_fd: %ld | início\n", amount_fd);

        i = 0;
        if (file_fd && amount_fd != 0)
        {
                while (i < amount_fd)
                {
                        if (file_fd[i] != -1)
                        {
                            close(file_fd[i]);
                            sh.errnbr = errno;
                        }
                        i++;
                }
                free(file_fd);
                sh.errnbr = errno;
                file_fd = NULL;
        }
	printf("Dentro da ft_free_minishell_close_fd | fim\n");
}
*/
