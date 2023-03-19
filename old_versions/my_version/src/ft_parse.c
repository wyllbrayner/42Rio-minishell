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

static void	ft_valid_empty_cmd(t_minishell *sh);
static void	ft_valid_amount_of_quotes(t_minishell *sh);
static void	ft_heredoc(t_minishell *sh);

//    printf("Dentro da parse | inicio errnbr: %i\n", sh->errnbr);
//        printf("Após a valid quotes ret: %d\n", sh->ret);
//    printf("Dentro da parse | fim errnbr: %i\n", sh->errnbr);
//        ft_print_list(sh->head);
void	ft_parse(t_minishell *sh)
{
	ft_valid_empty_cmd(sh);
	if (sh->ret < 0)
		return ;
	add_history(sh->line);
	ft_valid_amount_of_quotes(sh);
	if (sh->ret < 0)
		return ;
	ft_valid_redirect(sh);
	if (sh->ret < 0)
		return ;
	ft_cmd_builder(sh);
	if (sh->ret < 0)
		return ;
	ft_valid_lexcal_cmd(sh);
	if (sh->ret < 0)
		return ;
	ft_redirect_builder(sh);
	if (sh->ret < 0)
		return ;
	ft_heredoc(sh);
	if (sh->ret < 0)
		return ;
}

//    printf("Dentro da ft_valid_empty_cmd | inicio errnbr: %i\n", sh->errnbr);
//    printf("Dentro da ft_valid_empty_cmd | fim errnbr: %i\n", sh->errnbr);
static void	ft_valid_empty_cmd(t_minishell *sh)
{
	sh->tmp0 = ft_strtrim(sh->line, " ");
	if (!sh->tmp0)
	{
		g_sig.errnbr = errno;
		sh->ret = -3;
		return ;
	}
	if ((ft_strlen(sh->tmp0) == 0))
		sh->ret = -8;
	ft_free_minishell_single_aux(sh->line);
	sh->line = NULL;
	sh->line = sh->tmp0;
	sh->tmp0 = NULL;
}

//    printf("Dentro da ft_valid_quotes | inicio\n");
//    printf("Dentro da ft_valid_quotes | fim\n");
static void	ft_valid_amount_of_quotes(t_minishell *sh)
{
	long	i;
	long	squote;
	long	dquote;

	i = 0;
	squote = 0;
	dquote = 0;
	while (sh->line[i])
	{
		if (sh->line[i] == '\'')
			squote++;
		else if (sh->line[i] == '\"')
			dquote++;
		i++;
	}
	if (!ft_valid_quote(squote, dquote))
		sh->ret = -5;
}

static void	ft_heredoc(t_minishell *sh)
{
	t_node	*head;

	head = sh->head;
	while (head && (sh->ret == 0))
	{
		if (head->first_cmd[0] != '|' && head->first_cmd[0] != '<' \
				&& head->first_cmd[0] != '>')
		{
			if (head->prev)
			{
				if (ft_strncmp(head->prev->first_cmd, "<<", 2) == 0)
				{
					ft_heredoc_builder(sh, head);
					if (sh->ret < 0)
						break ;
				}
			}
		}
		head = head->next;
	}
}

/*
void ft_parse(t_minishell *sh)
{
//    printf("Dentro da parse | inicio errnbr: %i\n", sh->errnbr);
    if (sh)
    {
        ft_valid_empty_cmd(sh);
        if (sh->ret < 0)
            return ;
//    printf("Dentro da parse | intermediario errnbr: %i\n", sh->errnbr);
        add_history(sh->line);
//        printf("Após a emplty cmd ret: %d\n", sh->ret);
        ft_valid_amount_of_quotes(sh);
        if (sh->ret < 0)
            return ;
        ft_valid_redirect_0(sh);
        if (sh->ret < 0)
            return ;
        ft_valid_redirect_1(sh);
        if (sh->ret < 0)
            return ;
        ft_cmd_builder(sh);
        if (sh->ret < 0)
            return ;
//        ft_print_list(sh->head);
        sh->parse_str = ft_split(sh->line, ' ');
        if (!sh->parse_str)
        {
            sh->ret = -3;
            sh->errnbr = errno;
            return ;
        }
//        ft_print_list(sh->head);
        ft_valid_lexcal_cmd(sh);
        if (sh->ret < 0)
        {
            sh->errnbr = 258;
            return ;
        }
//        ft_print_rev_list(sh->head);
        ft_redirect(sh);
        if (sh->ret < 0)
            return ;
        ft_heredoc(sh);
        if (sh->ret < 0)
            return ;

//        printf("Após a valid quotes ret: %d\n", sh->ret);
    }
    else
        sh->ret = -1;
//    printf("Dentro da parse | fim errnbr: %i\n", sh->errnbr);
}
*/
