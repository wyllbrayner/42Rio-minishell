/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/17 14:38:18 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dispatch_builtins(t_app *app, t_command *cmd)
{
	if (ft_strcmp(cmd->name, "cd"))
		builtin_cd(app, cmd);
	else if (ft_strcmp(cmd->name, "echo"))
		builtin_echo(app, cmd);
	else if (ft_strcmp(cmd->name, "pwd"))
		builtin_pwd(app, cmd);
	else if (ft_strcmp(cmd->name, "exit"))
		builtin_exit(app, cmd);
	else if (ft_strcmp(cmd->name, "unset"))
		builtin_unset(app, cmd);
	else if (ft_strcmp(cmd->name, "export"))
		builtin_export(app, cmd);
	else if (ft_strcmp(cmd->name, "env"))
		builtin_env(app, cmd);
}
