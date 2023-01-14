/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/09 16:53:01 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_pipe {
	int	in;
	int	out;
	int	backup;
}	t_pipe;

typedef struct s_redir {
	t_redirection	type;
	char			*path;
	struct s_redir	*next;
}					t_redir;

typedef struct s_command {
	char				*name;
	char				**args;
	t_redir				*redirections;
	int					status;
	t_token				next_token;
	t_token				previous_token;
	struct s_command	*previous_cmd;
	struct s_command	*next_cmd;
	pid_t				pid;
	int					p_status;
	int					input_fd;
	int					output_fd;
	char				*executable;
}						t_command;

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_app {
	int				running;
	int				exit;
	int				last_exit;
	t_prompt_mode	mode;
	t_env			*env;
}					t_app;

#endif