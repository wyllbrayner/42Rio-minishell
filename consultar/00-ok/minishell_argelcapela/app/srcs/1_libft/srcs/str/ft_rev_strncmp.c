/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_strncmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:45:28 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/01 16:10:16 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

static size_t	ft_max(char *s1, char *s2, int *d1, int *d2)
{
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 > len2)
	{
		*d2 = len1 - len2;
		return (len1);
	}
	else
	{
		*d1 = len2 - len1;
		return (len2);
	}
}

int	ft_rev_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		d1;
	int		d2;

	d1 = 0;
	d2 = 0;
	if (n == 0)
		return (0);
	i = ft_max((char *)s1, (char *)s2, &d1, &d2) - 1;
	n = i - n;
	while (i > n && s1[i - d1] == s2[i - d2])
	{
		if (i == (n + 1))
			return (0);
		i--;
	}
	return (-1);
}
