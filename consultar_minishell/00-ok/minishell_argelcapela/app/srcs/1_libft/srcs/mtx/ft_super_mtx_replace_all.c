/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_super_mtx_replace_all.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:46:08 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/03 15:16:36 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

void	mtx_free(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		ft_free_ptr((void *) &matrix[i]);
		i++;
	}
	ft_free_ptr((void *) &matrix);
	matrix = NULL;
}

char	**ft_super_mtx_replace_all(char **mtx, int n, ...)
{
	va_list	vl;
	char	*arg1;
	char	*arg2;
	int		i;
	char	**n_mtx;

	i = 0;
	va_start(vl, n);
	while (i < n)
	{
		arg1 = va_arg(vl, char *);
		arg2 = va_arg(vl, char *);
		n_mtx = ft_mtx_replace_all(mtx, arg1, arg2);
		mtx = n_mtx;
		i += 2;
	}
	va_end(vl);
	return (mtx);
}
