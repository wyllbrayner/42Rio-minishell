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

void    ft_heredoc_build_list(t_minishell *sh, t_node *node)
{
    printf("ft_heredoc_build_list - Inicio\n");
    sh->tmp0 = readline("(42Rio) > ");
    if (sh->tmp0)
    {
        while(ft_strncmp(sh->tmp0, node->token, (ft_strlen(node->token) + 1)) != 0)
        {
            sh->tmp1 = ft_strjoin(" ", sh->tmp0);
            ft_free_minishell_single_aux(sh->tmp0);
            sh->tmp0 = NULL;
            if (!sh->tmp1)
            {
                sh->ret = -3;
                return ;
            }
            ft_list_add_last(&sh->head_tmp, ft_node_create(sh->tmp1));
            ft_free_minishell_single_aux(sh->tmp1);
            sh->tmp1 = NULL;
            sh->tmp0 = readline("(42Rio) > ");
        }
        ft_free_minishell_single_aux(sh->tmp0);
        sh->tmp0 = NULL;
    }
    else
    {
        sh->ret = -3;
        return ;
    }
    printf("ft_heredoc_build_list - Fim\n");
}

void    ft_heredoc_expand_var(t_minishell *sh)
{
    printf("ft_heredoc_expand_var - Início\n");
    t_node *node;

    node = sh->head_tmp;
    while (node)
    {
//        printf("token de heredoc pré expand_var: %s\n", node->token);
        if (!ft_strchr(node->token, '~'))
        {
            ft_expand_variable(sh, node);
//            printf("Após     ft_expand_variable, sh->tmp5     %s\n", sh->tmp5);
            if (sh->tmp5)
            {
//                printf("token de heredoc tmp5: %s\n", sh->tmp5);
                sh->tmp2 = ft_substr(sh->tmp5, 1, (ft_strlen(sh->tmp5) - 1));
                ft_free_minishell_single_aux(sh->tmp5);
                sh->tmp5 = NULL;
                if (!sh->tmp2)
                {
                    sh->ret = -3;
                    return ;
                }
                sh->tmp1 = sh->tmp2;
                sh->tmp2 = (void *)0;
                ft_builtin_cd_aux_2(sh, node); //substitua token por sh->tmp1
                if (sh->ret < 0)
                    return ;
            }
        }
//        printf("token de heredoc pós expand_var: %s\n", node->token);
        node = node->next;
    }
    printf("ft_heredoc_expand_var - Fim\n");
}

/*
void    ft_heredoc_expand_var(t_minishell *sh)
{
    printf("ft_heredoc_expand_var - Início\n");
    t_node *node;

    node = sh->head_tmp;
    while (node)
    {
//        printf("token de heredoc pré expand_var: %s\n", node->token);
        if (!ft_strchr(node->token, '~'))
        {
            ft_expand_variable(sh, node);
            if (sh->tmp5)
            {
//                printf("token de heredoc tmp5: %s\n", sh->tmp5);
                sh->tmp2 = ft_substr(sh->tmp5, 1, (ft_strlen(sh->tmp5) - 1));
                ft_free_minishell_single_aux(sh->tmp5);
                sh->tmp5 = NULL;
                if (!sh->tmp2)
                {
                    sh->ret = -3;
                    return ;
                }
            }
        }
        else
        {
            sh->tmp2 = ft_substr(node->token, 1, (ft_strlen(node->token) - 1));
            if (!sh->tmp2)
            {
                sh->ret = -3;
                return ;
            }
        }
//            printf("Após     ft_expand_variable, sh->tmp5     %s\n", sh->tmp5);
        sh->tmp1 = sh->tmp2;
        sh->tmp2 = (void *)0;
        ft_builtin_cd_aux_2(sh, node); //substitua token por sh->tmp1
        if (sh->ret < 0)
            return ;
//        printf("token de heredoc pós expand_var: %s\n", node->token);
        node = node->next;
    }
    printf("ft_heredoc_expand_var - Fim\n");
}
*/

