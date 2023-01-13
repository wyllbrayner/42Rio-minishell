/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**sub_array(char **array, size_t start, size_t length)
{
	char	**new;
	size_t	index;

	if (!array)
		return (array);
	if (start >= length || length > array_length(array))
		return (empty_array());
	index = start - 1;
	new = malloc(sizeof (char *) * (length - start + 1));
	if (!new)
		return (NULL);
	while (array[++index] && index < length)
		new[index - start] = ft_strdup(array[index]);
	new[index - start] = NULL;
	return (new);
}
