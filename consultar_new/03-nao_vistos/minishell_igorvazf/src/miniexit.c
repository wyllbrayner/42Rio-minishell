/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:35:22 by paugusto          #+#    #+#             */
/*   Updated: 2022/01/07 12:27:38 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	miniexit(t_mini *mini, t_node *node, t_list *list)
{
	int	code;
	int	i;

	code = 0;
	i = 0;
	while (node->str[i])
		i++;
	if (i > 2)
		printf("exit: too many arguments\n");
	else
	{
		if (node->str[1] && ft_strcmp(node->str[1], "exit"))
			code = ft_atoi(node->str[1]);
		free_reset(mini, list);
		free_em_all(mini);
		close(mini->st_out);
		close(mini->st_in);
		exit(code);
	}
}