void    ft_heredoc_fd(t_minishell *sh, t_node *node)
{
    printf("ft_heredoc_fd - Início\n");
    t_node  *tmp;   
/*
    node->redirect_file_fd = (int *)malloc(sizeof(int) * 1);
    if (!node->redirect_file_fd)
    {
        sh->ret = -3;
		return ;
    }
    node->redirect_file_fd_amount = 1;
    node->redirect_file = (char **)malloc(sizeof(char *) * 2);
    if (!node->redirect_file_fd)
    {
        ft_free_minishell_close_fd(node->redirect_file_fd, node->redirect_file_fd_amount);
        node->redirect_file_fd = NULL;
        sh->ret = -3;
		return ;
    }
    node->redirect_file[0] = NULL;
    node->redirect_file[1] = NULL;
    node->redirect_file[0] = ft_strjoin("src/", node->token);
    if (!node->redirect_file[0])
    {
        ft_free_minishell_close_fd(node->redirect_file_fd, node->redirect_file_fd_amount);
        node->redirect_file_fd = NULL;
        ft_free_minishell_double_aux(node->redirect_file_fd);
        node->redirect_file_fd = NULL;
        sh->ret = -3;
        return ;
    }
    node->redirect_file_fd = open(node->token, O_RDWR | O_CREAT | O_APPEND, 0777);
*/
    sh->tmp0 = ft_strjoin("src/files/", node->token);
    if (!sh->tmp0)
    {
        sh->ret = -3;
        return;
    }
    printf("após o join: %s\n", sh->tmp0);
//    ft_free_minishell_single_aux(sh->tmp0);
//    sh->tmp0 = NULL;
//    printf("liberei sh->tmp0: %s\n", sh->tmp0);

//    int     fd_open = open(node->token, O_RDWR | O_CREAT | O_APPEND, 0777);
    int     fd_open = open(sh->tmp0, O_RDWR | O_CREAT | O_APPEND, 0777);
    if (fd_open < 0)
	{
        printf("Não foi possível abrir o arquivo: %i\n", fd_open);  // apagar
        sh->ret = -3;  // criar um código de erro para este cenário.
		return ;
	}
    tmp = sh->head_tmp;
    while (tmp)
    {
        ft_putendl_fd(tmp->token, fd_open);
        tmp = tmp->next;
    }
    close(fd_open); // temporariamente feche o fd;
    printf("=======GNL=========\n");
//    sh->tmp0 = NULL;
//    fd_open = open(node->token, O_RDWR | O_CREAT | O_APPEND, 0777);
    fd_open = open(sh->tmp0, O_RDWR | O_CREAT | O_APPEND, 0777);
    ft_free_minishell_single_aux(sh->tmp0); /// não esquecer de !NÂO APAGAR
    sh->tmp0 = NULL;                        /// não esquecer de !NÂO APAGAR
    sh->tmp0 = get_next_line(fd_open);
    printf("===================\n");
    while (sh->tmp0)
    {
        printf("gnl: %s", sh->tmp0);
        ft_free_minishell_single_aux(sh->tmp0);
        sh->tmp0 = NULL;
        sh->tmp0 = get_next_line(fd_open);
    }
    printf("ft_heredoc_fd - Fim\n");
}

void    ft_heredoc_builder(t_minishell *sh, t_node *node)
{
    printf("ft_heredoc - Inicio\n");
    sh->head_tmp = (void *)0;
    ft_heredoc_build_list(sh, node);
    if (sh->ret < 0)
    {
        ft_list_destroy(&sh->head_tmp);
        return ;
    }
    ft_heredoc_expand_var(sh);
    if (sh->ret < 0)
    {
        ft_list_destroy(&sh->head_tmp);
        return ;
    }
    ft_heredoc_fd(sh, node);
    if (sh->ret < 0)
    {
        ft_list_destroy(&sh->head_tmp);
        return ;
    }
    ft_print_list(sh->head_tmp);
    ft_list_destroy(&sh->head_tmp); /// pensar quando e onde devo destruir a lista!!!
    sh->head_tmp = (void *)0;
    printf("ft_heredoc - Fim\n");
}
