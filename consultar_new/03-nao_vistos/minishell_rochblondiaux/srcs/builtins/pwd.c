/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(t_app *app, t_command *cmd)
{
	char	*path;

	path = get_env(app, "PWD");
	if (path)
	{
		printf("%s\n", path);
		cmd->status = 0;
	}
	else
	{
		cmd->status = 1;
		error(app, "pwd", PWD_UNDEFINED);
	}
}
