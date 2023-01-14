/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 15:08:15 by paugusto          #+#    #+#             */
/*   Updated: 2022/01/08 15:08:20 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_var(t_mini *mini, t_node *node, int i)
{
	char		*holder;

	holder = transform(mini, node, i, 0);
	if (holder != NULL)
	{
		free(node->str[i]);
		node->str[i] = ft_strdup(holder);
		free(holder);
	}
	else
	{
		free(node->str[i]);
		node->str[i] = ft_strdup(" ");
	}
}
