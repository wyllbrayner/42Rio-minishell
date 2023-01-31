/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:13:24 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/19 19:32:22 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H

/**************************************************************************** #
#                               INCLUDES                                      #
# ****************************************************************************/

// libft
# include           "1_libft/srcs/libft.h"
# include           <errno.h>

/**************************************************************************** #
#                                DESIGN                                       #
# ****************************************************************************/

# define YELLOW "\001\033[0;33m\002"
# define BOLD_YELLOW "\001\033[1;33m\002"
# define BLUE "\001\033[0;34m\002"
# define BOLD_BLUE "\001\033[1;34m\002"
# define BOLD_CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[0;37m\002"
# define BOLD_WHITE "\001\033[1;37m\002"
# define END_COLOR "\001\033[0m\002"

# define SHELL_NAME "miniheaven ▸ "
# define SHELL SHELL_NAME

/**************************************************************************** #
#                              CONSTANTS                                      #
# ****************************************************************************/

// tokens
# define T_CONNECTOR        "__[BANANA0]__"
# define T_CONNECTOR_AND    "__[BANANA1]__"
# define T_CONNECTOR_OR     "__[BANANA12]__"
# define T_PIPE             "__[BANANA2]__"
# define T_SPACE            "__[BANANA3]__"
# define T_WILDCARD         "__[BANANA4]__"
# define T_SUBSHELL         "__[BANANA5]__"

//<<
# define T_HEREDOC              "__[BANANA6]__"

//<
# define T_INPUT              "__[BANANA7]__"

//>
# define T_OUTPUT1          "__[BANANA8]__"

//>>
# define T_OUTPUT2          "__[BANANA9]__"

// (
# define T_LEFTP            "__[BANANA10]__"

// )
# define T_RIGHTP           "__[BANANA11]__"

// &
# define T_E_COMER          "__[BANANA12]__"

// |
# define T_PIPE2            "__[BANANA13]__"

# define T_JOKER            "__[22]__"
# define T_JOKER2            "__[2222]__"
# define T_SH				"#!/bin/sh"

# define T_EXIT_CODE		"___GANDOLF___"

// exit
# define EXIT_LIMIT			9223372036854775807

// all errors
# define E_CMDNOTFOUND ": command not found"
# define E_BADSINTAX " syntax error near unexpected token "
# define E_NOTDIR ": No such file or directory\n"
# define E_ISDIR ": Is a directory\n"
# define E_ACCESS ": Permission denied\n"

// // cd errors
// # define EACCES "cd: permission denied\n"
// # define ELOOP "cd: %s: too many levels of symbolic links\n"
// # define ENAMETOOLONG "cd: file name too long\n"
// # define ENOENT "cd: no such file or directory\n"
// # define ENOTDIR "cd: not a directory\n"
# define EHNOTSET "miniheaven: cd: HOME not set\n"

// // unset errors
// # define EINVAL "unset: %s: invalid parameter name"

// // export errors
// # define EXINVAL "export: %s: not a valid identifier"

// // exit errors
// # define NUMERIC_ARG ": numeric argument required\n"
// # define MANY_ARG "exit: too many arguments\n"

