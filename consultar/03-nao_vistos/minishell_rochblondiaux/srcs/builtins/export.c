/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/17 14:38:53 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	export_env(t_app *app, char *arg, int *err)
{
	t_env	*new;

	if (arg[0] != '$' && get_env(app, arg) != NULL)
		return ;
	if (check_new_env(app, arg) != 0)
	{
		*err += 1;
		return ;
	}
	new = create_map_element(arg);
	if (new)
		set_env(app, new->key, new->value);
	free_env(new);
}

void	builtin_export(t_app *app, t_command *cmd)
{
	int		err;
	size_t	i;

	if (print_right_output(app, cmd))
		return ;
	i = -1;
	err = 0;
	while (cmd->args[++i])
		export_env(app, cmd->args[i], &err);
	if (err != 0)
		cmd->status = 1;
	else
		cmd->status = 0;
}
