/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_tokenizer_sintax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 06:14:16 by argel             #+#    #+#             */
/*   Updated: 2022/12/14 06:44:14 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static int	connectors_are_wrong(char *c)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(c);
	while (c[i])
	{
		if (ft_strncmp(&c[i], "&", len) == 0
			|| ft_strncmp(&c[i], "|", len) == 0
			|| ft_strncmp(&c[i], ";", len) == 0
			|| ft_strncmp(&c[i], "<", len) == 0
			|| ft_strncmp(&c[i], "<", len) == 0
			|| ft_strncmp(&c[i], "<<", len) == 0
			|| ft_strncmp(&c[i], ">>", len) == 0)
		{
			if ((c[len - 1] == c[i])
				|| (((i + 2) <= (len - 1)) && (c[i + 2] == c[i])))
			{
				ft_pf_error("miniheaven:%s '%c'\n", E_BADSINTAX, c[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static int	subshell_wrong2( int i, char *c)
{
	if ((c[i] == '(' && ft_count_chr(c, ')') == 0)
		|| (c[i] == ')' && ft_count_chr(c, '(') == 0))
	{
		ft_pf_error("miniheaven:%s '%c'\n", E_BADSINTAX, c[i]);
		return (1);
	}
	return (0);
}

int	subshell_wrong(char *c)
{
	int		i;
	int		size;
	char	*tmp;

	i = 0;
	size = ft_strlen(c);
	while (i < size)
	{
		if (c[i] == '"' || c[i] == '\'')
		{
			i++;
			tmp = ft_chr_to_str(c[i], 1);
			i += ft_str_indexof(c, tmp, size);
			ft_free_ptr((void *) &tmp);
		}
		if (i < size && subshell_wrong2(i, c))
			return (1);
		i++;
	}
	return (0);
}

int	dont_confuse_heredoc(char *c)
{
	int		i;

	i = 0;
	while (c[i])
	{
		if (c[i] != '<')
			return (0);
		i++;
	}
	ft_pf_error("miniheaven:%s \n", E_BADSINTAX);
	return (1);
}

int	ms_sintax(t_ms *ms)
{
	char	*tmp;

	tmp = ft_strdup(ms->shell_line);
	if (connectors_are_wrong(tmp)
		|| dont_confuse_heredoc(tmp)
		|| all_equal(tmp))
	{
		ft_free_ptr((void *) &tmp);
		return (1);
	}
	ft_free_ptr((void *) &tmp);
	return (0);
}
