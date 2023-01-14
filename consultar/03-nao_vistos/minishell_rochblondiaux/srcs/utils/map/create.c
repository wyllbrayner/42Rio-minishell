/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/17 14:33:07 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_no_equal(char *entry)
{
	size_t	i;

	i = -1;
	while (entry[++i])
	{
		if (entry[i] == '=')
			return (TRUE);
	}
	return (FALSE);
}

static char	*give_env_value(char **entry)
{
	char	*dest;
	size_t	i;

	i = 1;
	while (entry[i])
	{
		if (i == 1)
			dest = ft_strdup(entry[i]);
		else
			dest = ft_strjoin_properly(dest, ft_strdup(entry[i]));
		if (entry[i + 1])
			dest = ft_strjoin_properly(dest, ft_strdup("="));
		i ++;
	}
	return (dest);
}

t_env	*create_map_element(char *entry)
{
	char	**e;
	t_env	*env;

	if (is_no_equal(entry) == FALSE)
		return (NULL);
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	e = ft_split(entry, '=');
	env->key = ft_strdup(e[0]);
	if (array_length(e) >= 2)
		env->value = give_env_value(e);
	else
		env->value = ft_strdup("");
	if (ft_strcmp(env->key, "SHLVL"))
		reset_str(&env->value, ft_itoa(ft_atoi(env->value) + 1));
	env->next = NULL;
	free_array(e);
	return (env);
}
