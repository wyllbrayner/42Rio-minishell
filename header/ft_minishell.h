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
//# include <readline/history.h>

# define TRUE 1
# define FALSE 0;

typedef struct  ft_minishell
{
    int     running;
    int     ret;
    char    **path;
    char    *pwd;
    char    *line;
    char    **env;
    char    **parse_str;
}           t_minishell;

void	start_command(t_minishell *sh, int *rato);
char	*access_command(char *cmd, char **str);

void    ft_builtin_exit(t_minishell *sh, long i);

void    ft_minishell_error(t_minishell *sh, char *str);

void    ft_free_minishell_single_aux(char *str);
void    ft_free_minishell(t_minishell *sh, int status);

int     ft_print(void);

#endif
