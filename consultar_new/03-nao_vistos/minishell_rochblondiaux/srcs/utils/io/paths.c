/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*parent(char *path)
{
	char	**a;
	char	*final;
	size_t	index;

	if (!exists(path))
		return (NULL);
	a = ft_split(path, '/');
	index = -1;
	final = ft_strdup("/");
	while (a[++index])
	{
		if (array_length(a) - 1 != index)
		{
			if (array_length(a) - 2 > index)
				final = ft_strjoin_properly(final,
						ft_strjoin_properly(a[index], ft_strdup("/")));
			else
				final = ft_strjoin_properly(final, a[index]);
		}
		else
			free(a[index]);
	}
	free(path);
	free(a);
	return (final);
}

char	*path(char *raw)
{
	char	*tmp;
	char	*temp;

	if (!raw)
		return (NULL);
	if (raw[ft_strlen(raw) - 1] != '/')
		temp = ft_strjoin(raw, "/");
	else
		temp = ft_strdup(raw);
	if (exists(temp) && raw[0] == '/')
		return (temp);
	tmp = ft_strjoin_properly(working_directory(), ft_strdup("/"));
	tmp = ft_strjoin_properly(tmp, temp);
	if (!exists(tmp))
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

int	is_relative(char *path)
{
	return (path && path[0] && path[0] != '/');
}
