/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	count_envs(char **args)
{
	size_t	i;
	int		count;

	i = -1;
	count = 0;
	while (args[++i])
	{
		if (args[i][0] != '$')
			count ++;
	}
	return (count);
}

void	check_for_args_env(t_command *cmd)
{
	size_t		i;
	size_t		j;
	char		**new_commands;

	i = -1;
	j = -1;
	new_commands = malloc(sizeof(char *) * (count_envs(cmd->args) + 1));
	if (!new_commands)
		return ;
	while (cmd->args[++i])
		if (cmd->args[i][0] != '$')
			new_commands[++j] = ft_strdup(cmd->args[i]);
	new_commands[++j] = NULL;
	free_array(cmd->args);
	cmd->args = new_commands;
}

void	check_for_env(t_app *app, t_command **cmd)
{
	size_t	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->name[0] == '$')
		{
			if (!get_env(app, cmd[i]->name))
			{
				free (cmd[i]->name);
				cmd[i]->name = ft_strdup("");
			}
		}
	}
}
