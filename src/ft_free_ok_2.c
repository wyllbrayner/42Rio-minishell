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

extern t_minishell	sh;

//	printf("Dentro da ft_free_minishell | inicio errnbr: %i\n", sh->errnbr);
//    	printf("Dentro da ft_free_minishell | dentro do if\n");
//    	printf("Dentro da ft_free_minishell | dentro do if | chama a double 
//para parse_str\n");
//    	printf("Dentro da ft_free_minishell | dentro do if | chama a 
//list_destroy para tmp = sh->head\n");
//	printf("Dentro da ft_free_minishell | intermediário errnbr: %i\n", 
//sh->errnbr);
//    	printf("Dentro da ft_free_minishell | dentro do else | inicio\n");
//	printf("Dentro da ft_free_minishell | fim errnbr: %i\n", sh->errnbr);
void	ft_free_minishell(t_minishell *sh, int status)
{
	t_node	*tmp;

	if (sh && (status == 1))
	{
		ft_free_minishell_single_aux(sh->line);
		sh->line = NULL;
		ft_free_minishell_double_aux(sh->parse_str);
		sh->parse_str = NULL;
		tmp = sh->head;
		ft_list_destroy(&tmp);
		ft_init_var_aux_one(sh);
	}
	if (sh && (status == 2))
	{
		ft_free_minishell_double_aux(sh->env);
		sh->env = NULL;
		ft_free_minishell_double_aux(sh->path);
		sh->path = NULL;
		ft_init_var_aux_two(sh);
	}
}

//	printf("Dentro da ft_single_aux | inicio\n");
//  printf("Dentro da ft_single_aux | dentro do if | libera str 
//%s\n", str);
//  printf("Dentro da ft_single_aux | dentro do if | aponta str para NULL
// %s\n", str);
//  printf("Dentro da ft_single_aux | dentro do if | após apontar str para 
//NULL %s\n", str);
//	printf("Dentro da ft_single_aux | fim\n");
void	ft_free_minishell_single_aux(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

//	printf("Dentro da ft_double_aux | inicio\n");
//  printf("Dentro da ft_double_aux | dentro do if\n");
//  printf("Dentro da ft_double_aux | dentro do if | str_double[0]: %s\n", 
//str_double[0]);
//  printf("Dentro da ft_double_aux | dentro do if | str_double[1]: %s\n", 
//str_double[1]);
// 	printf("Dentro da ft_double_aux | dentro do if | dentro do loop | chama
// a single aux para %s\n", str_double[i]);
//  printf("Dentro da ft_double_aux | dentro do if | libera str_double\n");
//  printf("Dentro da ft_double_aux | dentro do if | aponta str_double para 
//NULL\n");
//	printf("Dentro da ft_double_aux | fim\n");

void	ft_free_minishell_double_aux(char **str_double)
{
	long	i;

	if (str_double)
	{
		i = 0;
		while (str_double[i])
		{
			ft_free_minishell_single_aux(str_double[i]);
			str_double[i] = NULL;
			i++;
		}
		free(str_double);
		str_double = NULL;
	}
}

//  printf("Dentro da ft_free_minishell_close_fd amount_fd: %ld 
//| início\n", amount_fd);
//	printf("Dentro da ft_free_minishell_close_fd | fim\n");
void	ft_free_minishell_close_fd(int *file_fd, long amount_fd)
{
	long	i;

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
		file_fd = NULL;
	}
}
