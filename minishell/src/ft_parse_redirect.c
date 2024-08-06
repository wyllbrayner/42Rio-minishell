/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiniz <jodiniz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:45:06 by jodiniz           #+#    #+#             */
/*   Updated: 2023/03/16 22:19:20 by jodiniz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

void	organize_command(t_node *temp, char **path)
{
	bool	after_redirect;

	after_redirect = false;
	while (temp)
	{
		if (is_redirect(&temp, &after_redirect))
			continue ;
		else if (after_redirect)
		{
			after_redirect = false;
			if (temp->next != NULL)
			{
				temp = temp->next;
				continue ;
			}
		}
		else if (prev_redirect(&temp))
			continue ;
		else
			temp->command = ft_access(temp->first_cmd, path);
		temp = temp->next;
	}
}

void	organize_file_out(t_node *temp)
{
	t_node	*find;
	bool	flag;

	while (temp)
	{
		if (temp->command == 1)
		{
			find = temp;
			flag = 0;
			while (find)
			{
				if (find->first_cmd[0] == '|' || find->next == NULL)
				{
					if (file_swap_out(&temp, &find, &flag))
						break ;
				}
				if (flag)
					break ;
				find = find->next;
			}
		}
		temp = temp->next;
	}
}

void	organize_file_in(t_node *temp)
{
	t_node	*find;
	bool	flag;

	while (temp)
	{
		if (temp->command == 1)
		{
			find = temp;
			flag = 0;
			while (find)
			{
				if (find->first_cmd[0] == '|' || find->next == NULL)
				{
					if (file_swap_in(&temp, &find, &flag))
						break ;
				}
				if (flag)
					break ;
				find = find->next;
			}
		}
		temp = temp->next;
	}
}

int	is_redirect(t_node **temp, bool *redirect)
{
	t_node	*tmp;

	tmp = *temp;
	if (tmp->first_cmd[0] == '<' || tmp->first_cmd[0] == '>')
	{
		*redirect = true;
		if (tmp->next != NULL)
		{
			tmp = tmp->next;
			*temp = tmp;
			return (1);
		}
	}
	*temp = tmp;
	return (0);
}

int	prev_redirect(t_node **temp)
{
	t_node	*tmp;

	tmp = *temp;
	if ((tmp->prev != NULL ) && (tmp->prev->first_cmd[0] == '<' || \
		tmp->prev->first_cmd[0] == '>'))
	{
		tmp->command = false;
		tmp = tmp->next;
		tmp = *temp;
		return (1);
	}
	tmp = *temp;
	return (0);
}
