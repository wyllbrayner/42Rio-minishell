/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiniz <jodiniz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:23:54 by woliveir          #+#    #+#             */
/*   Updated: 2023/03/14 12:51:04 by jodiniz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"
#include <errno.h>

void    ft_redirect_aux_1(t_minishell *sh, t_node *node, int type)
{
    int j;
    //printf("Dentro da ft_redirect_aux_1 -> Início type: %d\n", type);
    j = 0;
    while (node->redirect_file[j])
    {
       // printf("Dentro da ft_redirect_aux_1 | dentro do loop type: %d | j: %d | node->redirect_file[%d]: %s\n", type, j, j, node->redirect_file[j]);
        if (j > 0)
        {
//            printf("Dentro da ft_redirect_aux_1 | dentro do loop | dentro do 1ª if type: %d | j: %d | node->redirect_file[%d]: %s\n", type, j, j, node->redirect_file[j]);
            sh->ret = -7;
            sh->erro = node->redirect_file[j];
            return ;
        }
//        printf("Dentro da ft_redirect_aux_1 -> Início type: %d | j: %d | node->redirect_file[%d]: %s pré open\n", type, j, j, node->redirect_file[j]);
        if (type == 1)
            node->redirect_file_fd[j] = open(node->redirect_file[j], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        else if (type == 2)
            node->redirect_file_fd[j] = open(node->redirect_file[j], O_WRONLY | O_CREAT | O_APPEND, 0666);
        else if (type == 3){
            node->redirect_file_fd[j] = open(node->redirect_file[j], O_RDONLY);
			if (node->redirect_file_fd[j])
			{
				if (node->redirect_file_fd[j] == -1)
				{
					if (errno == EACCES)
						printf("erro de permissao\n");
				}
			}
		}
        if (node->redirect_file_fd[j] == -1)
        {
//            printf("Dentro da ft_redirect_aux_1 | dentro do loop | dentro do 2ª if type: %d | j: %d | node->redirect_file[%d]: %s\n", type, j, j, node->redirect_file[j]);
            sh->ret = -7;
            sh->erro = node->redirect_file[j];
            return ;
        }
        j++;
//        printf("Dentro da ft_redirect_aux_1 -> Início type: %d | j: %d | node->redirect_file[%d]: %s pós open\n", type, j, j, node->redirect_file[j]);
    }
   // printf("Dentro da ft_redirect_aux_1 -> Fim\n");
}

void    ft_redirect_aux_0(t_minishell *sh, t_node *node)
{
    //printf("Dentro da ft_redirect_aux_0 -> Início\n");

	node->redirect_file = node->cmd;
	int j = 0;
	while (node->redirect_file[j])
    {
        //printf("após split: node->redirect_file[%i]: %s\n", j, node->redirect_file[j]);
        j++;
    }
//    printf("após split: node->redirect_file[%i]: %s\n", j, node->redirect_file[j]);

    while (node->redirect_file[node->redirect_file_fd_amount])
    {
//        printf("split para o arquivo: %s\n", node->redirect_file[node->redirect_file_fd_amount]);
        node->redirect_file_fd_amount++;
    }
    node->redirect_file_fd = (int *)malloc(sizeof(int) * node->redirect_file_fd_amount);
    if (!node->redirect_file_fd)
    {
        sh->ret = -3;
        return;
    }
//    printf("Conseguiu mallocar %i fds\n", node->redirect_file_fd_amount);
//    printf("para node->token: %s o prev é: %s\n", node->token, node->prev->token);
    if (node->prev)
    {
        if (ft_strncmp(node->prev->first_cmd, ">", 2) == 0)
        {
            //printf("Arquivo de saida normal\n");
            ft_redirect_aux_1(sh, node, 1);
        }
        else if (ft_strncmp(node->prev->first_cmd, ">>", 3) == 0)
        {
//            printf("Arquivo de saida com append\n");
            ft_redirect_aux_1(sh, node, 2);
        }
        else if (ft_strncmp(node->prev->first_cmd, "<", 2) == 0)
        {
//            printf("Arquivo de entrada normal\n");
            ft_redirect_aux_1(sh, node, 3);
        }
    }
   // printf("Dentro da ft_redirect_aux_0 -> Fim\n");
}

void	ft_redirect_2(t_minishell *sh)
{
//    printf("Dentro da ft_redirect -> Início\n");
    t_node *head;

    head = sh->head;
    while (head && (sh->ret == 0))
    {
//       printf("nó [cmd[0]   ]: %s\n", head->cmd[0]);
//       printf("nó [first cmd]: %s\n", head->first_cmd);
        if (head->first_cmd[0] != '|' && head->first_cmd[0] != '<' && head->first_cmd[0] != '>')
        {
            if (head->prev)
            {
                if ((ft_strncmp(head->prev->first_cmd, "<", 2) == 0) || (ft_strncmp(head->prev->first_cmd, ">", 2) == 0) || (ft_strncmp(head->prev->first_cmd, ">>", 3) == 0))
                {
//                    printf("Charmar a builder_redirect head->token: %s\n", head->first_cmd);
                    ft_redirect_aux_0(sh, head);
                    if (sh->ret < 0)
                        break ;
                }
            }
        }
        head = head->next;
    }
//    printf("Dentro da ft_redirect -> Fim\n");
}