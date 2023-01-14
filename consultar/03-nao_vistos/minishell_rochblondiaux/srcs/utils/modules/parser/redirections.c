/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static t_redirection	get_type(char *a, size_t index)
{
	if (a[index])
	{
		if (a[index] == '>' && a[index + 1] && a[index + 1] == '>')
			return (APPENDER);
		if (a[index] == '<' && a[index + 1] && a[index + 1] == '<')
			return (DELIMITER);
		if (a[index] == '>')
			return (OUTPUT);
		if (a[index] == '<')
			return (INPUT);
	}
	return (NO);
}

static char	*remove_redirection(t_command *cmd, char *raw,
							size_t i, t_redirection r)
{
	size_t	start;
	int		end;
	char	*tmp;
	t_redir	*redir;

	start = i;
	while (get_type(raw, i) != NO || raw[i] == ' ')
		i++;
	end = ft_strchr(&raw[i], ' ');
	if (end == 0)
		end = ft_strlen(raw);
	redir = create_redirection(r, ft_substr(raw, i, end));
	add_redirection(&cmd->redirections, redir);
	tmp = ft_strjoin_properly(ft_substr(raw, 0, start),
			ft_substr(raw, i + end, ft_strlen(raw)));
	free(raw);
	return (tmp);
}

int	contains_redirection(char *raw)
{
	size_t	i;
	int		q;

	i = -1;
	q = 0;
	while (raw[++i])
	{
		is_in_quotes(&q, raw[i]);
		if (q == 0 && get_type(raw, i) != NO)
			return (TRUE);
	}
	return (FALSE);
}

char	*parse_redirections(t_command *command, char *raw)
{
	size_t			i;
	t_redirection	redir;
	int				quotes;

	i = -1;
	quotes = 0;
	while (raw[++i])
	{
		is_in_quotes(&quotes, raw[i]);
		if (quotes != 0)
			continue ;
		redir = get_type(raw, i);
		if (redir != NO)
			return (remove_redirection(command, raw, i, redir));
	}
	return (raw);
}
