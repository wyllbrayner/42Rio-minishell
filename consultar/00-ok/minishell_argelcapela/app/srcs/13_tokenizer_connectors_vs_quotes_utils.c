/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_tokenizer_connectors_vs_quotes_utils.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:09:38 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/19 12:40:40 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ms_replace_connectors_by_token(t_ms *ms, char *tmp)
{
	char	*tmp2;

	tmp2 = NULL;
	if (ft_strnstr(ms->shell_line_tokenized, \
	"&&", ft_strlen(ms->shell_line_tokenized)))
	{
		tmp = ft_strdup(ms->shell_line_tokenized);
		tmp2 = ft_str_replace_all(tmp, "&&", T_CONNECTOR);
	}
	if (ft_strnstr(ms->shell_line_tokenized, \
	"||", ft_strlen(ms->shell_line_tokenized)))
	{
		if (tmp2 != NULL)
		{
			ft_free_ptr((void *) &ms->shell_line_tokenized);
			ms->shell_line_tokenized = tmp2;
		}
		tmp = ft_strdup(ms->shell_line_tokenized);
		tmp2 = ft_str_replace_all(tmp, "||", T_CONNECTOR);
	}
	if (tmp2 == NULL)
		tmp2 = ft_strdup(ms->shell_line_tokenized);
	if (ms->shell_line_tokenized != NULL)
		ft_free_ptr((void *) &ms->shell_line_tokenized);
	ms->shell_line_tokenized = tmp2;
}

int	ms_check_if_have_quotes(t_ms *ms, char *line)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strnstr(line, "\"", ft_strlen(line)) == NULL && \
	ft_strnstr(line, "\'", ft_strlen(line)) == NULL)
	{
		ms_replace_connectors_by_token(ms, tmp);
		if (ft_strnstr(ms->shell_line_tokenized, "|", \
		ft_strlen(ms->shell_line_tokenized)))
		{
			tmp = ft_strdup(ms->shell_line_tokenized);
			ft_free_ptr((void *) &ms->shell_line_tokenized);
			ms->shell_line_tokenized = \
				ft_str_replace_all(tmp, \
			"|", T_PIPE);
		}
		return (1);
	}
	return (0);
}

int	ms_get_index(t_ms *ms)
{
	int		i;
	char	*tmp;

	if (ms->is_aux_env)
		i = 0;
	else if (ms->shell_line[0] == '"' || ms->shell_line[0] == '\'')
		i = 0;
	else
	{
		tmp = ft_chr_to_str(' ', 1);
		i = ft_str_indexof(ms->shell_line, tmp, ft_strlen(ms->shell_line));
		ft_free_ptr((void *)&tmp);
		if (i == -1)
			i = 0;
	}
	return (i);
}

int	ms_jump_to_end_quote(t_ms *ms, char *line, int *i, int size)
{
	int		second;
	char	*line_inside_quotes;
	char	*tmp;
	char	*tmp2;

	second = 0;
	tmp = ft_chr_to_str(line[*i], 1);
	second = ft_str_indexof(line + *i + 1, \
	tmp, size - *i);
	ft_free_ptr((void *) &tmp);
	line_inside_quotes = ft_substr(line, *i + 1, second);
	tmp2 = ft_strdup(ms->aux);
	if (ms->aux)
		ft_free_ptr((void *) &ms->aux);
	ms->aux = ft_printf_to_var("%s%c%s%c", tmp2, line[*i], \
	line_inside_quotes, line[*i]);
	ft_free_ptr((void *) &tmp2);
	ft_free_ptr((void *) &line_inside_quotes);
	return (second + 1);
}

void	subs_replace_join_free(char *find, char *replace, \
t_ms *ms, char *line)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(line, ms->i, ft_strlen(line) - ms->i);
	tmp2 = ft_str_replace_all(tmp, find, replace);
	tmp3 = ft_strdup(ms->aux);
	ft_free_ptr((void *) &ms->aux);
	ms->aux = ft_strjoin_free(tmp3, tmp2);
	ft_free_ptr((void *) &tmp2);
}
