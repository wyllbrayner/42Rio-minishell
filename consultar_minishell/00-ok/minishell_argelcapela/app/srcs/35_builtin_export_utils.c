/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   35_builtin_export_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:25 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/13 15:45:02 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	cmpstr(void *v1, void *v2)
{
	char	*a1;
	char	*a2;

	a1 = *(char **) v1;
	a2 = *(char **) v2;
	return (ft_strncmp(a1, a2, ft_strlen(a1)));
}

static void	swap(t_qs *qs, void *v1, void *v2, int size)
{
	char	*buffer;

	buffer = malloc(size * sizeof(char));
	ft_memcpy(buffer, v1, size);
	ft_memcpy(v1, v2, size);
	ft_memcpy(v2, buffer, size);
	if (qs->free_qs == NULL)
	{
		qs->free_qs = malloc(sizeof(t_qs));
		qs->free_qs->prev = NULL;
		qs->free_qs->next = NULL;
		qs->free_qs->buffer = buffer;
	}
	else
	{
		while (qs->free_qs->next != NULL)
			qs->free_qs = qs->free_qs->next;
		ft_free_ptr((void *) &qs->free_qs->next);
		qs->free_qs->next = malloc(sizeof(t_qs));
		qs->free_qs->next->prev = qs->free_qs;
		qs->free_qs->next->next = NULL;
		qs->free_qs->next->buffer = buffer;
	}
}

void	quicksort(t_qs *qs, int left, int right,
						int (*comp)(void*, void*))
{
	int		i;

	qs->mid = (left + right) / 2;
	if (left >= right)
		return ;
	qs->vl = (char *)(qs->v + (left * qs->size));
	qs->vr = (char *)(qs->v + (qs->mid * qs->size));
	swap(qs, qs->vl, qs->vr, qs->size);
	qs->last = left;
	i = left;
	while (i <= right)
	{
		qs->vt = (char *)(qs->v + (i * qs->size));
		if ((*comp)(qs->vl, qs->vt) > 0)
		{
			++(qs->last);
			qs->v3 = (char *)(qs->v + (qs->last * qs->size));
			swap(qs, qs->vt, qs->v3, qs->size);
		}
		i++;
	}
	qs->v3 = (char *)(qs->v + (qs->last * qs->size));
	swap(qs, qs->vl, qs->v3, qs->size);
	quicksort(qs, left, qs->last - 1, comp);
	quicksort(qs, qs->last + 1, right, comp);
}

void	ms_free_qs(const t_ms *ms, int aux, char **line, t_free **curr_qs)
{
	int	i;

	i = 0;
	while ((*curr_qs)->prev)
		(*curr_qs) = (*curr_qs)->prev;
	while ((*curr_qs)->next)
	{
		(*curr_qs) = (*curr_qs)->next;
		if ((*curr_qs)->prev->buffer != NULL)
			ft_free_ptr((void *) &(*curr_qs)->prev->buffer);
		if ((*curr_qs)->prev != NULL)
			ft_free_ptr((void *) &(*curr_qs)->prev);
	}
	ft_free_ptr((void *) &(*curr_qs)->buffer);
	ft_free_ptr((void *) &(*curr_qs));
	while (ms->str_export[i])
	{
		if (ms->str_export[i])
		{
			(*line) = ft_printf_to_var("declare -x %s\n", ms->str_export[i]);
			ft_putstr_fd((*line), aux);
			ft_free_ptr((void *) line);
		}
		i++;
	}
}

void	print_sorted_env(t_ms *ms, int aux)
{
	char	*line;
	t_free	*curr_qs;

	ms->str_export = env_to_array(ms);
	ms->qs = ft_calloc (1, sizeof(t_qs));
	ms->qs->free_qs = NULL;
	ms->qs->v = ms->str_export;
	ms->qs->size = sizeof(char *);
	quicksort(ms->qs, 0, ft_mtx_size((void **) ms->str_export) - 1, \
			(int (*)(void *, void *))(cmpstr));
	curr_qs = ms->qs->free_qs;
	ms_free_qs(ms, aux, &line, &curr_qs);
	ft_mtx_free((void **) ms->str_export);
}
