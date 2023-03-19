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

void ft_valid_empty_cmd(t_minishell *sh)
{
    //printf("Dentro da ft_valid_empty_cmd | inicio (line: %s)\n", sh->line);
    sh->tmp1 = ft_strtrim(sh->line, " ");
    if (!sh->tmp1)
    {
        sh->ret = -3;
        return ;
    }
    if ((ft_strlen(sh->tmp1) == 0))
    {
        sh->ret = -8;
    }
    ft_free_minishell_single_aux(sh->tmp1);
    //printf("Dentro da ft_valid_empty_cmd | fim\n");
}

void ft_valid_quotes(t_minishell *sh)
{
    long    i;
    long    count_s;
    long    count_d;

//    printf("Dentro da ft_valid_quotes | inicio\n");
    if (sh)
    {
        i = 0;
        count_s = 0;
        count_d = 0;
        while (sh->line[i])
        {
            if (sh->line[i] == '\'')
                count_s++;
            else if (sh->line[i] == '\"')
                count_d++;
            i++;
        }
        if (((count_s % 2) != 0) || ((count_d % 2) != 0))
        {
            sh->ret = -5;
        }
    }
//    printf("Dentro da ft_valid_quotes | fim\n");
}

void ft_valid_redirect_flow_aux(t_minishell *sh, int c)
{
    long    i;
    long    count;

    i = 0;
    count = 0;
    while (sh->line[i])
    {
        if (sh->line[i] == c)
        {
            count++;
          //  if ((count == 2) && (sh->line[i - 1] != c))
          //  {
          //     sh->ret = -6;
          //      return ;
          //  }
        }
        i++;
    }
    //if (count > 2)
    //    sh->ret = -6;
}

void ft_valid_redirect_out(t_minishell *sh)
{
    long    i;
    long    j;
    long    start;

    i = 0;
    start = 0;
    ft_valid_redirect_flow_aux(sh, '>');
    if (sh->ret < 0)
        return ;
    while (sh->line[i] && (sh->line[i] != '>'))
        i++;
    if (i == 0)
    {
        sh->ret = -8;
        return;
    }
    if (sh->line[i] == '>' && (ft_isspace(sh->line[i - 1])))
    {
        sh->out_redirect = 1;
        i++;
        if (sh->line[i] && (sh->line[i] == '>'))
        {
            sh->out_redirect = 2;
            i++;
        }
        if (sh->line[i] && (!ft_isspace(sh->line[i])))
        {
            sh->ret = -6;
            return ;
        }
        start = i;
        while (sh->line[i] && ((sh->line[i] != '|') && (sh->line[i] != '<')))
            i++;
        if (i > start)
        {
            sh->tmp1 = ft_substr(&sh->line[start], 0, (size_t)(i - (start)));
            sh->out_redirect_file = ft_split(sh->tmp1, ' ');
            ft_free_minishell_single_aux(sh->tmp1);
            if (!sh->out_redirect_file)
            {
                sh->ret = -3;
                return ;
            }
            else
            {
                while (sh->out_redirect_file[sh->out_redirect_file_fd_amount])
                    sh->out_redirect_file_fd_amount++;
                sh->out_redirect_file_fd = (int *)malloc(sizeof(int) * sh->out_redirect_file_fd_amount);
                if (!sh->out_redirect_file_fd)
                {
                    sh->ret = -3;
                    return ;
                }
                else
                {
                    j = 0;
                    while (sh->out_redirect_file[j])
                    {
                        if (sh->out_redirect == 1)
                        {
                            sh->out_redirect_file_fd[j] = open(sh->out_redirect_file[j], O_WRONLY | O_CREAT | O_TRUNC, 0666);
                            if (sh->out_redirect_file_fd[j] == -1)
                            {
                                sh->ret = -7;
                                sh->erro = sh->out_redirect_file[j];
                                return ;
                            }
                        }
                        else
                        {
                            sh->out_redirect_file_fd[j] = open(sh->out_redirect_file[j], O_WRONLY | O_CREAT | O_APPEND, 0666);
                            if (sh->out_redirect_file_fd[j] == -1)
                            {
                                sh->ret = -7;
                                sh->erro = sh->out_redirect_file[j];
                                return ;
                            }
                        }
                        j++;
                    }
                }
            }
        }
        else
            sh->ret = -6;
    }
}

