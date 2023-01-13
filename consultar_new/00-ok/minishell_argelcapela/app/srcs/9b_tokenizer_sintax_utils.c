/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9b_tokenizer_sintax_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 06:14:16 by argel             #+#    #+#             */
/*   Updated: 2022/12/07 12:42:47 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	all_equal(char *c)
{
	int		i;
	int		len;
	char	cc;

	if (!c)
		return (0);
	len = ft_strlen(c);
	i = 0;
	cc = c[0];
	if (cc != '\"' && cc != '\'')
		return (0);
	while (i < len)
	{
		if (c[i] != cc)
			return (0);
		i++;
	}
	ft_pf_error("miniheaven: %s\n", E_CMDNOTFOUND);
	return (1);
}
