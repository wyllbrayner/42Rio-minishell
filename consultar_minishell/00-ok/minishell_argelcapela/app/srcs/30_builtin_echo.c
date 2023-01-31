/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:25 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/19 17:37:54 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

char	*last_cmd_exit_code(t_cmd *curr_cmd)
{
	t_history	*history_line;
	char		*e_code;

	history_line = ms_last_history(curr_cmd->my_prompt->ms->history);
	history_line = history_line->prev;
	e_code = ft_itoa(history_line->l_c_exit_code);
	if ((curr_cmd->my_prompt->ms->p_amount > 1)
		&& (curr_cmd->my_prompt->index > 0)
		&& (ft_strnstr(curr_cmd->cmd_line,
				"$?", ft_strlen(curr_cmd->cmd_line))))
		e_code = ft_itoa(curr_cmd->my_prompt->prev->exit_code);
	return (e_code);
}

static void	print_cmd_content_aux(t_cmd *curr_cmd,
int aux, char **cmd_splited, int i)
{
	char	*e_code;
	int		len;

	len = ft_mtx_size((void **) cmd_splited);
	e_code = last_cmd_exit_code(curr_cmd);
	if (curr_cmd->my_prompt->ms->has_single_quotes)
		ft_chr_remove_all(cmd_splited[i], '\'');
	cmd_splited[i] = ft_super_replace_all(cmd_splited[i], 22,
			T_SPACE, " ", T_HEREDOC, "<<", T_INPUT, "<",
			T_OUTPUT1, ">", T_OUTPUT2, ">>", T_LEFTP, "(",
			T_SUBSHELL, "()", T_RIGHTP, ")", T_E_COMER, "&",
			T_PIPE2, "|", T_EXIT_CODE, e_code);
	ft_free_ptr((void *) &e_code);
	ft_free_ptr((void *) &e_code);
	ft_putstr_fd(cmd_splited[i], aux);
	if (i < (len - 1))
		ft_putstr_fd(" ", aux);
}

static void	print_cmd_content( \
t_cmd *curr_cmd, char **cmd_splited, int aux)
{
	int		i;

	i = 0;
	if (ft_strncmp(cmd_splited[1], "-n", ft_strlen(cmd_splited[1])) == 0)
		i = 1;
	while (!ft_strncmp(cmd_splited[i], "-n", \
	ft_strlen(cmd_splited[i])) && cmd_splited[i])
		++i;
	if (i != 0)
		i--;
	while ((i++ < (curr_cmd->args_amount - 1)) && (cmd_splited[i]))
		print_cmd_content_aux(curr_cmd, aux, cmd_splited, i);
}

static void	ms_echo_having_flag(t_ms *ms, char **cmd_splited, \
	t_cmd *curr_cmd, int aux)
{
	int		has_flag;

	has_flag = ft_strncmp(cmd_splited[1], "-n", ft_strlen(cmd_splited[1]));
	print_cmd_content(curr_cmd, cmd_splited, aux);
	if (has_flag)
		ft_putstr_fd("\n", aux);
	ms->p->cmds->exit_code = 0;
}

void	ms_echo(t_ms *ms, t_cmd *curr_cmd, t_p *prompt)
{
	char	**cmd_splited;
	int		aux;
	int		clo;

	clo = 0;
	aux = bridge_builtion_other_cmds(curr_cmd, prompt, &clo);
	cmd_splited = curr_cmd->cmd_splited_by_space;
	if (!cmd_splited[1])
		ft_putstr_fd("\n", aux);
	else
		ms_echo_having_flag(ms, cmd_splited, curr_cmd, aux);
	if (clo)
		close(aux);
}