void ft_valid_redirect_in(t_minishell *sh)
{
    long    i;
    long    j;
    long    start;

    i = 0;
    start = 0;
    ft_valid_redirect_flow_aux(sh, '<');
    if (sh-> ret < 0)
        return ;
    while (sh->line[i] && (sh->line[i] != '<'))
        i++;
    if (i == 0)
    {
        sh->ret = -8;
        return;
    }
    if (sh->line[i] == '<' && (ft_isspace(sh->line[i - 1])))
    {
        sh->in_redirect = 1;
        i++;
        if (sh->line[i] && (sh->line[i] == '<'))
        {
            sh->in_redirect = 2;
            i++;
        }
        if (sh->line[i] && (!ft_isspace(sh->line[i])))
        {
            sh->ret = -6;
            return ;
        }
        start = i;
        while (sh->line[i] && ((sh->line[i] != '|') && (sh->line[i] != '>')))
            i++;
        if (i > start)
        {   
            sh->tmp1 = ft_substr(&sh->line[start], 0, (size_t)(i - (start)));
            sh->in_redirect_file = ft_split(sh->tmp1, ' ');
            ft_free_minishell_single_aux(sh->tmp1);
            if (!sh->in_redirect_file)
            {
                sh->ret = -3;
                return ;
            }
            else
            {
                while (sh->in_redirect_file[sh->in_redirect_file_fd_amount])
                    sh->in_redirect_file_fd_amount++;
                sh->in_redirect_file_fd = (int *)malloc(sizeof(int) * sh->in_redirect_file_fd_amount);
                if (!sh->in_redirect_file_fd)
                {
                    sh->ret = -3;
                    return ;
                }
                else
                {
                    j = 0;
                    while (sh->in_redirect_file[j])
                    {
                        if (sh->in_redirect == 1)
                        {
                            sh->in_redirect_file_fd[j] = open(sh->in_redirect_file[j], O_RDONLY);
                            if (sh->in_redirect_file_fd[j] == -1)
                            {
                                sh->ret = -7;
                                sh->erro = sh->in_redirect_file[j];
                                return ;
                            }
                        }
                        else
                        {
                            sh->in_redirect_file_fd[j] = open(sh->in_redirect_file[j], O_WRONLY | O_CREAT | O_APPEND, 0666);
                            if (sh->in_redirect_file_fd[j] == -1)
                            {
                                sh->ret = -7;
                                sh->erro = sh->in_redirect_file[j];
                                return ;
                            }
                        }
                        j++;
                    }
                }
            }
        }
        else
            sh->ret = -6;
    }
}

void ft_first_cmd(t_minishell *sh)
{
    t_node *tmp;
    //long    i;
    //printf("Dentro da first cmd - Início\n");
    tmp = sh->head;
    while (tmp)
    {
        sh->tmp3 = ft_split(tmp->cmd[0], ' ');
        if (!sh->tmp3)
        {
            sh->ret = -3;
            return;            
        }
        tmp->first_cmd = ft_strdup(sh->tmp3[0]);
        if (!tmp->first_cmd)
        {
            sh->ret = -3;
            return;            
        }
        //printf("Nó: %s     possui first_cmd: %s\n", tmp->cmd[0], tmp->first_cmd);
        ft_free_minishell_double_aux(sh->tmp3);
        sh->tmp3 = NULL;
        sh->tmp3 = ft_split(tmp->cmd[0], ' ');
        if (!sh->tmp3)
        {
            sh->ret = -3;
            return;            
        }
        ft_free_minishell_double_aux(tmp->cmd);
        tmp->cmd = NULL;
        tmp->cmd = sh->tmp3;
        sh->tmp3 = NULL;
        tmp = tmp->next;
    }
    //printf("Dentro da first cmd - Fim\n");
}

