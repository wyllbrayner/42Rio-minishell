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
# include "get_next_line.h"
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>

# define TRUE 1;
# define FALSE 0;
# define MSGERROR "(Minishell): syntax error near unexpected token `newline'\n"

typedef struct doubly_node
{
	char                *token;
	char                **cmd;
	char                *first_cmd;
	char                *path;
    char                **redirect_file;
    int                 *redirect_file_fd;
    int                 redirect_file_fd_amount;
    bool                command; //novo
    int                 *infile; //novo
    int                 *outfile;//novo
    int                 *i;      //novo
    int                 *status; //novo
	struct doubly_node	*prev;
	struct doubly_node	*next;
}	t_node;

typedef struct s_signal
{
    int     s_int; //one
    int     errnbr; //two
} t_signal;

typedef struct  s_minishell
{
    int     ret; //one
    int     running; //two
//    int     s_int; //one aqui
//    int     errnbr; //two aqui
    int     bkp_fd_in; // two
    int     bkp_fd_out;// two
//    char    *cwd;
    char    **path; //two
    char    *line; //one
    char    **env; //two
    char    *erro; //one
    t_node  *head; //one
    t_node  *head_tmp; //one
    char    caract[4]; //one
    char    *tmp0; //one
    char    *tmp1; //one
    char    *tmp2; //one
    char    *tmp5; //one
    char    **tmp3; //one
    char    **tmp4; //one
}           t_minishell;

void    rl_replace_line (const char *text, int clear_undo);

void    ft_isexec(t_minishell *sh, t_node *node);


void    ft_cmd_builder(t_minishell *sh);
void    ft_cmd_builder_init_var(char *caract, char *str, long *var); //ok
void    ft_cmd_builder_aux_0(t_minishell *sh, long *i, long *squote, 
                                                                long *dquote);
void    ft_valid_lexcal_cmd(t_minishell *sh);
void    ft_minishell_error(t_minishell *sh); //ok
void    ft_valid_redirect(t_minishell *sh);  //ok
void    ft_valid_redirect_1(t_minishell *sh); //ok
void    ft_redirect_builder(t_minishell *sh);
void	ft_exec_token(t_minishell *sh);

void    ft_heredoc_builder(t_minishell *sh, t_node *node); //ok
void    ft_interpreter(t_minishell *sh, t_node *node);

void	ft_expand_variable(t_minishell *sh, t_node *node);
void	ft_expand_variable_0(t_minishell *sh, t_node *node, long *var);
void	ft_expand_variable_0_aux_04(t_minishell *sh, long *var);
void	ft_expand_variable_0_aux_05(t_minishell *sh);

void    ft_free_minishell(t_minishell *sh, int status); //ok
void    ft_free_minishell_single_aux(char *str); //ok
void    ft_free_minishell_double_aux(char **str_double); //ok
void    ft_free_minishell_close_fd(int *file_fd, long amount_fd); //ok

int     ft_valid_quote(long squote, long dquote); //ok
size_t  ft_strchr_i(const char *str, int c); //ok

void    ft_expander_quote(t_minishell *sh, t_node *node);
void    ft_expand_variable(t_minishell *sh, t_node *node);
void    ft_expander_variable(t_minishell *sh, t_node *node);
void    ft_variable_expansion(t_minishell *sh);

void    ft_builtin_exit(t_minishell *sh, t_node *node);
void    ft_builtin_env(t_minishell *sh, t_node *node);
void	ft_builtin_cd(t_minishell *cmd, t_node *node);
void	ft_builtin_cd_aux_2(t_minishell *sh, t_node *node); //ok
void    ft_builtin_echo(t_node *node);
int     filter_space(char *str);
void    ft_builtin_pwd(t_minishell *sh);
void    ft_builtin_export(t_minishell *sh, t_node *node);
void    ft_builtin_unset(t_minishell *sh, t_node *node);
void    ft_unset_aux_1(t_minishell *sh, long *var);

void	ft_valid_quotes_aux2(t_minishell *sh, t_node *node, long *var);

void	ft_heredoc_fd(t_minishell *sh, t_node *n);
void	ft_single_and_double_quotes(t_minishell *sh, t_node *node, char *first);
void    ft_init_var(t_minishell *sh, char **envp);//ok
void    ft_init_var_aux_one(t_minishell *sh); //ok
void    ft_init_var_aux_two(t_minishell *sh); //ok

void	ft_start_command(t_minishell *sh, int *rato, t_node *node);
void    ft_parse(t_minishell *sh);
char	*ft_access_command(t_minishell *sh, t_node *node);

void    ft_redirect_2(t_minishell *sh);
void    ft_parse_comand_is_valid(t_minishell *sh);
void    ft_list_destroy(t_node **head); //ok
void    ft_list_add_last(t_node **head, t_node *node); //ok
t_node	*ft_node_create(char *cmd); //ok


int		ft_printf(const char *fornat, ...);

void    ft_print_list(const t_node *node); // retirar antes de entregar!
void    ft_print_rev_list(const t_node *node); // retirar antes de entregar!

#endif
