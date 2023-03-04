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

void ft_free_minishell(t_minishell *sh, int status)
{
    t_node *tmp;

//	printf("Dentro da ft_free_minishell | inicio\n");
    if (sh && (status == 1))
    {
//    	printf("Dentro da ft_free_minishell | dentro do if\n");
        tmp = sh->head;
        ft_free_minishell_single_aux(sh->line);
        sh->line = NULL;
// NÃO APAGAR!! retirar o comentário a partir de recolocar a readline ft_free_minishell_single_aux(sh->line); // NÂO APAGAR
//    	printf("Dentro da ft_free_minishell | dentro do if | chama a double para parse_str\n");
        ft_free_minishell_double_aux(sh->parse_str);
        sh->parse_str = NULL;
//    	printf("Dentro da ft_free_minishell | dentro do if | chama a double para out_redirect\n");
        ft_free_minishell_double_aux(sh->out_redirect_file);
        sh->out_redirect_file = NULL;
//    	printf("Dentro da ft_free_minishell | dentro do if | chama a close_fd para out_redirect_file_fd\n");
        ft_free_minishell_close_fd(sh->out_redirect_file_fd, sh->out_redirect_file_fd_amount);
        sh->out_redirect_file_fd = NULL;
//    	printf("Dentro da ft_free_minishell | dentro do if | chama a double para in_redirect\n");
        ft_free_minishell_double_aux(sh->in_redirect_file);
        sh->in_redirect_file = NULL;
//    	printf("Dentro da ft_free_minishell | dentro do if | chama a close_fd para in_redirect_file_fd\n");
        ft_free_minishell_close_fd(sh->in_redirect_file_fd, sh->in_redirect_file_fd_amount);
        sh->in_redirect_file_fd = NULL;
//    	printf("Dentro da ft_free_minishell | dentro do if | chama a list_destroy para tmp = sh->head\n");
        ft_list_destroy(&tmp);
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
//	printf("Dentro da ft_free_minishell | fim\n");
}

void ft_free_minishell_single_aux(char *str)
{
//	printf("Dentro da ft_single_aux | inicio\n");
    if (str)
    {
//      	printf("Dentro da ft_single_aux | dentro do if | libera str %s\n", str);
        free(str);
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
//     	printf("Dentro da ft_double_aux | dentro do if | aponta str_double para NULL\n");
        str_double = NULL;
    }
//	printf("Dentro da ft_double_aux | fim\n");
}

void ft_free_minishell_close_fd(int *file_fd, long amount_fd)
{
    long i;

    i = 0;
    if (file_fd)
    {
        while (i < amount_fd)
        {
            close(file_fd[i]);
            i++;
        }
        free(file_fd);
        file_fd = NULL;
    }
}
