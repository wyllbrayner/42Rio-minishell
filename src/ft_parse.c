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

void    ft_parse_comand_is_valid(t_minishell *sh)
{
    long    i;

    i = 0;
    while (sh->parse_str[i])
    {
        if ((ft_strncmp(sh->parse_str[i], "|", 1) == 0) || (ft_strncmp(sh->parse_str[i], "<", 1) == 0) || (ft_strncmp(sh->parse_str[i], "<<", 2) == 0) || (ft_strncmp(sh->parse_str[i], ">", 1) == 0) || (ft_strncmp(sh->parse_str[i], ">>", 2) == 0))
            printf("%s     é um PIPE ou > ou <\n", sh->parse_str[i]);
        else
            printf("%s não é um PIPE ou > ou <\n", sh->parse_str[i]);
        i++;        
    }

// int access(const char *pathname, int mode);
// F_OK, R_OK, W_OK, X_OK
}

/*
char *ft_join_path(char const *path, char const *cmd)
{
    char *tmp1;
    char *tmp2;

    tmp1 = NULL;
    tmp2 = NULL;
    tmp1 = ft_strjoin(path, "/");
    if (!tmp1)
        return (NULL);
    tmp2 = ft_strjoin(tmp1, cmd);
    if (!tmp2)
    {
        ft_free_minishell_single_aux(tmp1);
        return (NULL);
    }
    return(tmp2);
}
*/

void ft_parse(t_minishell *sh)
{
//    printf("ft_parse -> g_control.running: %i | g_control.ret: %i\n", g_control.running, g_control.ret);
    sh->parse_str = ft_split(sh->line, ' ');
//    ft_parse_comand_is_valid(sh);
}
