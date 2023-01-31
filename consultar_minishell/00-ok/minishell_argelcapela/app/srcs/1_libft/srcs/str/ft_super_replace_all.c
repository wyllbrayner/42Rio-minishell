/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_super_replace_all.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:46:08 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/02 21:06:59 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

char	*ft_super_replace_all(char *str, int n, ...)
{
	va_list	vl;
	char	*arg1;
	char	*arg2;
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	va_start(vl, n);
	while (i < n)
	{
		arg1 = va_arg(vl, char *);
		arg2 = va_arg(vl, char *);
		tmp = ft_strdup(str);
		ft_free_ptr((void *) &str);
		str = ft_str_replace_all(tmp, arg1, arg2);
		i += 2;
	}
	va_end(vl);
	return (str);
}
