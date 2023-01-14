/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_del_nl(char *param)
{
	size_t	i;

	i = 0;
	if (param[0] != '-')
		return (-1);
	while (param[++i])
		if (param[i] != 'n')
			return (-1);
	return (0);
}

static void	print_arg(t_app *app, t_command *cmd, size_t i)
{
	if (cmd->args[i][0] == '$' && cmd->args[i][1] == '?'
		&& !cmd->args[i][2])
	{
		free(cmd->args[i]);
		cmd->args[i] = ft_itoa(app->last_exit);
	}
	if (i == array_length(cmd->args) - 1)
		printf("%s", cmd->args[i]);
	else
		printf("%s ", cmd->args[i]);
}

void	builtin_echo(t_app *app, t_command *cmd)
{
	int		mode;
	size_t	i;

	i = 0;
	mode = 0;
	if (!cmd->args[0])
	{
		printf("\n");
		cmd->status = 0;
		return ;
	}
	while (!is_del_nl(cmd->args[i++]))
		mode = 1;
	i -= 2;
	while (cmd->args[++i])
		print_arg(app, cmd, i);
	if (array_length(cmd->args) > 0)
	{
		if (mode)
			printf("%s%s%%%s", BOLD, "\033[3;107;30m", RESET);
		printf("\n");
	}
	else
		printf("\n");
	cmd->status = 0;
}
