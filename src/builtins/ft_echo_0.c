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
// echo -nnnnn2 '$USER'
//	printf("Dentro da filter_echo - Inicio: token: %s\n", str);
//		printf("Dentro da filter_echo | 1º loop token: %s | i: %d\n", str, i);
//				printf("Dentro da filter_echo | 2º loop | 1º if token: 
//%s | i: %d\n", str, i);
//				printf("Dentro da filter_echo | 2º loop | 2º if token: 
//%s | i: %d\n", str, i);
//	printf("Dentro da filter_echo - Fim\n");

extern t_signal	g_sig;

static int	ft_builtin_echo_intern(char *echo);
static void	ft_builtin_echo_intern_aux_0(char *echo);
static int	filter_echo(char *str);
static void	print_echo(char *str, int n);

//	printf("Dentro da ft_builtin_echo - errnbr: %i Inicio\n", sh->errnbr);
//	printf("Dentro da ft_builtin_echo - errnbr: %i Fim\n", sh->errnbr);
void	ft_builtin_echo(t_node *node)
{
	long	i;
	long	ret_echo;

	i = 0;
	ret_echo = 0;
	while (node->token[i] && ft_isspace(node->token[i]))
		i++;
	ret_echo = ft_builtin_echo_intern(&node->token[i]);
	if (ret_echo)
		g_sig.errnbr = 0;
}

//	printf("Dentro da ft_builtin_echo_intern - Inicio\n");
//	printf("echo: %s \n", echo);
//		printf("Dentro do if\n");
//		printf("Dentro da ft_builtin_echo_intern | chama    a 
//filter_echo(%s)\n", echo);
//		printf("Dentro da ft_builtin_echo_intern | retorno da
// filter_echo(%s) | flag: %d\n", echo, flag);
//		printf("Dentro da ft_builtin_echo_intern | chama    a
// print_echo(%s)\n", echo);
//		printf("Dentro da ft_builtin_echo_intern | retorno da
// print_echo(%s)\n", echo);
//	printf("Dentro da ft_builtin_echo_intern - Fim\n");
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

//		printf("Dentro da ft_builtin_echo_intern | dentro do último if (%s | 
//flag: %d)\n", echo, flag);
//			printf("Dentro da ft_builtin_echo_intern | dentro do último if | 
//1º loop (%s | flag: %d)\n", echo, flag);
//		printf("Dentro da ft_builtin_echo_intern | dentro do último if | 
//fora do 1º loop (%s | flag: %d)\n", echo, flag);
static void	ft_builtin_echo_intern_aux_0(char *echo)
{
	int	flag;

	flag = 4;
	while (echo[flag])
	{
		if (echo[flag] == ' ')
			flag++;
		else
			break ;
	}
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

	i = 4;
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

//	printf("Dentro da print_echo - Início\n");
//	printf("Dentro da print_echo - Fim\n");
static void	print_echo(char *str, int n)
{
	int	i;
	int	j;

	j = 0;
	i = n + 2;
	j = filter_space(str);
	while (str[i] == ' ')
		i++;
	while (i <= j)
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
