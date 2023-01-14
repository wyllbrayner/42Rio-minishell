/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/04 10:33:30 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	set_path(t_app *app, char *a)
{
	int	ret;

	set_env(app, "OLDPWD", get_env(app, "PWD"));
	set_env(app, "PWD", a);
	ret = chdir(a);
	free(a);
	return (ret == FALSE);
}

void	builtin_cd(t_app *app, t_command *cmd)
{
	char	*paths;
	char	*temp;

	if (array_length(cmd->args) > 1)
	{
		error(app, "cd", TOO_MANY_ARGUMENTS);
		cmd->status = 1;
		return ;
	}
	paths = get_path(app, cmd->args[0]);
	if (!paths)
	{
		cmd->status = 1;
		error(app, "cd", HOME_UNDEFINED);
		return ;
	}
	temp = path(paths);
	free(paths);
	if (!temp)
	{
		str_error(app, "cd");
		cmd->status = 1;
		return ;
	}
	set_path(app, temp);
}