// here_doc errors
# define CTRL_D_HD "bash: warning: here-document \
at line 5 delimited by end-of-file (wanted `FIM')\n"

/**************************************************************************** #
#                                STRUCTS                                      #
# ****************************************************************************/

typedef struct s_prompt		t_p;
typedef struct s_str_subs	t_ssub;
typedef struct s_minishell	t_ms;

// Global points to ms struct, so we can easily free ms when signal is called
extern t_ms					*g_ms;

typedef struct s_parse_subshell
{
	int		index;
	int		start;
	int		end;
	int		r_leftp;
	int		r_rightp;
	char	*str;
	int		save_subshell;
	t_ssub	*ssub;
	t_ssub	*head;
	t_p		*curr_p;
	int		n_subs;
	int		i_subs;
}	t_psub;

typedef struct s_str_subs
{
	int					index;
	struct s_str_subs	*prev;
	char				*str;
	struct s_str_subs	*next;
}	t_ssub;

typedef struct s_file
{
	char			*name;
	int				cursor;
	struct s_file	*next;
	struct s_file	*prev;
}	t_file;

typedef struct s_free
{
	int				index;
	char			*buffer;
	struct s_free	*prev;
	struct s_free	*next;
}	t_free;

typedef struct s_sc
{
	int	cat_ls;
	int	reset_fd;
	int	cat;
	int	ls;
}	t_sc;

typedef struct s_qs
{
	struct s_free	*free_qs;
	void			*vt;
	void			*v3;
	void			*vr;
	void			*vl;
	int				last;
	int				mid;
	void			*v;
	int				size;
	int				left;
	int				right;
}	t_qs;

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
	struct s_env			*prev;
}	t_env;

typedef struct s_history
{
	int						index;
	char					*line;
	struct s_history		*next;
	struct s_history		*prev;
	int						l_c_exit_code;
}	t_history;

typedef struct s_cmd
{
	int						index;
	struct s_cmd			*prev;
	struct s_cmd			*next;
	char					*cmd_line;
	char					*cmd_line_pre_cat;
	char					**cmd_splited_by_space;
	int						args_amount;
	char					*just_name;
	char					*path_and_name;
	int						exit_code;
	int						can_execute;
	int						subshell;
	int						input_fd;
	int						output_fd;
	int						type;
	char					*symbol_path;
	char					*input_path;						
	char					*output_path;
	char					*hd_limiter;
	struct s_prompt			*my_prompt;
	int						pipe[2];
	int						redirect;
	int						pre_cat;
	int						only_here_doc;
	int						only_input_redirected_to_file;
}	t_cmd;

typedef struct s_prompt
{
	struct s_prompt			*prev;
	struct s_prompt			*next;
	int						has_here_doc;
	int						pipe_here_doc[2];
	char					*hd_limiter;
	int						input_fd;
	char					*input_path;
	int						input_redirected_to_file;
	int						no_cmd_just_redirect;
	int						dont_execute_first;
	int						output_fd;
	char					*output_path;
	int						redirect;
	int						n_cmds;
	t_cmd					*cmds;
	int						aux_fd;
	char					*this_p_line;
	char					**this_p_line_splited_by_pipe;
	int						args_amount;
	int						mtx_free;
	t_sc					*sc;
	struct s_minishell		*ms;
	struct s_minishell		*subs;
	int						n_subs;
	int						i_subs;
	int						exit_code;
	int						index;
}	t_p;

typedef struct s_minishell
{
	int						index;
	int						argc;
	char					**argv;
	char					**envp;
	int						*connectors_order;
	int						connectors_index;
	int						connectors_amount;
	char					*shell_line;
	char					*shell_line_tokenized;
	char					**slt_splited_by_connectors;
	char					*sh_name;
	int						hdoc;
	char					*readline_var;
	int						p_amount;
	int						has_double_quotes;
	int						has_single_quotes;
	t_p						*p;
	int						exit_code;
	int						history_i;
	t_history				*history;
	t_env					*envs;
	t_env					*aux_envs;
	int						is_aux_env;
	char					*tmp;
	char					*tmp2;
	char					*tmp3;
	char					**dolar_cmd;
	int						*i_dolar_cmd;
	char					*aux;
	int						i;
	char					**str_export;
	t_qs					*qs;
	int						here_doc_open;
	int						here_document;
	int						pipe_here_doc[2];
	int						*input_shortcut;
	int						hd_pipe[2];
	int						input_command_open;
	int						is_cat_sequence;
	int						fake_cat_input;
	int						no_path;
	int						n_threats;
	int						exit;
	int						breakline;
	int						force_stop;
}	t_ms;

/**************************************************************************** #
#                             PROTOTYPES                                      #
# ****************************************************************************/

/* design */
void		print_banner(void);
char		*ms_print_sh_name(void);

/* init */
void		ms_init(t_ms *ms, int argc, char **argv, char **envp);

// env
void		ms_init_env(t_ms *ms);
void		ms_add_env(t_env **env, char *key, char *value);
int			ms_delete_env(t_env **envs, char *key);
char		*ms_find_env_value(t_ms *ms, char *key);
void		ms_free_env(t_env *envs);
int			ms_is_in_env(t_ms *ms, const char *key);
int			update_env_value(t_env *env, char *key, char *value);
t_env		*ms_last_env(t_env *env);

// history
t_history	*ms_last_history(t_history *history);
void		ms_free_history(t_ms *ms);

/* read_input */
int			ms_read_input(t_ms *ms);
int			ms_here_doc(t_cmd **curr_cmd);

// signals
void		ms_init_signal_detection(void);
void		ctrl_c_redisplay_prompt(int sig, siginfo_t *siginfo, void *context);
void		ctrl_d_exit_shell(int sig, siginfo_t *siginfo, void *context);

/* history */
void		ms_init_history(t_ms *ms);
void		ms_add_history(t_ms *ms, char *line);
void		ms_print_history(t_ms *ms, t_cmd *curr_cmd, t_p *prompt);

/* tokenizer */
void		line_inside_quotes_replaces(t_ms *ms, char **line_inside_quotes,
				int first, int second);
void		ms_switch_subshell_output(t_ms *ms);
int			ms_execute_prompt_in_subshell(t_ms *ms, t_p *curr_p,
				int *exit_code);
void		ms_parse_subshells(t_p **curr_p);
int			execv_in_sub_shell(t_cmd **curr_cmd, t_ms *ms);
int			ms_sintax(t_ms *ms);
int			ms_tokenizer(t_ms *ms);
void		ms_wildcard(t_ms *ms);
int			ms_check_quotes(t_ms *ms);
int			ms_get_index(t_ms *ms);
int			ms_check_if_have_quotes(t_ms *ms, char *line);
int			get_index_before_space(t_ms *ms, int size, char **cmd);
int			get_boolean(const char *wildcard, const struct dirent *de, int all);
void		update_tmp(char **replace, DIR *dr, struct dirent **de, char **tmp);
void		ms_expand_dolar(t_ms *ms);
void		threat_dolar(t_ms *ms,
				char **line_splited, int i, char *dolar_cmd);
void		ms_has_single_quotes(t_ms *ms, char *dolar_cmd);
int			ms_jump_to_end_quote(t_ms *ms, char *line, int *i, int size);
void		subs_replace_join_free(char *find, char *replace, \
t_ms *ms, char *line);
int			ms_count_char(char *str, char c);
int			valid_chr(char chr);
void		ms_quotes_vs_connectors(t_ms *ms, char *line);
void		ms_check_quotes_aux(t_ms *ms, char **cmd, char *tmp, char *aux);
void		ms_replace_connectors_by_token(t_ms *ms, char *tmp);
void		print_lst(t_file *head);
void		ms_free_files(t_file **files);
t_file		*ms_get_current_directory(void);
void		ms_file_delete(t_file **head);
void		ms_go_start(t_file **files);
void		set_exit_code(t_ms *ms, t_cmd *curr_cmd, int code);
int			all_equal(char *c);

char		identify_chr(char *line);
int			ft_count_chrs(char **str);
char		**malloc_split(int n);
void		ft_sigation(int signum, void (*f)(int, siginfo_t *, void *));

/* parse */
int			ms_parse(t_ms *ms);
t_p			*parse_prompts(t_ms *ms);
int			ms_parse_commands_aux(t_cmd *curr_cmd, int *c);
t_p			*ms_get_prompt(t_ms *ms, t_p *curr_p, int i);
int			try_find_cmd_path_using_access(t_cmd *curr_cmd);
int			ms_parse_input(t_cmd **curr_cmd);
int			parse_input_output(t_cmd *curr_cmd);
int			ms_parse_commands(t_ms *ms, t_p *curr_p);
int			try_find_cmd_path_using_access(t_cmd *curr_cmd);
t_cmd		*append_new_cmd_next(t_cmd *curr_cmd);
int			is_input_command(char *name);
char		*treat_acumulated_space(char *str);
void		remove_redirect(t_cmd *curr_cmd, char *str_op, char *output_path);
int			create_output(t_cmd *curr_cmd, int type, char *cut);
char		*treat_acumulated_space(char *str);
int			nothing_before(char **str_op, t_cmd **curr_cmd, \
char **split_by_space, char *arg);
int			something_before(t_cmd **curr_cmd, \
char **split_by_space, char *arg, char **str_op);
int			check_inputs(char *input, t_cmd **curr_cmd, int i);
char		**ft_mtx_replace_all_special(char **mtx, t_cmd *curr_cmd);
int			is_dir(char *path);
int			invalid_permission1(t_cmd **curr_cmd, char *path, char *subject);
int			invalid_permission2(t_cmd **curr_cmd, char *path, char *subject);
int			is_file(const char *path);
void		check_inputs_aux_error_msg(\
t_cmd **curr_cmd, char *tmp4, char *tmp2);
int			is_not_a_dir(t_cmd *curr_cmd);
int			test_access1(t_cmd **curr_cmd, char *path, char *subject);
int			test_access2(t_cmd **curr_cmd, char *path, char *subject);
int			glued(t_cmd **curr_cmd);
int			loose(t_cmd **curr_cmd);
char		*trim_many_spaces(char	*line, char *key);
int			execute_symbol(t_cmd *curr_cmd, int type, char *cut);
int			can_read(char *path);
int			can_write(char *path);
int			can_execute(char *path);
void		pre_treats(t_cmd **curr_cmd);
int			output_fd(t_cmd **curr_cmd);
int			parse_path_execution(t_cmd **curr_cmd);
t_psub		*token_subshells_pre_split_connectors(t_ms *ms);
void		untoken_subshells_pos_split_connectors(t_ms *ms, t_psub *psub);
void		ms_parse_subshells_save_subshell(t_psub *psub);
void		ms_parse_subshells_loop(t_psub *psub, int i);
int			check_aste(char **wc_split, int i, char *wc, t_file *head);
void		pre_init_curr_cmd(t_ms *ms, t_p **curr_p, \
t_cmd **curr_cmd, int c);
int			try_find_cmd_path_using_access_aux(t_cmd *curr_cmd, \
char *test_this_cmd, char **s_path);

// prompt
void		ms_free_prompt(t_ms *ms);

// cmd
t_cmd		*ms_dll_cmd_last(t_cmd *cmds);
void		ms_dll_cmd_free(t_cmd *cmds);
int			decide_correct_error_message(t_cmd *curr_cmd);

/* execute */
void		ms_execute(t_ms *ms);
int			ms_execute_commands(t_ms *ms, t_p *curr_p);
void		ms_execute_command(t_p *prompt, \
t_cmd *curr_cmd, char **envp, int *aux_fd);
int			bridge_builtion_other_cmds(t_cmd *curr_cmd, \
t_p *prompt, int *clo);

int			is_builtin(char *cmd);
void		execute_builtin(t_ms *ms, t_cmd *curr_cmd, t_p *prompt);
void		ms_close_fds(t_p *curr_p);
char		*last_cmd_exit_code(t_cmd *curr_cmd);
int			pre_cat_ls_sc(t_ms *ms, t_cmd **curr_cmd);
void		exec_cat_ls_sc(t_ms *ms);
int			ms_which_command_type(t_p *curr_p, \
t_cmd *curr_cmd, t_ms *ms);
void		print_fd_or_execute_cmd(t_ms *ms, t_p *curr_p);
int			get_child_process_id(const t_p *prompt, \
				t_cmd *curr_cmd, char **envp, const int *aux_fd);
int			is_input_command2(char *name, t_cmd **curr_cmd, \
t_p *curr_p);
int			ms_execute_in_redi(t_p *curr_p);

// builtins
void		ms_cd(t_ms *ms, t_cmd *curr_cmd, t_p *prompt);
void		ms_echo(t_ms *ms, t_cmd *curr_cmd, t_p *prompt);
void		ms_env(t_ms *ms, t_cmd *curr_cmd, t_p *prompt);
void		ms_exit(t_ms *ms, t_cmd *curr_cmd);
void		ms_export(t_ms *ms, t_cmd *curr_cmd);
void		ms_free_qs(const t_ms *ms, int aux, char **line, t_free **curr_qs);
void		quicksort(t_qs *qs, int left, int right, int (*comp)(void*, void*));
int			cmpstr(void *v1, void *v2);
void		ms_pwd(t_ms *ms, t_cmd *curr_cmd, t_p *prompt);
void		ms_unset(t_ms *ms, t_cmd *curr_cmd, t_p *curr_p);
void		print_sorted_env(t_ms *ms, int aux);
char		**env_to_array(t_ms *ms);

/* deinit */
void		ms_reinit(t_ms *ms);
void		ms_finish(t_ms *ms);
void		free_ssub(t_ssub *ssub);

/* ms */
void		ms_subshell(t_ms *ms);
void		minishell(t_ms *ms);

#endif
