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
# include <fcntl.h>

# define TRUE 1;
# define FALSE 0;

//# define PATH_MAX 1024;
//# include <linux/limits.h>
//# include <limits.h>
//# include <stdbool.h>

typedef struct doubly_node
{
	char                *token;
	char                **cmd;
	char                *first_cmd;
    int                 is_exec;
	char                *path;
	struct doubly_node	*prev;
	struct doubly_node	*next;
}	t_node;

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
    int     errno;
//    char    *cwd;
//    char    *buff;
    char    **path;
    char    *line;
    char    **env;
    char    **parse_str;
    char    *erro;
    t_node  *head;
    t_node  *node_tmp;
    char    caract[4];
    char    *tmp0;
    char    *tmp1;
    char    *tmp2;
    char    *tmp5;
    char    **tmp3;
    char    **tmp4;
}           t_minishell;

void    rl_replace_line (const char *text, int clear_undo);

void    ft_isexec(t_minishell *sh, t_node *node);
void    ft_valid_redirect(t_minishell *sh);
void    ft_cmd_builder_init_var(char *caract, char *str, long *var);
void    ft_cmd_builder_aux_0(t_minishell *sh, long *i, long *squote, 
                                                                long *dquote);
void    ft_cmd_builder(t_minishell *sh);
int     ft_valid_quote(long squote, long dquote);
void    ft_minishell_error(t_minishell *sh);

void    ft_interpreter(t_minishell *sh);

void    ft_free_minishell(t_minishell *sh, int status);
void    ft_free_minishell_single_aux(char *str);
void    ft_free_minishell_double_aux(char **str_double);
void    ft_valid_redirect_in(t_minishell *sh);
void    ft_valid_redirect_out(t_minishell *sh);

void    ft_variable_expansion(t_minishell *sh);
void    ft_variable_expansion_aux(t_minishell *sh, t_node *no);

void    ft_builtin_exit(t_minishell *sh, t_node *node);
void    ft_builtin_env(t_minishell *sh, t_node *node);
void	ft_builtin_cd(t_minishell *cmd, t_node *node);
///void    ft_builtin_echo(t_minishell *cmd, t_node *node);
int     ft_builtin_echo(char *echo);
void    ft_builtin_pwd(t_minishell *sh);
void    ft_builtin_export(t_minishell *sh, t_node *node);
void    ft_builtin_unset(t_minishell *sh, t_node *node);

void	ft_single_and_double_quotes(t_minishell *sh, t_node *node, char *first, long *status);
void	ft_builtin_cd_aux_2(t_minishell *sh, t_node *node);
void    ft_init_var(t_minishell *sh, char **envp);
void    ft_init_var_aux_one(t_minishell *sh);
void    ft_init_var_aux_two(t_minishell *sh);

void	ft_start_command(t_minishell *sh, int *rato, t_node *node);
void    ft_parse(t_minishell *sh);
void    ft_select_way(t_minishell *sh, t_node *no);
char	*ft_access_command(t_minishell *sh, t_node *node);
//char	*ft_access_command(t_minishell *sh, char *cmd);
//char	*ft_access_command(char *cmd, char **str);

void    ft_unset_aux_1(t_minishell *sh, long *i, long start, long end, long *status);

void    ft_minishell_error(t_minishell *sh);
void    ft_parse_comand_is_valid(t_minishell *sh);

void    ft_list_destroy(t_node **head);
void    ft_list_add_last(t_node **head, t_node *node);
t_node	*ft_node_create(char *cmd);

size_t  ft_strchr_i(const char *str, int c);
size_t  ft_strrchr_i(const char *str, int c);

void    ft_print_list(const t_minishell *sh); // retirar antes de entregar!
void    ft_print_rev_list(const t_minishell *sh); // retirar antes de entregar!

#endif
