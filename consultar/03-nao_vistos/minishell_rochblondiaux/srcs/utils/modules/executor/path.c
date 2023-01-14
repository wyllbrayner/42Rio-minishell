/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/17 14:12:30 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static char	*get_accurate_path(char *path, char *name)
{
	char	*final;
	char	*tmp;

	if (access(name, F_OK) == FALSE)
		return (ft_strdup(name));
	if (path[ft_strlen(path) - 1] != '/')
		tmp = ft_strjoin(path, "/");
	else
		tmp = ft_strdup(path);
	final = ft_strjoin(tmp, name);
	free(tmp);
	return (final);
}

static char	*exec_errors(t_app *app, t_command *cmd, char *tmp, char *input)
{
	if (input[0] == '.' && input[1] == '/')
	{
		cmd->status = 126;
		errno = 13;
		str_error(app, cmd->name);
	}
	else if (input[0] != '$')
	{
		cmd->status = 127;
		error(app, cmd->name, COMMAND_NOT_FOUND);
	}
	free(tmp);
	return (ft_strdup(""));
}

static char	*no_path(t_app *app, t_command *cmd)
{
	char	**split;
	size_t	j;

	cmd->status = 127;
	split = ft_split(cmd->name, '/');
	j = array_length(split) - 1;
	errno = 2;
	str_error(app, split[j]);
	return (ft_strdup(""));
}

static char	*free_all_arr(char *path, char **paths, char *s)
{
	free(path);
	free_array(paths);
	return (s);
}

char	*get_executable(t_app *a, t_command *b, char *c)
{
	char		**paths;
	int			i;
	char		*path;
	char		*t;

	i = -1;
	if (get_env(a, "PATH") == NULL)
		return (no_path(a, b));
	if (c[0] == '.' && c[1] == '/')
		return (ft_strdup(c));
	if ((access(c, F_OK) == FALSE))
		return (right_file(c));
	paths = ft_split(get_env(a, "PATH"), ':');
	path = NULL;
	while (paths[++i])
	{
		t = get_accurate_path(paths[i], c);
		if (t && !path && access(t, F_OK) == FALSE)
			path = ft_strdup(t);
		else if (access(t, F_OK | X_OK) == 0)
			return (free_all_arr(path, paths, exec_errors(a, b, t, c)));
		free(t);
	}
	free_array(paths);
	return (path);
}
