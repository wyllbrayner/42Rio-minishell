/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word(char const *s, char c);
static char		**ft_split_word(char const *s, char c, char **str, size_t q_wd);
static size_t	ft_len_word(char const *s, char c);
static void		ft_free_str(char **str, size_t q_pt);

char	**ft_split(char const *s, char c)
{
	size_t	qtd_plv;
	char	**str;

	if (!s)
		return (NULL);
	qtd_plv = ft_count_word(s, c);
	str = (char **)malloc(sizeof(str) * (qtd_plv + 1));
	if (!str)
		return (NULL);
	ft_split_word(s, c, str, qtd_plv);
	return (str);
}

static size_t	ft_count_word(char const *s, char c)
{
	size_t	qtd_word;
	size_t	flag;

	qtd_word = 0;
	flag = 0;
	while (*s)
	{
		if ((*s != c) && (flag == 0))
		{
			qtd_word++;
			flag = 1;
		}
		else if ((*s == c) && (flag == 1))
			flag = 0;
		s++;
	}
	return (qtd_word);
}

static char	**ft_split_word(char const *s, char c, char **str, size_t q_wd)
{
	size_t	i;
	size_t	len_word;

	i = 0;
	while (i < q_wd)
	{
		while (*s && (*s == c))
			s++;
		if (*s)
		{
			len_word = ft_len_word(s, c);
			str[i] = ft_substr(s, 0, len_word);
			if (!str[i])
			{
				ft_free_str(str, i);
				return (NULL);
			}
			i++;
		}
		s += len_word;
	}
	str[q_wd] = NULL;
	return (str);
}

static size_t	ft_len_word(char const *s, char c)
{
	size_t	len_word;

	len_word = 0;
	while (s[len_word] && s[len_word] != c)
		len_word++;
	return (len_word);
}

static void	ft_free_str(char **str, size_t q_pt)
{
	long long int	i;

	i = (long long int)q_pt;
	while (--i >= 0)
	{
		free(str[i]);
		str[i] = (void *)0;
	}
	free(str);
}
