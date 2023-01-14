/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:01:39 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:16 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	int		index;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		new = malloc(sizeof(char));
		new[0] = '\0';
		return (new);
	}
	index = 0;
	while (s[start + index] && index < (int) len)
		index++;
	new = malloc((index + 1) * sizeof(char));
	if (!new)
		return (NULL);
	index = 0;
	while (s[start + index] && index < (int) len)
	{
		new[index] = s[start + index];
		index++;
	}
	new[index] = '\0';
	return (new);
}
