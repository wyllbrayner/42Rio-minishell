/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static size_t	size_env(t_env *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**format_env(t_app *app)
{
	char	**v;
	t_env	*e;
	size_t	i;

	v = malloc(sizeof (char *) * (size_env(app->env) + 1));
	e = app->env;
	i = 0;
	while (e)
	{
		v[i] = ft_strjoin_properly(ft_strjoin(e->key, "="),
				ft_strdup(e->value));
		i++;
		e = e->next;
	}
	v[i] = NULL;
	return (v);
}