int ft_valid_command_aux(t_minishell *sh, char *cmd)
{
//    printf("Dentro da ft_valid_comand_aux | inicio\n");
    if (sh && cmd)
    {
        if (ft_strncmp(cmd, "echo", 5) == 0)
            return (1);
        else if (ft_strncmp(cmd, "cd", 3) == 0)
            return (1);
        else if (ft_strncmp(cmd, "pwd", 4) == 0)
            return (1);
        else if (ft_strncmp(cmd, "export", 7) == 0)
            return (1);
        else if (ft_strncmp(cmd, "unset", 6) == 0)
            return (1);
        else if (ft_strncmp(cmd, "env", 4) == 0)
            return (1);
        else if (ft_strncmp(cmd, "exit", 5) == 0)
            return (1);
        else
        {
            sh->tmp1 = ft_access_command(cmd, sh->path);
            if (!sh->tmp1)
                return (0);
            ft_free_minishell_single_aux(sh->tmp1);
            return (1);
        }
    }
//    printf("Dentro da ft_valid_comand_aux | fim\n");
    return (0);
}

/*
int ft_pipe_or_redirect(t_minishell *sh, long i)
{
    return (sh->parse_str[i][0] == '|' || sh->parse_str[i][0] == '<' || sh->parse_str[i][0] == '>');
}
*/

int ft_pipe_or_redirect(char *cmd)
{
    //return (cmd[0] == '|');
    return (cmd[0] == '|' || cmd[0] == '<' || cmd[0] == '>');
}

int ft_valid_file(t_minishell *sh, long i)
{
    int fd;

    fd = open(sh->parse_str[i], O_WRONLY | O_CREAT, 0666);
    if (fd == -1)
        return (0);
    else
    {
        close(fd);
        return (1);
    }
}

//  0   1        2             3 4 5    6        7 8 9      10      11 
// ls -la Makefile src/ft_main.c | | grep Makefile > > test1.c test2.c

/*
void ft_valid_lexcal_cmd(t_minishell *sh)
{
    t_node  *tmp;

    tmp = sh->head;
    while (tmp)
    {
        if ((!tmp->prev) && (tmp->cmd[0][0] == '|'))
        {
            sh->ret = -6;
            sh->erro ="|"; 
            return ;
        }
        else if ((tmp->cmd[0][0] == '|') && (tmp->next) && (tmp->next->cmd[0][0] == '|'))
        {
            sh->ret = -6;
            sh->erro = "|";
            return ;
        }
        tmp = tmp->next;
        i++;
    }
}
*/

void ft_valid_lexcal_cmd(t_minishell *sh)
{
    t_node  *tmp;

    tmp = sh->head;
    while (tmp)
    {
//        printf("cmd[0] de tmp: %s\n", tmp->cmd[0]);
//        if (tmp->prev)
//        {
//            if (tmp->prev->cmd[0][0] != '|')
//            {
//                printf("Entrou no 2º if do prev\n");
//                sh->tmp3 = ft_split(tmp->prev->cmd[0], ' ');
//            }
//            printf("cmd[0] de tmp->prev: %s\n", tmp->prev->cmd[0]);
//        }
//        if (tmp->next)
//        {
//            if (tmp->next->cmd[0][0] != '|')
//            {
//                printf("Entrou no 2º if do next\n");
//                sh->tmp4 = ft_split(tmp->next->cmd[0], ' ');
//            }
//            printf("cmd[0] de tmp->next: %s\n", tmp->next->cmd[0]);
//        }
//        sh->tmp3 = ft_split(tmp->prev->cmd[0], ' ');
//        sh->tmp4 = ft_split(tmp->next->cmd[0], ' ');
        if ((!tmp->prev) && (tmp->cmd[0][0] == '|'))
        {
            sh->ret = -6;
            sh->erro ="|"; 
            return ;
        }
        else if ((tmp->cmd[0][0] == '|') && (tmp->next) && (tmp->next->cmd[0][0] == '|'))
        {
            sh->ret = -6;
            sh->erro = "|";
            return ;
        }
//        else if ((tmp->cmd[0][0] == '|') && (sh->tmp3 && sh->tmp4))
//        {
//            if ((!ft_access_command(sh->tmp3[0], sh->path)))
//            {
//                sh->ret = -7;
//                sh->erro = sh->tmp3[0];
//                return ;           
//            }
//            else if ((!ft_access_command(sh->tmp4[0], sh->path)))
//            {
//                sh->ret = -7;
//                sh->erro = sh->tmp4[0];
//                return ;           
//            }
//        }
//        ft_free_minishell_double_aux(sh->tmp3);
//        ft_free_minishell_double_aux(sh->tmp4);
        tmp = tmp->next;
    }
}



