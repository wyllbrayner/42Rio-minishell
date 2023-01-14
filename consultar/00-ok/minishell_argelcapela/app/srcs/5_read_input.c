/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_read_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:47 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/06 17:42:58 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

char	*ms_print_sh_name(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_printf_to_var("%s%s%s %s%s%s ", \
			BOLD_BLUE, SHELL, END_COLOR, BOLD_CYAN, cwd, END_COLOR));
	else
		return (ft_printf_to_var("%s", SHELL));
}

static void	ms_count_connectors(t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ms->shell_line[i])
	{
		if ((ms->shell_line[i] == '&' && ms->shell_line[i + 1] == '&') \
			|| (ms->shell_line[i] == '|' && ms->shell_line[i + 1] == '|'))
			j++;
		i++;
	}
	ms->connectors_amount = j;
}

int	ft_is_empty(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\0')
			return (0);
		i++;
	}
	return (1);
}

int	ms_read_input(t_ms *ms)
{
	ms_init_signal_detection();
	ms->sh_name = ms_print_sh_name();
	ms->shell_line = readline(ms->sh_name);
	ft_free_ptr((void *) &ms->sh_name);
	if (ft_is_empty(ms->shell_line))
		return (1);
	else if (!ms->shell_line)
	{
		ctrl_d_exit_shell(SIGQUIT, NULL, NULL);
		exit(0);
	}
	if (ft_strnstr(ms->shell_line, "&&", ft_strlen(ms->shell_line)) \
	!= NULL || ft_strnstr(ms->shell_line, "||", ft_strlen(ms->shell_line)) \
	!= NULL )
		ms_count_connectors(ms);
	return (0);
}
