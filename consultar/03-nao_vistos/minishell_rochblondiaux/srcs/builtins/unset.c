/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/17 13:59:59 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	arr_length(char **array)
{
	size_t	i;

	i = 0;
	if (!array[i])
		return (i);
	while (array[i])
		i++;
	return (i);
}

void	builtin_unset(t_app *app, t_command *cmd)
{
	size_t	i;
	int		nb_error;

	if (arr_length(cmd->args) < 1)
	{
		error(app, "unset", NOT_ENOUGH_ARGS);
		return ;
	}
	i = -1;
	nb_error = 0;
	while (cmd->args[++i])
		nb_error += remove_map_element(&app->env, cmd->args[i]);
	if (nb_error != 0)
	{
		error(app, UNSET_ERROR, "");
		cmd->status = 1;
	}
	else
		cmd->status = 0;
}
