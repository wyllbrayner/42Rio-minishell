/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/17 14:53:42 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	open_fd(t_redir *r, t_command *cmd)
{
	if (r->type == APPENDER)
		cmd->output_fd = open(r->path,
				O_CREAT | O_RDWR | O_APPEND, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
	else
		cmd->output_fd = open(r->path,
				O_CREAT | O_RDWR, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
}

int	expand_output(t_app *app, t_command *cmd)
{
	t_redir	*r;

	r = cmd->redirections;
	while (r)
	{
		if (r->type == OUTPUT || r->type == APPENDER)
		{
			if (!r->path || !r->path[0] || r->path[0] == '$')
			{
				error(app, cmd->name, AMBIGUOUS_REDIRECTION);
				app->last_exit = 1;
				return (FALSE);
			}
			open_fd(r, cmd);
			if (cmd->output_fd <= 0)
			{
				str_error(app, r->path);
				return (FALSE);
			}
		}
		r = r->next;
	}
	return (TRUE);
}
