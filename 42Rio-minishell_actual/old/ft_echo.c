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

void ft_builtin_echo(t_minishell *sh, t_node *node)
{
	printf("Dentro da ft_builtin_echo - Inicio\n");
	long i;
	
	printf("tmp0: %s\n", sh->tmp0);
	printf("tmp1: %s\n", sh->tmp1);
	printf("tmp2: %s\n", sh->tmp2);
	printf("tmp5: %s\n", sh->tmp5);

	i = 0;
	while (node->token[i])
		i++;
	printf("Total de caracteres em token: %ld\n", i);
	printf("token: %s\n", node->token);
	sh->tmp0 = (char *)malloc(sizeof(char) * ++i);

	i = 0;
	while (node->cmd[i])
	{
		printf("node->cmd[%ld]: %s\n", i, node->cmd[i]);
		i++;
	}

	ft_free_minishell_single_aux(sh->tmp0);
	sh->tmp0 = NULL;

	sh->ret = 0;


	printf("tmp0: %s\n", sh->tmp0);
	printf("tmp1: %s\n", sh->tmp1);
	printf("tmp2: %s\n", sh->tmp2);
	printf("tmp5: %s\n", sh->tmp5);

	printf("Dentro da ft_builtin_echo - Fim\n");
}
/*
tratamento de aspas simples e duplas
var de ambiente / $?
printar texto
	se parametro == -n
		printar \n

mallocar tmp com tamanho de token
percorrer token copiando o que for diferente de \' ou \" para tmp
identificar e substituir var de ambiente / $?
printar tmp
	se parametro == -n
		printar \n
liberar temp

*/