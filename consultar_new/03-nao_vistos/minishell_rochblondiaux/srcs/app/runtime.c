/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/17 13:49:39 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	runtime(t_app *app, char *input)
{
	t_token		*tokens;
	int			result;
	t_command	**commands;

	result = 0;
	tokens = lexer(app, input, &result);
	if (!tokens)
		return (FALSE);
	result = syntaxer(input, tokens);
	if (!result)
	{
		str_error(app, SYNTAX_ERROR);
		app->last_exit = 2;
		return (FALSE);
	}
	input = expand_env_vars(app, input);
	if (!input)
		return (FALSE);
	commands = parse(input);
	if (expand(app, commands))
		executor(app, commands);
	free_command_map(commands);
	return (TRUE);
}
