/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_command	*parse_command(char **raw)
{
	t_command	*cmd;
	char		**args;

	cmd = init_command();
	if (!cmd)
		return (NULL);
	while (contains_redirection(*raw))
		reset_str(raw, parse_redirections(cmd, ft_strdup(*raw)));
	args = parse_quotes(*raw);
	if (!args)
		return (NULL);
	if (array_length(args) > 0)
		reset_str(&cmd->name, ft_strdup(args[0]));
	else
		reset_str(&cmd->name, ft_strdup(""));
	cmd->args = sub_array(args, 1, array_length(args));
	free_array(args);
	return (cmd);
}

t_command	**parse(char *input)
{
	t_command	**cmds;
	char		**raw_cmds;
	size_t		index;

	index = -1;
	raw_cmds = parse_raw_commands(input);
	if (!raw_cmds)
		return (NULL);
	cmds = malloc(sizeof (t_command *) * (array_length(raw_cmds) + 1));
	if (!cmds)
		return (NULL);
	while (raw_cmds[++index])
		cmds[index] = parse_command(&raw_cmds[index]);
	cmds[index] = NULL;
	free_array(raw_cmds);
	parse_cmd_tokens(cmds, input);
	free(input);
	return (cmds);
}
