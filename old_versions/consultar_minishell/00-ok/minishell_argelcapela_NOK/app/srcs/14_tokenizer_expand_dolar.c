/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_tokenizer_expand_dolar.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:55:01 by argel             #+#    #+#             */
/*   Updated: 2022/12/17 16:39:18 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	ms_quotes_something_1(t_ms *ms, char **line_splited, int i)
{
	int	index_double;
	int	index_single;

	index_double = ft_str_indexof(line_splited[i], \
	"\"", ft_strlen(line_splited[i]) - 1);
	index_single = ft_str_indexof(line_splited[i], "'", \
	ft_strlen(line_splited[i]) - 1);
	if (index_double != -1 && index_single \
	!= -1 && index_double < index_single)
		ms->has_double_quotes = 1;
	else if (index_double != -1 && index_single \
	!= -1 && index_single < index_double)
		ms->has_single_quotes = 1;
	if (index_double != -1 && index_single == -1)
		ms->has_double_quotes = 1;
	else if (index_single != -1 && index_double == -1)
		ms->has_single_quotes = 1;
	if (ms_count_char(line_splited[i], '\'') == 1)
		ms->has_single_quotes = 0;
	if (ms_count_char(line_splited[i], '"') == 1)
		ms->has_double_quotes = 0;
}

void	ms_expand_dolar_loop(t_ms *ms, char **line_splited, int i)
{
	char	*dolar_cmd;

	dolar_cmd = NULL;
	ms->has_double_quotes = 0;
	ms->has_single_quotes = 0;
	ms_quotes_something_1(ms, line_splited, i);
	if (ft_strchr(line_splited[i], '$') == NULL || ms->has_single_quotes)
		(void) i;
	else if (ft_strncmp(ms->shell_line_tokenized,
			"$", ft_strlen(ms->shell_line_tokenized)) != 0)
		threat_dolar(ms, line_splited, i, dolar_cmd);
	if (ms->has_double_quotes)
		ft_chr_remove_all(ms->shell_line_tokenized, '"');
	if (ms->has_single_quotes)
		ft_chr_remove_all(ms->shell_line_tokenized, '\'');
}
// if (ms->has_double_quotes || ms->has_single_quotes)
// {
// 	dolar_cmd = ft_super_replace_all(ms->shell_line_tokenized, 8,
// 			"<<", T_HEREDOC,
// 			">>", T_OUTPUT2,
// 			"<", T_INPUT,
// 			">", T_OUTPUT1);
// 	ms->shell_line_tokenized = dolar_cmd;
// }

void	ms_expand_dolar(t_ms *ms)
{
	char		**line_splited;
	int			i;
	char		*tmp;

	i = -1;
	tmp = ft_str_replace_all(ms->shell_line_tokenized, "$EMPTY", "");
	ms->shell_line_tokenized = tmp;
	line_splited = ft_split(ms->shell_line_tokenized, ' ');
	while (line_splited[++i])
		ms_expand_dolar_loop(ms, line_splited, i);
	ft_mtx_free((void **) line_splited);
}
