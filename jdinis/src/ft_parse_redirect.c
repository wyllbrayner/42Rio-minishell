/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiniz <jodiniz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:45:06 by jodiniz           #+#    #+#             */
/*   Updated: 2023/03/15 17:59:38 by jodiniz          ###   ########.fr       */
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

// int file_swap(t_node **temp, t_node **find, bool *flag)
// {
	//t_node *temp_node = *temp;
	//t_node *find_node = *find;

	//while (find_node)
	//{
	//	if (find_node->first_cmd[0] == '|' || find_node->prev == NULL)
	//	{
	//		*flag = 1;
	//		*find = find_node;
	//		break ; 
	//	}
	//	if (find_node->first_cmd[0] == '>' && find_node->next)
	//	{
	//		temp_node->outfile = find_node->next->redirect_file_fd;
	//		*flag = 1;
	//		*find = find_node;
	//		*temp = temp_node;
	//		break ; 
	//	}
	//	find_node = find_node->prev;
	//}
	//*temp = temp_node;
	//*find = find_node;
	//return (0); // sucesso
// }

// void	organize_file_in(t_node *temp)
// {
// 	t_node	*find;
// 	bool	flag;

// 	while(temp)
// 	{
// 		if (temp->command == 1)
// 		{
// 			find = temp;
// 			flag = 0;
// 			while (find)
// 			{
// 				if (find->first_cmd[0] == '|' || find->next == NULL)
// 				{
// 					if (find->prev)
// 						find = find->prev;
// 					else
// 						break ;
// 					while (find)
// 					{
// 						if (find->first_cmd[0] == '|' || find->prev == NULL)
// 						{
// 							flag = 1;
// 							break ;
// 						}
// 						if (find->first_cmd[0] == '<' && find)
// 						{
// 							temp->infile = find->next->redirect_file_fd;
// 							flag = 1;
// 							break ;
// 						}
// 						find = find->prev;
// 					}
// 				}
// 				if (flag)
// 					break ;
// 				find = find->next;
// 			}
// 		}
// 		temp = temp->next;
// 	}
// }

// void	organize_file_out(t_node *temp)
// {
// 	t_node	*find;
// 	bool	flag;

// 	while(temp)
// 	{
// 		if (temp->command == 1)
// 		{
// 			find = temp;
// 			flag = 0;
// 			while (find)
// 			{
// 				if (find->first_cmd[0] == '|' || find->next == NULL)
// 				{
// 					if (find->prev)
// 						find = find->prev;
// 					else
// 						break ;
// 					while (find)
// 					{
// 						if (find->first_cmd[0] == '|' || find->prev == NULL)
// 						{
// 							flag = 1;
// 							break ;
// 						}
// 						if (find->first_cmd[0] == '>' && find)
// 						{
// 							temp->outfile = find->next->redirect_file_fd;
// 							flag = 1;
// 							break ;
// 						}
// 						find = find->prev;
// 					}
// 				}
// 				if (flag)
// 					break ;
// 				find = find->next;
// 			}
// 		}
// 		temp = temp->next;
// 	}
// }

// void	organize_command(t_node *temp, char **path)
// {
// 	bool	after_redirect;

// 	after_redirect = false;
// 	while (temp)
// 	{
// 		if (temp->first_cmd[0] == '<' || temp->first_cmd[0] == '>')
// 		{
// 			after_redirect = true;
// 			if (temp->next != NULL)
// 			{
// 				temp = temp->next;
// 				continue;
// 			}
// 		}
// 		else if (after_redirect)
// 		{
// 			after_redirect = false;
// 			 if (temp->next != NULL)
// 			{
// 				temp = temp->next;
// 				continue;
// 			}
// 		}
// 		else if ((temp->prev != NULL ) && (temp->prev->first_cmd[0] == '<'
		//|| temp->prev->first_cmd[0] == '>'))
// 		{
// 			temp->command = false;
// 			temp = temp->next;
// 			continue;
// 		}
// 		else
// 			temp->command = ft_access(temp->first_cmd, path);
// 		temp = temp->next;
// 	}
// }
