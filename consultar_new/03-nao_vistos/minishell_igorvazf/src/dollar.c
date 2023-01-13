/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:19:02 by paugusto          #+#    #+#             */
/*   Updated: 2022/01/08 15:07:58 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_var_content(t_mini *mini, char *key)
{
	t_nodenv	*node_env;

	node_env = mini->env->begin;
	while (node_env != NULL)
	{
		if (!ft_strcmp(node_env->key, key))
			return (ft_strdup(node_env->content));
		node_env = node_env->next;
	}
	return (NULL);
}

char	*get_var(t_mini *mini, char *str, int i)
{
	char	*var;
	char	*content;
	int		len;
	int		j;

	len = 0;
	j = i;
	while (str[i] && str[i] != '$')
	{
		len++;
		i++;
	}
	if (len > 0)
	{
		var = malloc (sizeof(char) * len + 1);
		i = 0;
		while (str[j] && str[j] != '$' && str[j] != D_QUOTE)
			var[i++] = str[j++];
		var[i] = '\0';
		content = get_var_content(mini, var);
		free(var);
		return (content);
	}
	return (NULL);
}

char	*get_join(char *str)
{
	int		i;
	char	*aux;

	i = 0;
	if (str[i] == '$')
		return (NULL);
	while (str[i] && str[i] != '$')
		i++;
	aux = ft_substr(str, 0, i - 1);
	return (aux);
}

char	*get_content(t_mini *mini, t_node *node, int i, int j)
{
	char	*content;

	content = NULL;
	if (node->str[i][j + 1] == '?')
		content = ft_itoa(g_return);
	else
		content = get_var(mini, node->str[i], j + 1);
	return (content);
}

char	*transform(t_mini *mini, t_node *node, int i, int j)
{
	char	*content;
	char	*holder;
	char	*aux;

	content = NULL;
	holder = get_join(node->str[i]);
	while (node->str[i][j])
	{
		if (node->str[i][j] == '$')
		{
			content = get_content(mini, node, i, j);
			if (content != NULL)
			{
				aux = holder;
				if (holder == NULL)
					aux = ft_strdup("");
				holder = ft_strjoin(aux, content);
				free(aux);
				free(content);
			}
		}
		j++;
	}
	return (holder);
}
