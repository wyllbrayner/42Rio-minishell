/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 09:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2023/03/20 11:03:29 by jodiniz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdbool.h>
# include <dirent.h>
# include <errno.h>
# include <signal.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <termios.h>

# define TRUE 1;
# define FALSE 0;
# define MSGERROR "(Minishell): syntax error near unexpected token `newline'\n"

typedef struct doubly_node
{
	char				*token;
	char				**cmd;
	char				*first_cmd;
	char				*path;
	char				**redirect_file;
	int					*redirect_file_fd;
	int					redirect_file_fd_amount;
	bool				command;
	int					*infile;
	int					*outfile;
	int					*i;
	int					*status;
	struct doubly_node	*prev;
	struct doubly_node	*next;
}	t_node;

typedef struct s_signal
{
	int		s_int;
	int		errnbr;
}	t_signal;

typedef struct s_minishell
{
	int		ret;
	int		running;
	int		bkp_fd_in;
	int		bkp_fd_out;
	char	**path;
	char	*line;
	char	**env;
	char	*erro;
	t_node	*head;
	t_node	*head_tmp;
	char	caract[4];
	char	*tmp0;
	char	*tmp1;
	char	*tmp2;
	char	*tmp5;
	char	**tmp3;
	char	**tmp4;
}			t_minishell;

void	rl_replace_line(const char *text, int clear_undo);
void	ft_isexec(t_minishell *sh, t_node *node);
void	ft_cmd_builder(t_minishell *sh);
void	ft_cmd_builder_init_var(char *caract, char *str, long *var);
void	ft_cmd_builder_aux_0(t_minishell *sh, long *i, long *squote, \
		long *dquote);
void	ft_valid_lexcal_cmd(t_minishell *sh);
void	ft_minishell_error(t_minishell *sh);
void	ft_valid_redirect(t_minishell *sh);
void	ft_valid_redirect_1(t_minishell *sh);
void	ft_redirect_builder(t_minishell *sh);
void	ft_exec_token(t_minishell *sh);
void	ft_heredoc_builder(t_minishell *sh, t_node *node);
void	ft_interpreter(t_minishell *sh, t_node *node);
void	ft_expand_variable(t_minishell *sh, t_node *node);
void	ft_expand_variable_0(t_minishell *sh, t_node *node, long *var);
void	ft_expand_variable_0_aux_04(t_minishell *sh, long *var);
void	ft_expand_variable_0_aux_05(t_minishell *sh);
void	ft_free_minishell(t_minishell *sh, int status);
void	ft_free_minishell_single_aux(char *str);
void	ft_free_minishell_double_aux(char **str_double);
void	ft_free_minishell_close_fd(int *file_fd, long amount_fd);
int		ft_valid_quote(long squote, long dquote);
size_t	ft_strchr_i(const char *str, int c);
void	ft_expander_quote(t_minishell *sh, t_node *node);
void	ft_expand_variable(t_minishell *sh, t_node *node);
void	ft_expander_variable(t_minishell *sh, t_node *node);
void	ft_variable_expansion(t_minishell *sh);
void	ft_builtin_exit(t_minishell *sh, t_node *node);
void	ft_builtin_env(t_minishell *sh, t_node *node);
void	ft_builtin_cd(t_minishell *cmd, t_node *node);
void	ft_builtin_cd_aux_2(t_minishell *sh, t_node *node);
void	ft_builtin_echo(t_node *node);
int		filter_space(char *str);
void	ft_builtin_pwd(t_minishell *sh);
void	ft_builtin_export(t_minishell *sh, t_node *node);
void	ft_builtin_unset(t_minishell *sh, t_node *node);
void	ft_unset_aux_1(t_minishell *sh, long *var);
void	ft_valid_quotes_aux2(t_minishell *sh, t_node *node, long *var);
void	ft_heredoc_fd(t_minishell *sh, t_node *n);
void	ft_single_and_double_quotes(t_minishell *sh, t_node *node, char *first);
void	ft_init_var(t_minishell *sh, char **envp);
void	ft_init_var_aux_one(t_minishell *sh);
void	ft_init_var_aux_two(t_minishell *sh);
void	ft_start_command(t_minishell *sh, t_node *node);
void	ft_parse(t_minishell *sh);
char	*ft_access_command(t_minishell *sh, t_node *node);
void	ft_redirect_2(t_minishell *sh);
void	ft_parse_comand_is_valid(t_minishell *sh);
void	ft_list_destroy(t_node **head);
void	ft_list_add_last(t_node **head, t_node *node);
t_node	*ft_node_create(char *cmd);
void	dup_infile_last(t_node *temp);
void	dup_outfile_last(t_node *temp);
void	verify(t_node *temp, t_minishell *sh);
void	execute_command(int *i, t_node *temp, t_minishell *sh);
void	ft_last(int i, t_node *temp, t_minishell *sh);
void	check_pipe(t_minishell *shell);
int		ft_select_way(t_minishell *sh, t_node *node);
void	organize_command(t_node *temp, char **path);
void	organize_file_out(t_node *temp);
void	organize_file_in(t_node *temp);
int		is_redirect(t_node **temp, bool *redirect);
int		prev_redirect(t_node **temp);
int		file_swap_in(t_node **temp, t_node **find, bool *flag);
int		file_swap_out(t_node **temp, t_node **find, bool *flag);
bool	ft_access(char *cmd, char **path);
void	restore_fd(t_minishell *sh);
void	execute_pipe_command(t_node *temp, t_minishell *sh, int size);
void	ft_init_path(t_minishell *sh);
int		ft_printf(const char *fornat, ...);
void	ft_print_list(const t_node *node);
void	ft_print_rev_list(const t_node *node);
#endif
