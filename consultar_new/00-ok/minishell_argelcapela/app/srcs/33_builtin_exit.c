/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:39 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/12 19:44:16 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>
#include <stdio.h>

static int	ms_check_numeric_argument(t_ms *ms,
t_cmd *curr_cmd, int aux, int *exit_code)
{
	char	*line;
	int		i;

	i = 0;
	while (curr_cmd->cmd_splited_by_space[1][i])
	{
		if (!ft_isdigit(curr_cmd->cmd_splited_by_space[1][i])
			&& curr_cmd->cmd_splited_by_space[1][i] != '+'
			&& curr_cmd->cmd_splited_by_space[1][i] != '-')
		{
			line = ft_printf_to_var("exit\nminiheaven: exit: %s: \
numeric argument required\n", \
					curr_cmd->cmd_splited_by_space[1]);
			ft_putstr_fd(line, aux);
			ft_free_ptr((void *) &line);
			*exit_code = 2;
			get_next_line(-1);
			ms_finish(ms);
			exit(*exit_code);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ms_exit(t_ms *ms, t_cmd *curr_cmd)
{
	int		aux;
	int		exit_code;

	aux = 0;
	exit_code = 0;
	if (curr_cmd->args_amount > 2)
	{
		ft_putstr_fd("exit\nminiheaven: exit: too many arguments\n", aux);
		set_exit_code(curr_cmd->my_prompt->ms, curr_cmd, 1);
	}
	else if (curr_cmd->args_amount == 2)
	{
		if (!ms_check_numeric_argument(ms, curr_cmd, aux, &exit_code))
			exit_code = ft_atoi(curr_cmd->cmd_splited_by_space[1]);
	}
	ft_putstr_fd("exit", aux);
	if (!ms->breakline)
		ft_putstr_fd("\n", aux);
	ms_finish(ms);
	get_next_line(-1);
	exit(exit_code);
}
