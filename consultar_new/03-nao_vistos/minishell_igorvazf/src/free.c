/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:54:03 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/31 16:51:04 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minifree(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	free_reset(t_mini *mini, t_list *list)
{
	free_list(&list);
	if (ft_strlen(mini->input) > 0)
	{
		if (mini->input[0] == '|')
			printf("minishell: syntax error. Unexpected token \'|\'\n");
		free(mini->input);
	}
	free(mini->input_sanitized);
	if (mini->correct_path != NULL)
		free(mini->correct_path);
}

void	free_em_all(t_mini *mini)
{
	t_env	*env;

	env = mini->env;
	free_env(&env);
	minifree(mini->path);
	free(mini->home);
}
