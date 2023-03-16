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

extern t_signal	g_sig;

//    printf("ft_heredoc_fd - Início\n");
//   printf("Não foi possível abrir o arquivo: %i\n", *node->redirect_file_fd);
//    printf("fd 1º open: %i\n", *node->redirect_file_fd);
//    *node->redirect_file_fd = open(sh->tmp0, O_RDWR | O_CREAT, 0666);
//    ft_free_minishell_single_aux(sh->tmp0);
//    sh->tmp0 = NULL;
//        printf("Erro no dup\n");
//        printf("fd 2º open: %i\n", *node->redirect_file_fd);
/*
    printf("=======GNL=========\n");
    while ((sh->tmp0 = get_next_line(*node->redirect_file_fd)))
    {
        printf("gnl: %s", sh->tmp0);
        ft_free_minishell_single_aux(sh->tmp0);
        sh->tmp0 = NULL;
    }
    printf("===================\n");
*/
//    printf("ft_heredoc_fd - Fim\n");
static void	ft_heredoc_fd_aux0(t_minishell *sh, t_node *node);
static void	ft_heredoc_fd_aux1(t_minishell *sh, t_node *n);

//    printf("Dentro da ft_heredoc -> Início\n");
//        printf("nó [token    ]: %s\n", head->token);
//        printf("nó [cmd[0]   ]: %s\n", head->cmd[0]);
//        printf("nó [first cmd]: %s\n", head->first_cmd);
//    printf("Dentro da ft_heredoc -> Fim\n");

void	ft_heredoc_fd(t_minishell *sh, t_node *n)
{
	ft_heredoc_fd_aux0(sh, n);
	if (sh->ret < 0)
		return ;
	ft_heredoc_fd_aux1(sh, n);
	if (sh->ret < 0)
		return ;
	*n->redirect_file_fd = open(n->redirect_file[0], O_RDWR | O_CREAT, 0666);
	if (*n->redirect_file_fd < 0)
	{
		sh->ret = -7;
		sh->erro = n->redirect_file[0];
		g_sig.errnbr = errno;
		return ;
	}
	else
		n->redirect_file_fd_amount = 1;
}

static void	ft_heredoc_fd_aux0(t_minishell *sh, t_node *node)
{
	sh->tmp0 = ft_strjoin(".heredoc_", node->token);
	if (!sh->tmp0)
	{
		sh->ret = -3;
		g_sig.errnbr = errno;
		return ;
	}
	node->redirect_file = ft_split(sh->tmp0, ' ');
	ft_free_minishell_single_aux(sh->tmp0);
	sh->tmp0 = NULL;
	if (!node->redirect_file)
	{
		sh->ret = -3;
		g_sig.errnbr = errno;
		return ;
	}
	node->redirect_file_fd = (int *)malloc(sizeof(int) * 1);
	if (!node->redirect_file_fd)
	{
		sh->ret = -3;
		g_sig.errnbr = errno;
		return ;
	}
}

static void	ft_heredoc_fd_aux1(t_minishell *sh, t_node *n)
{
	t_node	*tmp;

	*n->redirect_file_fd = open(n->redirect_file[0], O_RDWR | O_CREAT, 0666);
	if (*n->redirect_file_fd < 0)
	{
		sh->ret = -7;
		sh->erro = n->redirect_file[0];
		g_sig.errnbr = 1;
		return ;
	}
	tmp = sh->head_tmp;
	while (tmp)
	{
		ft_putendl_fd(tmp->token, *n->redirect_file_fd);
		tmp = tmp->next;
	}
	close(*n->redirect_file_fd);
}
