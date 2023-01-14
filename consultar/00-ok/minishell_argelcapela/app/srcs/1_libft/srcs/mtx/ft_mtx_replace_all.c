/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtx_replace_all.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:47:50 by acapela-          #+#    #+#             */
/*   Updated: 2022/10/12 20:08:24 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

char	**ft_mtx_replace_all(char **matrix, char *search, char *replace)
{
	char	*tmp;
	int		i;

	i = 0;
	while (i < ft_mtx_size((void **) matrix))
	{
		if (ft_strnstr(matrix[i], search, ft_strlen(matrix[i])) != NULL)
		{
			tmp = ft_strdup(matrix[i]);
			ft_free_ptr((void *) &(matrix[i]));
			matrix[i] = ft_str_replace_all(tmp, search, replace);
		}
		i++;
	}
	return (matrix);
}
