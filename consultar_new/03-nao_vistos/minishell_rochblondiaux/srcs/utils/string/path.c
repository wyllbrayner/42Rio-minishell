/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:13:16 by lfilloux          #+#    #+#             */
/*   Updated: 2022/03/17 14:13:29 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*right_file(char *c)
{
	if ((access(c, F_OK) == FALSE) && c[0] == '/')
		return (ft_strdup(c));
	else if ((access(c, F_OK) == FALSE) && c[0] != '/')
		return (NULL);
	return (NULL);
}
