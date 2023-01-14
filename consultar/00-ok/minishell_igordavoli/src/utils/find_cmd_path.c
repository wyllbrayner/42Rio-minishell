/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 02:18:04 by idavoli-          #+#    #+#             */
/*   Updated: 2022/09/11 03:48:41 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static char	**get_paths(void)
{
	t_dlist	*envs;

	envs = g_msh.envp_lst;
	while (envs != NULL && ft_strncmp(get_node_value(envs), "PATH=", 5))
		envs = envs->next;
	if (envs != NULL)
		return (ft_split(get_node_value(envs) + 5, ':'));
	else
		return (ft_split("", ':'));
}

static char	*join_path(char *path, char *cmd)
{
	char	*tmp;

	tmp = ft_strjoin("/", cmd);
	return (ft_strjoin2(path, tmp, 0, 1));
}

char	*find_cmd_path(char *cmd)
{
	int		i;
	char	*whole_name;
	char	**path_list;

	path_list = get_paths();
	i = 0;
	while (path_list[i])
	{
		whole_name = join_path(path_list[i], cmd);
		if (cmd != NULL && (!access(cmd, F_OK) || !access(whole_name, F_OK)))
		{
			free_matrix(path_list);
			if (!access(cmd, F_OK))
				return (cmd);
			else if (!access(whole_name, F_OK))
				return (whole_name);
		}
		free(whole_name);
		i++;
	}
	free_matrix(path_list);
	return (NULL);
}
