/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_by_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:44:12 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/11 22:33:35 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

static int	ft_countwords(char *str, char *token)
{
	char	*tmp;
	char	*tmp_free;
	int		w;

	w = 0;
	tmp = ft_strdup(str);
	tmp_free = tmp;
	while (*tmp)
	{
		if (ft_strnstr(tmp, token, ft_strlen(token)))
			w++;
		tmp++;
	}
	ft_free_ptr((void *) &tmp_free);
	return (w);
}

static int	ft_wordlen(char *str, char *token)
{
	char	*tmp;
	char	*tmp_free;
	int		len;

	len = 0;
	tmp = str;
	tmp_free = tmp;
	while (*tmp)
	{
		if (ft_strnstr(tmp, token, ft_strlen(token)) == NULL)
			len++;
		else
			return (len);
		tmp++;
	}
	ft_free_ptr((void *) &tmp_free);
	return (len);
}

static char	*ft_tosplit2(int i, char *s, char *token)
{
	char	*split;

	split = (char *) ft_calloc (i + 1, sizeof(char));
	if (split != NULL)
		ft_strlcpy (split, s, ft_wordlen(s, token) + 1);
	return (split);
}

char	**ft_tosplit(char *s, char *token, char **split)
{
	char	*tmp;
	char	*tmp_free;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tmp = ft_strdup(s);
	tmp_free = tmp;
	while (*tmp)
	{
		if (ft_strnstr(tmp, token, ft_strlen(token)))
		{
			split[j] = ft_tosplit2(i, s, token);
			tmp += ft_strlen(token);
			s = tmp;
			j++;
		}
		i++;
		tmp++;
	}
	split[j] = (char *) ft_calloc((i + 1), sizeof(char));
	ft_strlcpy (split[j], s, ft_strlen(s) + 1);
	ft_free_ptr((void *) &tmp_free);
	return (split);
}

char	**ft_split_by_str(char *s, char *token)
{
	char	**split;
	int		words;

	if (!s)
		return (0);
	words = ft_countwords(s, token);
	words++;
	split = (char **) ft_calloc ((words + 1), sizeof(char **));
	if (!split)
		return (NULL);
	split = ft_tosplit(s, token, split);
	split[words] = NULL;
	return (split);
}
