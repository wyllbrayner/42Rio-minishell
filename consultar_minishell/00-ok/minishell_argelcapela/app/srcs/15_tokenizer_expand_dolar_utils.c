/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_tokenizer_expand_dolar_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:55:01 by argel             #+#    #+#             */
/*   Updated: 2022/12/19 17:21:51 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	threat_dolar_loop(char **line_splited, \
int j, int *threated, t_ms *ms)
{
	int		final;

	if (line_splited[*(ms->i_dolar_cmd)][j] == '$' &&
	j != (int)(ft_strlen(line_splited[*(ms->i_dolar_cmd)]) - 1)
	&& line_splited[*(ms->i_dolar_cmd)][j + 1] != '$'
	&& ft_strncmp(&line_splited[*(ms->i_dolar_cmd)][j + 1], \
T_SPACE, ft_strlen(T_SPACE)) != 0)
	{
		final = 1;
		while (valid_chr(line_splited[\
*(ms->i_dolar_cmd)][j + final])
		&& ft_strncmp(&line_splited[*(ms->i_dolar_cmd)][j + final], \
T_SPACE, ft_strlen(T_SPACE) != 0))
			final++;
		(*ms->dolar_cmd) = ft_substr((line_splited[*(ms->i_dolar_cmd)] + j), \
0, final);
		ms_has_single_quotes(ms, (*ms->dolar_cmd));
		*threated = 1;
		ms->n_threats += 1;
	}
}

void	threat_dolar(t_ms *ms,
char **line_splited, int i, char *dolar_cmd)
{
	int		j;
	int		threated;

	j = 0;
	threated = 0;
	while (line_splited[i][j])
	{
		ms->dolar_cmd = &dolar_cmd;
		ms->i_dolar_cmd = &i;
		threat_dolar_loop(line_splited, j,
			&threated, ms);
		j++;
	}
}

static char	*treat_exit_code_str(t_ms *ms)
{
	t_history	*history_line;
	char		*tmp_exit_code;
	char		*tmp;

	history_line = ms_last_history(ms->history);
	history_line = history_line->prev;
	tmp_exit_code = ft_itoa(history_line->l_c_exit_code);
	tmp = ft_str_replace_all(ft_strdup(ms->shell_line_tokenized), \
"$?", T_EXIT_CODE);
	ft_free_ptr((void *) &tmp_exit_code);
	return (tmp);
}

int	check_expand(t_ms *ms, char *dolar_cmd,
char *aux)
{
	if (ft_strnstr(dolar_cmd, "$?", ft_strlen(dolar_cmd)))
	{
		aux = treat_exit_code_str(ms);
		ft_free_ptr((void *) &ms->shell_line_tokenized);
		ms->shell_line_tokenized = aux;
		return (0);
	}
	else
	{
		aux = ft_str_replace_all(\
ms->shell_line_tokenized, dolar_cmd, "");
		ms->shell_line_tokenized = aux;
		return (1);
	}
}

void	ms_has_single_quotes(t_ms *ms, \
char *dolar_cmd)
{
	char	*no_dolar;
	char	*value;
	char	*aux;

	aux = NULL;
	no_dolar = ft_substr(dolar_cmd, 1, ft_strlen(dolar_cmd));
	if (ft_strncmp(dolar_cmd, "$", ft_strlen(dolar_cmd)) == 0)
		return ;
	if (ms_is_in_env(ms, no_dolar))
	{
		value = ms_find_env_value(ms, no_dolar);
		aux = ft_str_replace_all(\
ms->shell_line_tokenized, dolar_cmd, value);
		ms->shell_line_tokenized = aux;
	}
	else
		check_expand(ms, dolar_cmd, aux);
	ft_free_ptr((void *) &no_dolar);
	ft_free_ptr((void *) &dolar_cmd);
}
