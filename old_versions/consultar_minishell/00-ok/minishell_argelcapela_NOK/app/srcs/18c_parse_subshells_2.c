/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18c_parse_subshells_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/08 17:52:05 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	ms_parse_subshells_replace_loop(t_ms *ms, \
t_psub *psub, char **tmp)
{
	ft_free_ptr((void *) &(*tmp));
	*(tmp) = ft_str_replace(
			ms->shell_line_tokenized, psub->head->str, T_JOKER2);
	ms->shell_line_tokenized = ft_strdup((*tmp));
	psub->head = psub->head->next;
}

static t_psub	*init_psub(t_ms *ms)
{
	t_psub	*new;

	new = (t_psub *) ft_calloc(1, sizeof(t_psub));
	new->str = ms->shell_line_tokenized;
	new->start = 0;
	new->end = 0;
	new->r_leftp = 0;
	new->r_rightp = 0;
	new->save_subshell = 0;
	new->ssub = (t_ssub *) ft_calloc(1, sizeof(t_ssub));
	new->ssub->prev = NULL;
	new->ssub->next = NULL;
	new->head = new->ssub;
	new->n_subs = 0;
	new->i_subs = 0;
	new->curr_p = NULL;
	return (new);
}

t_psub	*token_subshells_pre_split_connectors(t_ms *ms)
{
	int		i;
	int		len;
	char	*tmp;
	t_psub	*psub;

	if (ft_count_chr(ms->shell_line_tokenized, '(') == 0)
		return (NULL);
	psub = init_psub(ms);
	i = -1;
	len = ft_strlen(psub->str);
	while (i++ < len)
		ms_parse_subshells_loop(psub, i);
	i = -1;
	tmp = NULL;
	psub->head = psub->ssub;
	while ((++i < psub->n_subs) && psub->head)
		ms_parse_subshells_replace_loop(ms, psub, &tmp);
	ft_free_ptr((void *) &tmp);
	return (psub);
}

static int	untoken_subshells_loop(t_ms *ms, t_psub *psub, \
char **tmp, int x)
{
	if (ft_strnstr(ms->slt_splited_by_connectors[x], T_JOKER2,
			ft_strlen(ms->slt_splited_by_connectors[x])) != NULL)
	{
		ft_free_ptr((void *) &(*tmp));
		(*tmp) = ft_str_replace(ms->slt_splited_by_connectors[x],
				T_JOKER2, psub->head->str);
		ms->slt_splited_by_connectors[x] = ft_strdup((*tmp));
		psub->head = psub->head->next;
		psub->i_subs++;
		return (0);
	}
	else
		return (1);
}

void	untoken_subshells_pos_split_connectors(t_ms *ms, t_psub *psub)
{
	int		x;
	char	*tmp;

	x = -1;
	tmp = NULL;
	while (psub && ms->slt_splited_by_connectors[++x] && psub->head)
	{
		while (psub->i_subs < psub->n_subs)
		{
			if (!untoken_subshells_loop(ms, psub, &tmp, x))
				continue ;
			else
				break ;
		}
	}
	ft_free_ptr((void *) &tmp);
}

// (echo oi && echo oi) && (echo oi && echo oi)
// (echo oi && echo oi)&&(echo oi)
// ((echo oi && echo oi)|wc -l) > a