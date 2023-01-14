/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

size_t	ft_strlen_lastrepo(char *s)
{
	size_t	i;

	i = ft_strlen(s);
	while (--i > 0)
	{
		if (s[i] == '/')
			return (i);
	}
	return (1);
}

static char	*chose_cdpath(t_app *app, char *input, char *arg)
{
	free(input);
	input = ft_strjoin(get_env(app, "CDPATH"), arg);
	return (input);
}

static char	*chose_path(t_app *app, char *input, char **split)
{
	size_t	j;

	j = -1;
	while (split[++j])
	{
		if (ft_strcmp(split[j], ".") || ft_strcmp(split[j], ".."))
			reset_str(&input, get_rep_path(input, split[j], j));
		else
		{
			if (j == 0)
				input = chose_cdpath(app, input, split[j]);
			else
				input = get_new_path(input, split[j]);
		}
	}
	printf("%s\n", input);
	return (input);
}

char	*cdpath_exist(t_app *app, char *input, char **split)
{
	if (get_env(app, "CDPATH") && get_env(app, "CDPATH")[0])
		input = chose_path(app, input, split);
	free_array(split);
	return (input);
}

char	*is_a_path(char *input, char **split)
{
	size_t	j;
	char	*temp;
	char	*tmp;

	j = -1;
	tmp = ft_strdup(input);
	while (split[++j])
	{
		if (ft_strcmp(split[j], ".") || ft_strcmp(split[j], ".."))
			reset_str(&input, get_rep_path(input, split[j], j));
		else
		{
			free(input);
			input = ft_strjoin_properly(working_directory(),
					ft_strjoin("/", split[j]));
		}
		temp = path(input);
		if (!temp)
			reset_str(&input, ft_strdup(tmp));
		free(temp);
	}
	free(tmp);
	free_array(split);
	return (input);
}
