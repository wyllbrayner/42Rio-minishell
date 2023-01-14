/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c 	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_app	*load_application(char **env)
{
	t_app	*app;

	app = malloc(sizeof(t_app));
	if (!app)
	{
		str_error(app, APP_INITIALIZATION_FAILED);
		exit(EXIT_FAILURE);
	}
	app->env = init_env_map(env);
	app->mode = NORMAL;
	app->exit = 0;
	app->last_exit = 0;
	return (app);
}
