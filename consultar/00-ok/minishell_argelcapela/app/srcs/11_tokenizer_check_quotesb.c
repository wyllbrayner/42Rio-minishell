/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_tokenizer_check_quotesb.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/19 15:37:35 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	ms_count_char(char *str, char c)
{
	int		count;
	char	*iter;
	int		i;

	i = 0;
	count = 0;
	iter = ft_strdup(str);
	while (iter[i])
	{
		if (iter[i] == c)
			count++;
		i++;
	}
	ft_free_ptr((void *) &iter);
	return (count);
}

void	line_inside_quotes_replaces(t_ms *ms, char **line_inside_quotes,
int first, int second)
{
	(*line_inside_quotes) = ft_substr(ms->shell_line, first + 1, second);
	(*line_inside_quotes) = ft_super_replace_all((*line_inside_quotes), 16,
			"<<", T_HEREDOC,
			">>", T_OUTPUT2,
			"<", T_INPUT,
			">", T_OUTPUT1,
			"(", T_LEFTP,
			")", T_RIGHTP,
			"&", T_E_COMER,
			"|", T_PIPE2);
}

//echo "$USER --- $USER açsdklfjasdlkf < << > >> () && || |"