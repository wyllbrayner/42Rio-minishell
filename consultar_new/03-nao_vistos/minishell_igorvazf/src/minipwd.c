/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:52:42 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/25 22:41:37 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minipwd(void)
{
	char	wd[1024];

	getcwd(wd, sizeof(wd));
	printf("%s\n", wd);
	g_return = 0;
}
