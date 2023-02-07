/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:44:12 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/03 15:00:22 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

static int	ft_countwords(char const *str, char c)
{
	int	con;
	int	i;
	int	w;

	con = 0;
	w = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && con == 0)
		{
			con = 1;
			w++;
		}
		else if (str[i] == c)
			con = 0;
		i++;
	}
	return (w);
}

static int	ft_wordsize(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static void	init_vars(int	*len, int	*con, int *i, int	*j)
{
	*j = 0;
	*i = 0;
	*len = 0;
	*con = 0;
}

static char	**ft_tosplit(const char *s, char c, char **split)
{
	int	len;
	int	con;
	int	i;
	int	j;

	init_vars(&len, &con, &i, &j);
	while (s[i])
	{
		if (s[i] != c && con == 0)
		{
			con = 1;
			if ((s + i) != NULL)
				len = ft_wordsize(s + i, c);
			else
				len = 0;
			split[j] = (char *) ft_calloc ((len + 1), sizeof(char));
			if (split[j] != NULL)
				ft_strlcpy (split[j], s + i, len + 1);
			j++;
		}
		else if (s[i] == c)
			con = 0;
		i++;
	}
	return (split);
}

char	**ft_split(char *s, char c)
{
	char	**split;
	int		words;

	if (!s)
		return (0);
	s[ft_strlen(s)] = '\0';
	words = ft_countwords(s, c);
	split = (char **) ft_calloc ((words + 1), sizeof(char **));
	if (!split)
		return (NULL);
	split = ft_tosplit(s, c, split);
	split[words] = NULL;
	return (split);
}
