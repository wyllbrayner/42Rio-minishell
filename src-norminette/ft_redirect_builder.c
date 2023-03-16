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

#include "../header/ft_minishell.h"

void	ft_redirect_builder_aux_0(t_minishell *sh, t_node *node);
void	ft_redirect_builder_aux_1(t_minishell *sh, t_node *node, int type);
void	ft_redirect_builder_aux_1_0(int j, t_minishell *sh, t_node *node, \
		int type);

//    printf("Dentro da ft_redirect -> Início\n");
//        printf("nó [token    ]: %s\n", head->token);
//        printf("nó [cmd[0]   ]: %s\n", head->cmd[0]);
//        printf("nó [first cmd]: %s\n", head->first_cmd);
//                    printf("Charmar a builder_redirect head->token:
// %s\n", head->token);
//    printf("Dentro da ft_redirect -> Fim\n");
void	ft_redirect_builder(t_minishell *sh)
{
	t_node	*head;

	head = sh->head;
	while (head && (sh->ret == 0))
	{
		if (head->first_cmd[0] != '|' && head->first_cmd[0] != '<' && \
				head->first_cmd[0] != '>')
		{
			if (head->prev)
			{
				if ((ft_strncmp(head->prev->first_cmd, "<", 2) == 0) || \
						(ft_strncmp(head->prev->first_cmd, ">", 2) == 0) || \
						(ft_strncmp(head->prev->first_cmd, ">>", 3) == 0))
				{
					ft_redirect_builder_aux_0(sh, head);
					if (sh->ret < 0)
						break ;
				}
			}
		}
		head = head->next;
	}
}

//    printf("Dentro da ft_redirect_aux_0 -> Início\n");
//    printf("Conseguiu mallocar %i fds\n", node->redirect_file_fd_amount);
//    printf("para node->token: %s o prev é: %s\n", node->token, 
//    node->prev->token);
//    printf("Dentro da ft_redirect_aux_0 -> Fim\n");
void	ft_redirect_builder_aux_0(t_minishell *sh, t_node *node)
{
	node->redirect_file = ft_split(node->token, ' ');
	if (!node->redirect_file)
	{
		sh->ret = -3;
		sh->errnbr = errno;
		return ;
	}
	while (node->redirect_file[node->redirect_file_fd_amount])
		node->redirect_file_fd_amount++;
	node->redirect_file_fd = (int *)malloc(sizeof(int) * \
			node->redirect_file_fd_amount);
	if (!node->redirect_file_fd)
	{
		sh->ret = -3;
		sh->errnbr = errno;
		return ;
	}
	if (ft_strncmp(node->prev->token, ">", 2) == 0)
		ft_redirect_builder_aux_1(sh, node, 1);
	else if (ft_strncmp(node->prev->token, ">>", 3) == 0)
		ft_redirect_builder_aux_1(sh, node, 2);
	else if (ft_strncmp(node->prev->token, "<", 2) == 0)
		ft_redirect_builder_aux_1(sh, node, 3);
}

//    printf("Dentro da ft_redirect_aux_1 -> Início type: %d\n", type);
//        printf("Dentro da ft_redirect_aux_1 | dentro do loop type: %d 
//| j: %d | node->redirect_file[%d]: %s\n", type, j, j, 
//node->redirect_file[j]);
//            printf("Dentro da ft_redirect_aux_1 | dentro do loop | 
//dentro do 1ª if type: %d | j: %d | node->redirect_file[%d]: %s\n", 
//type, j, j, node->redirect_file[j]);
//        printf("Dentro da ft_redirect_aux_1 -> Início type: %d | j: 
//%d | node->redirect_file[%d]: %s pós open\n", type, j, j, 
//node->redirect_file[j]);
//    printf("Dentro da ft_redirect_aux_1 -> Fim\n");
void	ft_redirect_builder_aux_1(t_minishell *sh, t_node *node, int type)
{
	int	j;

	j = 0;
	while (node->redirect_file[j])
	{
		if (j > 0)
		{
			sh->ret = -7;
			sh->erro = node->redirect_file[j];
			sh->errnbr = 1;
			return ;
		}
		ft_redirect_builder_aux_1_0(j, sh, node, type);
		if (sh->ret < 0)
			return ;
		j++;
	}
}

//            printf("Dentro da ft_redirect_aux_1 | dentro do loop | dentro 
//do 2ª if type: %d | j: %d | node->redirect_file[%d]: %s\n", type, j, j, n
//ode->redirect_file[j]);
void	ft_redirect_builder_aux_1_0(int j, t_minishell *sh, t_node *node, \
		int type)
{
	if (type == 1)
		node->redirect_file_fd[j] = \
		open(node->redirect_file[j], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (type == 2)
		node->redirect_file_fd[j] = \
		open(node->redirect_file[j], O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (type == 3)
		node->redirect_file_fd[j] = \
		open(node->redirect_file[j], O_RDONLY);
	if (node->redirect_file_fd[j] == -1)
	{
		if (errno == EACCES)
			sh->ret = -12;
		else
			sh->ret = -7;
		sh->erro = node->redirect_file[j];
		sh->errnbr = 1;
	}
}
