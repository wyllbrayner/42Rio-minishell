/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiniz <jodiniz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:06:38 by jodiniz           #+#    #+#             */
/*   Updated: 2023/01/24 16:06:38 by jodiniz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_minishell.h"

void	ft_builtin_cd(t_minishell *cmd)
{
	char	*str;
	int 	i;
	char	string[1024];
	int		j;

	j = 0;
	i = 3;
	str = cmd->line;
	while (str[i] == ' ')
		i++;
	while(str[i])
	{
		string[j] = str[i];
		j++;
		i++; 
	}
	chdir(string);
}