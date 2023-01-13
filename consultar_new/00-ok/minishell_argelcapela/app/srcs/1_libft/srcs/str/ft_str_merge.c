/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_merge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:39:46 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 15:17:52 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

char	*ft_str_merge(char *s1, char *s2)
{
	size_t	total;
	char	*new;

	if (!s1 || !s2)
	{
		ft_free_ptr((void *) &s1);
		ft_free_ptr((void *) &s2);
		return (NULL);
	}
	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = (char *)malloc(sizeof(char) * total);
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1, ft_strlen(s1) + 1);
	ft_strlcat(new, s2, total);
	ft_free_ptr((void *) &s1);
	ft_free_ptr((void *) &s2);
	return (new);
}
