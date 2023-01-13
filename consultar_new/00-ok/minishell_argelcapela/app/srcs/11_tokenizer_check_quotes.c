/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_tokenizer_check_quotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/19 15:32:50 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	treat_having_quotes_3(t_ms *ms, char *tmp, int *i, int size)
{
	int		final;
	char	*tmp2;
	char	*tmp3;

	final = size - *i + 1;
	if (final != -1)
	{
		tmp2 = ft_substr(ms->shell_line, *i + 1, final);
		tmp3 = ft_printf_to_var("%s%s", \
		tmp, tmp2);
		ft_free_ptr((void *) &tmp2);
		ft_free_ptr((void *) &tmp);
		ft_free_ptr((void *) &ms->shell_line_tokenized);
		ms->shell_line_tokenized = tmp3;
	}
	else
		ms->shell_line_tokenized = tmp;
}

static char	*treat_having_quotes_2(t_ms *ms, int *i, int first, int second)
{
	char	*aux;
	char	*aux2;
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	line_inside_quotes_replaces(ms, &tmp2, first, second);
	aux = ft_str_replace_all(tmp2, " ", T_SPACE);
	aux2 = ft_substr(ms->shell_line, 0, *i);
	tmp = ft_printf_to_var("%s%c%s%c", aux2, \
	ms->shell_line[*i], aux, ms->shell_line[*i]);
	*i += second + 1;
	ft_free_ptr((void *) &aux);
	ft_free_ptr((void *) &aux2);
	return (tmp);
}

static int	treat_having_quotes(t_ms *ms, int *i)
{
	int		first;
	int		second;
	int		size;
	char	*tmp;
	char	*aux;

	size = (int) ft_strlen(ms->shell_line) - 1;
	first = *i;
	aux = ft_chr_to_str(ms->shell_line[*i], 1);
	second = ft_str_indexof(ms->shell_line + first + 1, \
	aux, size - *i);
	ft_free_ptr((void *) &aux);
	tmp = treat_having_quotes_2(ms, i, first, second);
	treat_having_quotes_3(ms, tmp, i, size);
	return (0);
}

int	ms_check_quotes(t_ms *ms)
{
	int		i;
	char	**cmd;

	cmd = ft_split(ms->shell_line, ' ');
	i = -1;
	if (ft_strchr(ms->shell_line_tokenized, '\'') || \
		ft_strchr(ms->shell_line_tokenized, '"'))
	{
		while (ms->shell_line[++i])
		{
			if (ms->shell_line[i] != '"' && ms->shell_line[i] != '\'')
				continue ;
			if (ft_strrchr(&ms->shell_line[i + 1],
					ms->shell_line[i]) == NULL)
			{
				ft_putstr_fd("miniheaven: close your quotes\n", 1);
				ft_mtx_free((void **) cmd);
				set_exit_code(ms, NULL, 1);
				return (1);
			}
			treat_having_quotes(ms, &i);
		}
	}
	ft_mtx_free((void **) cmd);
	return (0);
}

// echo "exit_code ->$? user ->$USER home -> $HOME"