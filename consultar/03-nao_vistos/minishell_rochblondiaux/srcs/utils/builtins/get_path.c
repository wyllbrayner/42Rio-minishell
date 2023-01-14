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

static char	*get_old_path(t_app *app)
{
	char	*old;

	old = get_env(app, "OLDPWD");
	if (!old)
	{
		error(app, "cd", OLDPWD_UNDEFINED);
		return (NULL);
	}
	return (ft_strdup(old));
}

char	*get_new_path(char *input, char *arg)
{
	char	*temp;

	temp = ft_strjoin_properly(input, ft_strdup("/"));
	input = ft_strjoin_properly(temp, ft_strdup(arg));
	return (input);
}

char	*get_rep_path(char *input, char *arg, int j)
{
	char	*temp;
	char	*path;

	path = NULL;
	if (ft_strcmp(arg, "."))
		path = working_directory();
	else if (ft_strcmp(arg, ".."))
	{
		if (j == 0)
			temp = working_directory();
		else
			temp = ft_strdup(input);
		path = ft_substr(temp, 0, ft_strlen_lastrepo(temp));
		free (temp);
	}
	return (path);
}

static char	*get_good_dir(t_app *app)
{
	if (home_directory(app) && !home_directory(app)[0])
		return (working_directory());
	if (!home_directory(app))
		return (NULL);
	return (ft_strdup(home_directory(app)));
}

char	*get_path(t_app *app, char *input)
{
	char	**split;
	char	*i;

	if (!input)
		return (get_good_dir(app));
	if (ft_strcmp(input, "-"))
	{
		i = get_old_path(app);
		if (!i)
			return (NULL);
		printf("%s\n", i);
	}
	else
	{
		split = ft_split(input, '/');
		if (!split)
			i = get_new_path(working_directory(), input);
		i = path(input);
		if (i)
			i = is_a_path(i, split);
		else
			reset_str(&i, cdpath_exist(app, ft_strdup(input), split));
	}
	return (i);
}
