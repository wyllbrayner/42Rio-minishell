/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**add_array_element(char **array, char *element)
{
	size_t	index;
	char	**a;

	a = malloc(sizeof(char *) * (array_length(array) + 2));
	index = -1;
	a[0] = ft_strdup(element);
	while (array[++index])
		a[index + 1] = ft_strdup(array[index]);
	a[index + 1] = NULL;
	return (a);
}
