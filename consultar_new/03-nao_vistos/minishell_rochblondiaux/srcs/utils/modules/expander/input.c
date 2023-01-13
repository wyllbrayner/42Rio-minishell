/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/09 16:52:33 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	error_synt(t_app *app, t_command *cmd)
{
	error(app, cmd->name, AMBIGUOUS_REDIRECTION);
	app->last_exit = 1;
	return (FALSE);
}

int	expand_input(t_app *app, t_command *cmd)
{
	t_redir	*r;

	r = cmd->redirections;
	while (r)
	{
		if (r->type == INPUT)
		{
			if (!r->path || !r->path[0] || r->path[0] == '$')
				return (error_synt(app, cmd));
			cmd->input_fd = open(r->path, O_RDONLY);
			if (cmd->input_fd <= 0)
			{
				str_error(app, r->path);
				return (FALSE);
			}
		}
		else if (r->type == DELIMITER)
			if (!r->path || !r->path[0])
				return (error_synt(app, cmd));
		r = r->next;
	}
	return (TRUE);
}
