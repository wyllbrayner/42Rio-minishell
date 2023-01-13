/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/17 15:57:38 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/**
 * Libraries
 */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "colors.h"
# include "settings.h"
# include "messages.h"
# include "enums.h"
# include "structures.h"
# include "../libft/libft.h"

/**
 * Booleans
 */
# define TRUE 1
# define FALSE 0

/**
 * Application
 */
t_app		*load_application(char **env);
void		start_application_loop(t_app *app);
int			runtime(t_app *app, char *input);
void		start_application(t_app *app);
void		stop_application(t_app *app);
void		handle_mode(t_app *app, char *input, char **ret);
char		*get_right_prompt(t_app *app);

/**
 * Modules
 */
t_token		*lexer(t_app *app, char *input, int *result);
int			syntaxer(char *input, t_token *tokens);
t_command	**parse(char *input);
int			expand(t_app *app, t_command **commands);
void		executor(t_app *app, t_command **cmds);

/**
 * Modules utils
 */
t_token		get_token(char *input, size_t i);
t_token		get_real_token(char *a);
size_t		tokens_length(t_token *tokens);
int			is_separator(char *c, size_t index);
size_t		count_commands(char *args);
char		**parse_raw_commands(char *raw);
char		*parse_redirections(t_command *command, char *raw);
char		**parse_quotes(char *raw);
char		*expand_env_vars(t_app *app, char *input);
int			expand_input(t_app *app, t_command *cmd);
void		parse_cmd_tokens(t_command **cmds, char *raw);
char		*get_executable(t_app *app, t_command *cmd, char *input);
int			fork_cmd(t_app *app, t_command *cmd);
char		**get_executable_args(t_command *cmd);
t_pipe		*init_pipeline(t_app *app);
void		update_pipeline(t_app *app, t_pipe *p);
void		execute_native(t_app *app, t_command *cmd, t_pipe *pipe);
int			expand_output(t_app *app, t_command *cmd);
int			contains_redirection(char *raw);
void		check_for_env(t_app *app, t_command **cmd);
void		check_for_args_env(t_command *cmd);
char		*expand_wildcards(t_app *app, char *input);
int			find_executable(t_app *app, t_command *cmd);
int			get_quote_in_here(char *s);
void		fill(char **args, char **raw);
char		*sup_quote(char *arg);
int			is_quote_in_here(char *s);
int			choose_quote(char *s);

/**
 * Builtins
 */
void		dispatch_builtins(t_app *app, t_command *cmd);
void		builtin_echo(t_app *app, t_command *cmd);
void		builtin_cd(t_app *app, t_command *cmd);
void		builtin_pwd(t_app *app, t_command *cmd);
void		builtin_exit(t_app *app, t_command *cmd);
void		builtin_export(t_app *app, t_command *cmd);
void		builtin_unset(t_app *app, t_command *cmd);
void		builtin_env(t_app *app, t_command *cmd);

/**
 * App utils
 */
char		*get_prompt_symbol(t_app *app);
void		error(t_app *app, char *name, char *error);
void		str_error(t_app *app, char *error);
void		disable_signal(t_app *app);
void		enable_signal(t_app *app);

/**
 * Array utils
 */
size_t		array_length(char **array);
void		free_array(char **array);
char		**sub_array(char **array, size_t start, size_t length);
char		**add_array_element(char **array, char *element);
char		**empty_array(void);

/**
 * Map utils
 */
t_env		*init_env_map(char **env);
void		add_map_element(t_env **env, t_env *new);
void		free_map(t_env **env);
t_env		*create_map_element(char *entry);
t_env		*get_map_element(t_env *env, char *name);
int			remove_map_element(t_env **env, char *key);
void		print_sorted_map(t_env *env);
size_t		map_length(t_env *env);

/**
 * Environment utils
 */
char		*get_env(t_app *app, char *key);
char		*env_exists(t_app *app, char *key);
void		set_env(t_app *app, char *name, char *key);
int			check_new_env(t_app *app, char *var);
int			print_right_output(t_app *app, t_command *cmd);
void		free_env(t_env *env);
char		**format_env(t_app *app);

/**
 * IO Utils
 */
char		*working_directory(void);
char		*home_directory(t_app *app);
int			exists(char *path);
char		*parent(char *path);
char		*path(char *raw);
char		*read_file(t_app *app, char *path);
void		write_in_file(t_app *app, char *filename,
				char *content, int append);
int			is_relative(char *path);

/**
 * String utils
 */
void		ft_strcat(char *dst, char *src);
char		*replace_str(char *sentence, char *find, char *replace);
int			strchr_separator(char *s);
void		is_in_quotes(int *quote, char c);
void		reset_str(char **original, char *replacement);
void		reset_cmd(t_app *app, t_command *cmd, char *input);
char		*reset_arg(char *original, char *replacement);
size_t		ft_contains(char *s, char c);
char		*replace_first(char *str, char *find, char *replace);
char		*right_file(char *c);

/**
 * Commands utils
 */
void		free_command(t_command *cmd);
void		free_command_map(t_command **map);
t_command	*init_command(void);
size_t		commands_length(t_command **args);

/**
 * Builtins utils
 */
int			is_builtin(t_command *cmd);
char		*get_path(t_app *app, char *input);
size_t		ft_strlen_lastrepo(char *s);
char		*is_a_path(char *input, char **split);
char		*cdpath_exist(t_app *app, char *input, char **split);
char		*get_path(t_app *app, char *input);
char		*get_new_path(char *input, char *arg);
char		*get_rep_path(char *input, char *arg, int j);

/**
 * Redirections utils
 */
t_redir		*create_redirection(t_redirection type, char *path);
void		add_redirection(t_redir **list, t_redir *redir);
void		free_redirections(t_redir **list);
size_t		redirections_length(t_redir *list);

/**
 * Delimiters utils
 */
int			contains_del(char *input);
char		*is_the_del(char *input);
char		*delimit_all(t_app *app, t_command *cmd);
int			is_a_delim(t_redir *r);
char		*join_delims(char *args, char *line, int *i, size_t *j);
void		handle_delims(t_app *app, t_command *cmd);
int			ft_contains_delim(char *input);

#endif