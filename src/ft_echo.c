/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiniz <jodiniz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2023/03/17 13:30:12 by jodiniz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

extern t_signal	g_sig;

static int	ft_builtin_echo_intern(char *echo);
static void	ft_builtin_echo_intern_aux_0(char *echo);
static int	filter_echo(char *str);
static void	print_echo(char *str, int n);

void	ft_builtin_echo(t_node *node)
{
	long	i;
	long	ret_echo;

	i = 0;
	ret_echo = 0;
	ret_echo = ft_builtin_echo_intern(&node->token[i]);
	if (ret_echo)
		g_sig.errnbr = 0;
}

static int	ft_builtin_echo_intern(char *echo)
{
	int	flag;

	flag = 0;
	if (ft_strlen(echo) == 4)
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	if (echo)
		flag = filter_echo(echo);
	if (flag)
		print_echo(echo, flag);
	else
		ft_builtin_echo_intern_aux_0(echo);
	return (1);
}

static void	ft_builtin_echo_intern_aux_0(char *echo)
{
	int	flag;

	flag = 5;
	while (echo[flag])
	{
		if (echo[flag] == '\'')
			flag++;
		if (echo[flag])
		{
			ft_putchar_fd(echo[flag], 1);
			flag++;
		}
	}
	ft_putchar_fd('\n', 1);
}

static int	filter_echo(char *str)
{
	int	i;

	i = 5;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
		i++;
	if (str[i])
	{
		while (str[i] == 'n')
		{
			if (str[i + 1] == '\0')
				return (i);
			if (str[i + 1] == ' ')
				return (i);
			i++;
		}
	}
	return (0);
}

static void	print_echo(char *str, int n)
{
	int	i;

	i = n + 2;
	while (str[i])
	{
		if (str[i] == 39)
			i++;
		else
		{
			ft_putchar_fd(str[i], 1);
			i++;
		}
	}
}
