/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 05:16:59 by ldatilio          #+#    #+#             */
/*   Updated: 2022/09/11 03:25:18 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../libs/libft/src/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <wait.h>

typedef struct s_msh
{
	int		argc; //ok
	char	**argv; //ok
	char	**envp; //ok
	t_dlist	*envp_lst; //ok
	char	*prompt; //ok
	int		exit_code;
	char	*parsed_line; //ok
	int		error; //ok
	char	*file_name;
	char	redirect; //ok
	int		doble_redirect; //ok
	int		here_doc;
	int		fd[2];
	int		fdin;
	int		fdout;
	int		save_stdin; //ok
	int		save_stdout; //ok
	pid_t	pid; //ok
	int		last_cmd; //ok
	t_dlist	*cmds_lst;
}	t_msh;

extern t_msh	g_msh;

/* ************************************************************************** */
/* ******************************** BUILTINS ******************************** */
/* ************************************************************************** */
void	cd(char **cmd);
int		echo(char **cmd);
int		env(void);
char	*ft_getenv(char *var);
void	export(char **cmd);
void	export_var(char *cmd);
void	msh_exit(char **cmd);
int		pwd(void);
int		unset(char *env);
int		ft_strcmp(char *s1, char *s2);
/* ************************************************************************** */

/* ************************************************************************** */
/* ********************************* UTILS ********************************** */
/* ************************************************************************** */
int		check_syntax_error(char c);
void	check_directory_error(char *file);
t_dlist	*create_list(char **strs);
int		exec_builtin(char **cmd);
int		exec_external(char **cmd);
void	execute(char **cmd);
char	*find_cmd_path(char *cmd);
void	free_all(void);
void	free_cmds(char ***cmds);
void	free_cmds_lst(void);
void	free_matrix(char **matrix);
char	*ft_strcjoin(char *s1, char s2);
char	*get_node_value(t_dlist *node);
int		is_builtin(char *cmd);
void	open_file_input(void);
void	open_file_output(void);
void	parse_cmds(char *parsed_line);
void	parse_line(char *line);
void	parse_quotes(char *line, int *i, char quote);
void	parse_redirect(char *line, int *i, char operator);
void	parse_variables(char *line, int *i);
char	*refresh_prompt(void);
void	signal_exit(int signum);
void	signal_handler(int signum);
/* ************************************************************************** */

#endif
