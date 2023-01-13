/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c 	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	has_close_quote(t_app *app, char *s)
{
	t_prompt_mode	mode;

	if (!s)
		return (0);
	mode = app->mode;
	return ((mode == D_QUOTE && ft_contains(s, '"') % 2 == 1)
		|| (mode == QUOTE && ft_contains(s, '\'') % 2 == 1));
}

char	*get_right_prompt(t_app *app)
{
	if (app->mode == D_QUOTE)
		return (D_QUOTE_PROMPT);
	else if (app->mode == QUOTE)
		return (QUOTE_PROMPT);
	else if (app->mode == DELIMIT)
		return (DELIMIT_PROMPT);
	return (PROMPT_SYMBOL);
}

static void	update_mode(t_app *app, char *input)
{
	if (!input || ft_strlen(input) == 0)
		return ;
	if (ft_contains(input, '"') == 1
		&& (ft_strchr(input, '\'') == 0
			|| ft_strchr(input, '\'') > ft_strchr(input, '"')))
		app->mode = D_QUOTE;
	else if (ft_contains(input, '\'') == 1
		&& (ft_strchr(input, '"') == 0
			|| ft_strchr(input, '"') > ft_strchr(input, '\'')))
		app->mode = QUOTE;
	else if (ft_contains_delim(input) != FALSE)
		app->mode = DELIMIT;
	else
		app->mode = NORMAL;
}

char	*get_arg(t_app *app)
{
	char	*input;
	char	*tmp;

	tmp = ft_strdup("");
	while (1)
	{
		input = readline(get_right_prompt(app));
		if (!input || has_close_quote(app, input))
			break ;
		if (app->mode == NORMAL)
		{
			free(tmp);
			return (ft_strtrim(input, "\n"));
		}
		tmp = ft_strjoin_properly(ft_strjoin_properly(tmp,
					input), ft_strdup("\n"));
	}
	tmp = ft_strjoin_properly(tmp, input);
	if (!input)
		return (NULL);
	return (tmp);
}

void	handle_mode(t_app *app, char *input, char **ret)
{
	char	*tmp;

	update_mode(app, input);
	if (app->mode == NORMAL || app->mode == DELIMIT)
		return ;
	tmp = get_arg(app);
	if (app->mode == NORMAL || !tmp)
		return (reset_str(ret, tmp));
	input = ft_strjoin_properly(input, ft_strdup("\n"));
	*ret = ft_strjoin_properly(input, tmp);
}
