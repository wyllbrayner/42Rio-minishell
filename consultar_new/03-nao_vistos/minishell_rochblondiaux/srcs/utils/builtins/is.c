/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c 	                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	cm(t_command *cmd, char *name)
{
	return (ft_strcmp(cmd->name, name));
}

int	is_builtin(t_command *cmd)
{
	return (cm(cmd, "echo")
		|| cm(cmd, "cd")
		|| cm(cmd, "pwd")
		|| cm(cmd, "export")
		|| cm(cmd, "unset")
		|| cm(cmd, "env")
		|| cm(cmd, "exit"));
}
