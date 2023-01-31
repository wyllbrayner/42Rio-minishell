/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_parse_commands_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:12 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/15 20:32:34 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	can_read(char *path)
{
	return (access(path, R_OK));
}

int	can_write(char *path)
{
	return (access(path, W_OK));
}

int	can_execute(char *path)
{
	return (access(path, X_OK));
}

int	invalid_permission1(t_cmd **curr_cmd, char *path, char *subject)
{
	(void) path;
	(void) subject;
	if (!can_read((*curr_cmd)->just_name)
		|| !can_execute((*curr_cmd)->just_name))
	{
		ft_pf_error("%s: %s: Permission denied\n", \
"miniheaven", (*curr_cmd)->just_name);
		(*curr_cmd)->can_execute = 0;
		(*curr_cmd)->exit_code = 126;
		set_exit_code((*curr_cmd)->my_prompt->ms, (*curr_cmd), 126);
		return (1);
	}
	return (0);
}
