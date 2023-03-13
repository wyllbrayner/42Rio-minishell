/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2022/05/09 15:09:49 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_minishell.h"

//	printf("Dentro da filter_space - Início\n");
//	printf("Dentro da filter_space - Fim\n");
int	filter_space(char *str)
{
	int	i;
	int	n;

	n = 0;
	while (str[n])
		n++;
	i = n - 1;
	while (i)
	{
		if (str[i] == ' ')
			i--;
		else if (str[i] == '\t')
			i--;
		else
			return (i);
	}
	return (i);
}
