/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                          :+:      :+:    :+:     */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	reset_cmd(t_app *app, t_command *cmd, char *input)
{
	free_command(cmd);
	runtime(app, input);
}

void	reset_str(char **original, char *replacement)
{
	free(*original);
	*original = replacement;
}

char	*reset_arg(char *original, char *replacement)
{
	free(original);
	return (replacement);
}
