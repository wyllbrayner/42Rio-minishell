/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/03/17 14:13:25 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
				return (i);
			j++;
		}
	}
	return (ft_strlen(str));
}

char	*replace_first(char *str, char *find, char *replace)
{
	int		start;
	char	*after;
	char	*tmp;

	start = ft_strstr(str, find);
	if (start >= (int) ft_strlen(str))
		return (str);
	tmp = ft_strjoin_properly(ft_substr(str, 0, start), ft_strdup(replace));
	if (start + ft_strlen(find) == ft_strlen(str))
		return (tmp);
	after = ft_substr(str, start + ft_strlen(find), ft_strlen(str));
	return (ft_strjoin_properly(tmp, after));
}

char	*replace_str(char *str, char *find, char *replace)
{
	char	*tmp;

	tmp = ft_strdup(str);
	while (ft_strstr(tmp, find) < (int) ft_strlen(tmp))
		reset_str(&tmp, replace_first(tmp, find, replace));
	return (tmp);
}
