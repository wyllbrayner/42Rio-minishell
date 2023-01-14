/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_tokenizer_connectors_vs_quotes_bonus.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:09:38 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/17 17:11:19 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	ms_treating_having_quotes_3(t_ms *ms, int i, int size, char *line)
{
	char	*tmp;
	char	*tmp2;

	ms->i = i;
	if (!ft_strnstr(line, "&&", ft_strlen(line)) \
	&& !ft_strnstr(line, "||", ft_strlen(line)) \
	&& !ft_strnstr(line, "|", ft_strlen(line)))
	{
		tmp = ft_substr(line, i, size - i);
		tmp2 = ft_strdup(ms->aux);
		ft_free_ptr((void *) &ms->aux);
		ms->aux = ft_strjoin_free(tmp2, tmp);
		free(tmp);
		return ;
	}
	if (ft_strnstr(line, "&&", ft_strlen(line)))
		subs_replace_join_free("&&", T_CONNECTOR, ms, line);
	if (ft_strnstr(line, "||", ft_strlen(line)))
		subs_replace_join_free("||", T_CONNECTOR, ms, line);
	if (ft_strnstr(line, "|", ft_strlen(line)))
		subs_replace_join_free("|", T_PIPE, ms, line);
}

static void	ms_treating_having_quotes_2(t_ms *ms, int *i, char *line, int i_aux)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(line + *i, 0, i_aux);
	*i += i_aux - 1;
	tmp2 = ft_strdup(tmp);
	ft_free_ptr((void *) &tmp);
	tmp = ft_str_replace_all(tmp2, "&&", T_CONNECTOR);
	tmp2 = ft_strdup(tmp);
	ft_free_ptr((void *) &tmp);
	tmp = ft_str_replace_all(tmp2, "||", T_CONNECTOR);
	tmp2 = ft_strdup(tmp);
	ft_free_ptr((void *) &tmp);
	tmp = ft_str_replace_all(tmp2, "|", T_PIPE);
	tmp2 = ft_strdup(ms->aux);
	ft_free_ptr((void *) &ms->aux);
	ms->aux = ft_strjoin_free(tmp2, tmp);
	ft_free_ptr((void *) &tmp);
}

static void	ms_treating_having_quotes_1(int index_double, int index_single, \
int *i_aux)
{
	if (index_double != -1 && index_single \
		!= -1 && index_double < index_single)
		*i_aux = index_double;
	else if (index_double != -1 && index_single \
		!= -1 && index_single < index_double)
		*i_aux = index_single;
	if (index_double != -1 && index_single == -1)
		*i_aux = index_double;
	else if (index_single != -1 && index_double == -1)
		*i_aux = index_single;
}

static void	ms_treating_having_quotes(t_ms *ms, int *i, int size, char *line)
{
	int		index_double;
	int		index_single;
	int		i_aux;

	if (line[*i] == '"' || line[*i] == '\'')
		*i += ms_jump_to_end_quote(ms, line, i, size);
	else
	{
		index_double = ft_str_indexof(line + *i, "\"", size);
		index_single = ft_str_indexof(line + *i, "\'", size);
		if (index_double != -1 || index_single != -1)
		{
			ms_treating_having_quotes_1(index_double, index_single, &i_aux);
			ms_treating_having_quotes_2(ms, i, line, i_aux);
		}
		else
		{
			ms_treating_having_quotes_3(ms, *i, size, line);
			*i = size - 1;
			return ;
		}
	}
}

void	ms_quotes_vs_connectors(t_ms *ms, char *line)
{
	int		i;
	int		size;

	i = 0;
	size = (int) ft_strlen(line);
	if (!line || ms_check_if_have_quotes(ms, line) == 1)
		return ;
	ms->aux = ft_strdup("");
	while (line[i])
	{
		ms_treating_having_quotes(ms, &i, size, line);
		i++;
	}
	ft_free_ptr((void *) &ms->shell_line_tokenized);
	ms->shell_line_tokenized = ft_strdup(ms->aux);
}
