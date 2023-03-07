/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiniz <jodiniz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2023/01/24 19:26:53 by jodiniz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_minishell.h"
// echo -nnnnn2 '$USER'
static int	filter_echo(char *str)
{
//	printf("Dentro da filter_echo - Inicio: token: %s\n", str);
	int i;

	i = 4;
	while (str[i] == ' ')
	{
//		printf("Dentro da filter_echo | 1º loop token: %s | i: %d\n", str, i);
		i++;
	}
	if (str[i] == '-')
		i++;
	if(str[i])
	{
		while(str[i] == 'n')
		{
			if(str[i + 1] == '\0')
			{
//				printf("Dentro da filter_echo | 2º loop | 1º if token: %s | i: %d\n", str, i);
				return (i);
			}
			if(str[i + 1] == ' ')
			{
//				printf("Dentro da filter_echo | 2º loop | 2º if token: %s | i: %d\n", str, i);
				return(i);
			}
			i++;
		}
	}
//	printf("Dentro da filter_echo - Fim\n");
	return (0);
}
int	filter_space(char *str)
{
//	printf("Dentro da filter_space - Início\n");
	int i;
	int n;

	n = 0;
	while (str[n])
		n++;
	i = n - 1;
	while(i)
	{
		if (str[i] == ' ')
			i--;
		else if (str[i] == '\t')
			i--;
		else
			return(i);
	}
	return(i);
//	printf("Dentro da filter_space - Fim\n");
}
static void	print_echo(char *str, int n)
{
//	printf("Dentro da print_echo - Início\n");
	int i;
	int j;
	
	j = 0;
	i = n + 2;
	j = filter_space(str);
//	printf("int j%d\n", j);
	while (str[i] == ' ')
		i++;
	while(i <= j)
	{
		if (str[i] == 39)
			i++;
		else
		{
			printf("%c", str[i]);
			i++;
		}
	}
//	printf("Dentro da print_echo - Fim\n");
}


int ft_builtin_echo_intern(char *echo)
{
//	printf("Dentro da ft_builtin_echo_intern - Inicio\n");
	int flag;
	
	flag = 0;
//	printf("echo: %s \n", echo);
	if (ft_strlen(echo) == 4)
	{
//		printf("Dentro do if\n");
		return(printf("\n"));
	}
	if (echo)
	{
//		printf("Dentro da ft_builtin_echo_intern | chama    a filter_echo(%s)\n", echo);
		flag = filter_echo(echo);
//		printf("Dentro da ft_builtin_echo_intern | retorno da filter_echo(%s) | flag: %d\n", echo, flag);
	}
	if(flag)
	{
//		printf("Dentro da ft_builtin_echo_intern | chama    a print_echo(%s)\n", echo);
		print_echo(echo, flag);
//		printf("Dentro da ft_builtin_echo_intern | retorno da print_echo(%s)\n", echo);
	}
	else
	{
		flag = 4;
//		printf("Dentro da ft_builtin_echo_intern | dentro do último if (%s | flag: %d)\n", echo, flag);
		while (echo[flag])
		{
//			printf("Dentro da ft_builtin_echo_intern | dentro do último if | 1º loop (%s | flag: %d)\n", echo, flag);
			if (echo[flag] == ' ')
				flag++;
			else
				break ;
		}
//		printf("Dentro da ft_builtin_echo_intern | dentro do último if | fora do 1º loop (%s | flag: %d)\n", echo, flag);
		while (echo[flag])
		{
//			while (echo[flag])
//			{
				if ((echo[flag] == '\''))
					flag++;
//				else
//					break ;
//			}
			if (echo[flag])
			{
				printf("%c", echo[flag]);
				flag++;
			}
		}
		printf("\n");
	}
//	printf("Dentro da ft_builtin_echo_intern - Fim\n");
	return (EXIT_SUCCESS);
}

void    ft_builtin_echo(t_minishell *sh, t_node *node)
{
	long i;
	long ret_echo;

	i = 0;
	ret_echo = 0;
//	printf("Dentro da ft_builtin_echo - Inicio\n");
	while (node->token[i] && ft_isspace(node->token[i]))
		i++;
	ret_echo = ft_builtin_echo_intern(&node->token[i]);

	if (ret_echo)
		sh->ret = 0;
//	else
//		sh->errno = perror;
//	printf("Dentro da ft_builtin_echo - Fim\n");
}

/*
void    ft_builtin_echo(t_minishell *sh, t_node *node)
{
	printf("Dentro da ft_builtin_echo - Inicio\n");
	while (node->token[i] && ft_isspace(node->token[i]))
		i++;
	while (node->token[i] && !ft_isspace(node->token[i]))
		i++;
	while (node->token[i] && ft_isspace(node->token[i]))
		i++;
	start = i;
	while (node->token[i])
	{	
		i++;
	}
	if (i == start)
		ft_putchar_fd('\n', 1);
	while (node->cmd[j])
		j++;
	if (j >= 2)
	{
		if (node->cmd[1][k] == '-')
		{
			k++;
			if (node->cmd[1][k] == 'n')
			{
				while (node->cmd[1][k])
				{
					if (node->cmd[1][k] == 'n')
						k++;
					else
						break ;
				}
			}
		}
	}
	sh->ret = 0;
	printf("Dentro da ft_builtin_echo - Fim\n");
}
*/

/*
int ft_builtin_echo(char *echo)
{
	printf("Dentro da ft_builtin_echo - Inicio\n");
	printf("%s\n", echo);
	printf("Dentro da ft_builtin_echo - Fim\n");
	return (EXIT_SUCCESS);
}
*/