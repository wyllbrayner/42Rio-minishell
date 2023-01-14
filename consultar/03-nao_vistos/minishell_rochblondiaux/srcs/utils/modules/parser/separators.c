/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	is_separator(char *c, size_t index)
{
	return (c[index] && (c[index] == '&'
			|| c[index] == '|'
			|| c[index] == ';'
			|| (c[index] == '|' && c[index + 1] && c[index + 1] == '|')
			|| (c[index] == '&' && c[index + 1] && c[index + 1] == '&')));
}
