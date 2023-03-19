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

static int	filter_echo(char *str)
{
	int i;

	i = 5;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
		i++;
	if(str[i])
	{
		while(str[i] == 'n')
		{
			if(str[i + 1] == '\0')
				return (i);
			if(str[i + 1] == ' ')
				return(i);
			i++;
		}
	}
	return (0);
}
int	filter_space(char *str)
{
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
}
static void	print_echo(char *str, int n)
{
	int i;
	int j;
	
	j = 0;
	i = n + 2;
	j = filter_space(str);
	printf("int j%d\n", j);
	while (str[i] == ' ')
		i++;
	while(i <= j)
	{
		if (str[i] == 34 || str[i] == 39 )
			i++;
		else
		{
			printf("%c", str[i]);
			i++;
		}
	}
}

int ft_builtin_echo(char *echo)
{
	int flag;
	
	flag = 0;
	if(ft_strlen(echo) == 4)
		return(printf("\n"));
	if (echo)
		flag = filter_echo(echo);
	if(flag)
		print_echo(echo, flag);
	else
	{
		flag = 5;
		while (echo[flag] == ' ')
				flag++;
		while (echo[flag])
		{
			while (echo[flag] == 34 || echo[flag] == 39 )
				flag++;
			printf("%c", echo[flag]);
			flag++;
		}
		printf("\n");
	}
	return (EXIT_SUCCESS);
}
