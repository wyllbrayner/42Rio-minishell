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
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE 1
# define FALSE 0;

///typedef struct  s_control
///{
///    int     running;
///    int     ret;
///}   t_control;

typedef struct  s_minishell
{
///    t_control *control;
    int     ret;
    int     running;
    char    **path;
    char    *line;
    char    **env;
    char    **parse_str;
    char    *tmp1;
}           t_minishell;

void	start_command(t_minishell *sh, int *rato);
char	*access_command(char *cmd, char **str);

void    ft_builtin_exit(t_minishell *sh, long i);
void    ft_builtin_env(t_minishell *sh, long i);
void    ft_builtin_export(t_minishell *sh, long i);

void    ft_minishell_error(t_minishell *sh, char *str);
void    ft_parse(t_minishell *sh);
void    ft_parse_comand_is_valid(t_minishell *sh);

void    ft_free_minishell_single_aux(char *str);
void    ft_free_minishell(t_minishell *sh, int status);

int     ft_print(void);

#endif
