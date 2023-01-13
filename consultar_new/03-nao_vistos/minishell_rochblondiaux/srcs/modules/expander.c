/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/04 10:22:20 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand(t_app *app, t_command **commands)
{
	size_t	i;

	i = -1;
	while (commands[++i])
	{
		if ((!commands[i] || (!commands[i]->name[0] && !commands[i + 1]))
			&& !commands[i]->redirections)
		{
			app->last_exit = 127;
			error(app, "", COMMAND_NOT_FOUND);
			return (FALSE);
		}
		if (commands[i]->name[0] == '$' && !get_env(app, commands[i]->name))
		{
			app->last_exit = 127;
			error(app, "", COMMAND_NOT_FOUND);
			return (FALSE);
		}
		if (!expand_output(app, commands[i])
			|| !expand_input(app, commands[i]))
			return (FALSE);
	}
	return (TRUE);
}