//void ft_valid_lexcal_cmd(t_minishell *sh)
void ft_put_cmd_in_lst(t_minishell *sh)
{
    long    i;

//    printf("Dentro da valide_lexcal_cmd | inicio\n");
    i = 0;
    sh->tmp3 = (char **)malloc(sizeof(char *) * 2);
    if (!sh->tmp3)
    {
        sh->ret = -3;
        return ;
    }
    sh->tmp3[0] = NULL;
    sh->tmp3[1] = NULL;
    while (sh->parse_str[i])
    {
        sh->tmp3[0] = ft_strdup(sh->parse_str[i]);
        i++;
//        while (sh->parse_str[i] && !ft_pipe_or_redirect(sh, i))
        while (sh->parse_str[i] && !ft_pipe_or_redirect(sh->parse_str[i]))
        {
            sh->tmp1 = ft_strjoin(sh->tmp3[0], " ");
            sh->tmp2 = ft_strjoin(sh->tmp1, sh->parse_str[i]);
            if (!sh->tmp1 || !sh->tmp2)
            {
                ft_free_minishell_single_aux(sh->tmp1);
                ft_free_minishell_single_aux(sh->tmp2);
                ft_free_minishell_double_aux(sh->tmp3);
                sh->ret = -3;
                return ;
            }
            ft_free_minishell_single_aux(sh->tmp3[0]);
            sh->tmp3[0] = sh->tmp2;
            ft_free_minishell_single_aux(sh->tmp1);
            sh->tmp2 = NULL;
            i++;
        }
        ft_list_add_last(&sh->head, ft_node_create(sh->tmp3));
        sh->tmp3[0] = NULL;
//        if (sh->parse_str[i] && ft_pipe_or_redirect(sh, i))
        if (sh->parse_str[i] && ft_pipe_or_redirect(sh->parse_str[i]))
        {
            sh->tmp3[0] = ft_strdup(sh->parse_str[i]);
            ft_list_add_last(&sh->head, ft_node_create(sh->tmp3));
            sh->tmp3[0] = NULL;
        }
        if (sh->parse_str[i])
            i++;
    }
    ft_free_minishell_double_aux(sh->tmp3);
//    printf("Dentro da valide_lexcal_cmd | fim\n");
}

void ft_parse(t_minishell *sh)
{
//    printf("Dentro da parse | inicio\n");
    if (sh)
    {
        ft_valid_empty_cmd(sh);
        if (sh->ret < 0)
            return ;
//        printf("Após a emplty cmd ret: %d\n", sh->ret);
        ft_valid_quotes(sh);
        if (sh->ret < 0)
            return ;
        // ft_valid_redirect_out(sh);
        // if (sh->ret < 0)
        //     return ;
        // ft_valid_redirect_in(sh);
         //if (sh->ret < 0)
         //    return ;

//        printf("Após a valid quotes ret: %d\n", sh->ret);
        sh->parse_str = ft_split(sh->line, ' ');
        if (!sh->parse_str)
        {
            sh->ret = -3;
            return ;
        }
//        printf("Após a split ret: %d\n", sh->ret);
//        ft_valid_lexcal_cmd(sh);
        ft_put_cmd_in_lst(sh);
        if (sh->ret < 0)
            return ;
        ft_first_cmd(sh);
        if (sh->ret < 0)
            return ;
		ft_redirect_2(sh);
		 if (sh->ret < 0)
            return ;
        ft_print_list(sh);
        //ft_print_rev_list(sh);
//        printf("Após a lexcal_cmd ret: %d\n", sh->ret);
        //ft_valid_lexcal_cmd(sh);
        //if (sh->ret < 0)
        //    return ;
    }
    else
        sh->ret = -1;
//    printf("Dentro da parse | fim\n");
}


/*
        if (!ft_valid_command_aux(sh, sh->parse_str[i]) || !ft_valid_file(sh, i))
        {
            sh->ret = -4;
            sh->erro = sh->parse_str[i];
            ft_free_minishell_double_aux(sh->tmp3);
            return ;
        }
*/