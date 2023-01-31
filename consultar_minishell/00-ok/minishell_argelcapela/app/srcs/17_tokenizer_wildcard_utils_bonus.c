/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_tokenizer_wildcard_utils_bonus.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 22:26:04 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/13 18:59:20 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ms_free_files(t_file **files)
{
	t_file	*del;

	ms_go_start(files);
	while ((*files)->next != NULL)
	{
		del = (*files);
		(*files) = (*files)->next;
		ms_file_delete(&del);
	}
}

t_file	*ms_get_current_directory(void)
{
	struct dirent	*de;
	DIR				*dr;
	t_file			*files;
	t_file			*prev;
	t_file			*start;

	dr = opendir(".");
	de = readdir(dr);
	files = ft_calloc(1, sizeof(t_file));
	start = files;
	while (de != NULL)
	{
		prev = files;
		if (de->d_name[0] != '.')
		{
			files->name = ft_strdup(de->d_name);
			files->next = ft_calloc(1, sizeof(t_file));
			files = files->next;
			files->prev = prev;
		}
		de = readdir(dr);
	}
	closedir(dr);
	return (start);
}

void	ms_file_delete(t_file **head)
{
	t_file	*prev;
	t_file	*del;

	if (!(*head)->prev)
	{
		*head = (*head)->next;
		ft_free_ptr((void *) &(*head)->prev->name);
		ft_free_ptr((void *) &(*head)->prev);
	}
	else if (!(*head)->next)
	{
		ft_free_ptr((void *) &(*head)->name);
		ft_free_ptr((void *) &(*head));
	}
	else
	{
		prev = (*head)->prev;
		del = *head;
		*head = (*head)->next;
		prev->next = *head;
		(*head)->prev = prev;
		ft_free_ptr((void *) &del->name);
		ft_free_ptr((void *) &del);
	}
}

int	valid_chr(char chr)
{
	if (chr != '\'' && chr != '\"' \
		&& chr != '\0' && chr != ' ' && chr != '$')
		return (1);
	return (0);
}

int	check_aste(char **wc_split, int i, char *wc, t_file *head)
{
	int		len;
	char	*after_aste;

	after_aste = NULL;
	after_aste = head->name + head->cursor;
	len = ft_mtx_size((void **) wc_split);
	if (i == 0 && wc[0] != '*' && ft_strncmp(wc_split[0],
			head->name, ft_strlen(wc_split[0])) != 0)
		return (1);
	else if (i == (len - 1) && wc[0] == '*'
		&& wc[ft_strlen(wc) - 1] != '*'
		&& ft_rev_strncmp(head->name, wc_split[i],
			ft_strlen(wc_split[i])) != 0)
		return (1);
	else if (ft_strnstr(after_aste, wc_split[i],
			ft_strlen(head->name)) == NULL)
		return (1);
	return (0);
}
