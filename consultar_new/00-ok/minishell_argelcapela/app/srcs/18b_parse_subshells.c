/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18b_parse_subshells.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/08 16:32:34 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

//4!
static void	ms_parse_subshells_replace_loop(t_p **curr_p, \
t_psub *psub, char **tmp, int i)
{
	ft_free_ptr((void *) &(*tmp));
	(*curr_p)->subs[i].shell_line = ft_substr(psub->head->str + 1, \
0, ft_strlen(psub->head->str) - 2);
	*(tmp) = ft_str_replace(
			(*curr_p)->this_p_line, psub->head->str, T_SUBSHELL);
	(*curr_p)->this_p_line = ft_strdup((*tmp));
	ms_init(&((*curr_p)->subs[i]), (*curr_p)->ms->argc,
		(*curr_p)->ms->argv, (*curr_p)->ms->envp);
		psub->head = psub->head->next;
}

//3!
void	ms_parse_subshells_save_subshell(t_psub *psub)
{
	psub->r_leftp = 0;
	psub->r_rightp = 0;
	if (psub->curr_p)
		psub->curr_p->n_subs++;
	else
		psub->n_subs++;
	if (psub->head == NULL)
	{
		psub->ssub->next = (t_ssub *) ft_calloc(1, sizeof(t_ssub));
		psub->ssub->next->next = NULL;
		psub->ssub->next->prev = psub->ssub;
		psub->head = psub->ssub->next;
	}
	psub->head->str = ft_substr(
			psub->str + psub->start, 0, psub->end + 1);
	psub->head = psub->head->next;
	psub->save_subshell = 0;
}

//2!
void	ms_parse_subshells_loop(t_psub *psub, int i)
{
	if (psub->str[i] == '(')
	{
		psub->r_leftp++;
		if (psub->r_leftp == 1)
			psub->start = i;
	}
	if (psub->str[i] == ')')
	{
		psub->r_rightp++;
		if (psub->r_rightp == psub->r_leftp)
		{
			psub->end = i;
			psub->save_subshell = 1;
		}
	}
	if (psub->save_subshell)
		ms_parse_subshells_save_subshell(psub);
}

//1!
static t_psub	*init_psub(t_p **curr_p)
{
	t_psub	*new;

	new = (t_psub *) ft_calloc(1, sizeof(t_psub));
	new->str = (*curr_p)->this_p_line;
	new->start = 0;
	new->end = 0;
	new->r_leftp = 0;
	new->r_rightp = 0;
	new->save_subshell = 0;
	new->ssub = (t_ssub *) ft_calloc(1, sizeof(t_ssub));
	new->ssub->prev = NULL;
	new->ssub->next = NULL;
	new->head = new->ssub;
	new->curr_p = (*curr_p);
	(*curr_p)->i_subs = 0;
	(*curr_p)->n_subs = 0;
	new->n_subs = 0;
	new->i_subs = 0;
	return (new);
}

void	ms_parse_subshells(t_p **curr_p)
{
	int		i;
	int		len;
	char	*tmp;
	t_psub	*psub;

	if (ft_count_chr((*curr_p)->this_p_line, '(') == 0)
		return ;
	psub = init_psub(curr_p);
	i = -1;
	len = ft_strlen(psub->str);
	while (i++ < len)
		ms_parse_subshells_loop(psub, i);
	(*curr_p)->subs = (t_ms *) ft_calloc((*curr_p)->n_subs, sizeof(t_ms));
	i = -1;
	tmp = NULL;
	psub->head = psub->ssub;
	while ((++i < (*curr_p)->n_subs) && psub->head)
		ms_parse_subshells_replace_loop(curr_p, psub, &tmp, i);
	ft_free_ptr((void *) &tmp);
	free_ssub(psub->ssub);
	ft_free_ptr((void *) &psub);
}

// (echo oi | (tr o a)) && ls
// (echo oi) && ls
// (echo oi)|tr o a && ls
// (echo oi)|tr|(ls) && ls