/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 09:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/29 17:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <linux/limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

# define T 1;
# define F 0;

typedef struct  s_minishell
{
    int     ret;
    int     out_redirect;
    char    **out_redirect_file;
    int     *out_redirect_file_fd;
    long    out_redirect_file_fd_amount;
    int     in_redirect;
    char    **in_redirect_file;
    int     *in_redirect_file_fd;
    long    in_redirect_file_fd_amount;
    int     running;
    int     s_int;
    char    **path;
    char    *line;
    char    **env;
    char    **parse_str;
    char    *erro;
    char    *tmp1;
}           t_minishell;

//extern t_minishell	sh;

void	ft_start_command(t_minishell *sh, int *rato);
char	*ft_access_command(char *cmd, char **str);

void    ft_builtin_exit(t_minishell *sh);
void    ft_builtin_env(t_minishell *sh);

void    ft_minishell_error(t_minishell *sh);
void    ft_select_way(t_minishell *sh);
void    ft_parse(t_minishell *sh);
void    ft_parse_comand_is_valid(t_minishell *sh);

void    ft_free_minishell_single_aux(char *str);
void    ft_free_minishell_double_aux(char **str_double);
void    ft_free_minishell(t_minishell *sh, int status);

int     ft_print(void);

#endif