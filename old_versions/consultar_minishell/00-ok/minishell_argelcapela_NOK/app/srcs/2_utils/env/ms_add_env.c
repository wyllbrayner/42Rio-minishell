/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:57:03 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/09 17:15:31 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ms_add_env(t_env **env, char *key, char *value)
{
	t_env	*head;

	head = *env;
	if (head == NULL)
	{
		head = malloc (sizeof(t_env));
		head->key = ft_strdup(key);
		head->value = ft_strdup(value);
		head->next = NULL;
		head->prev = NULL;
		*env = head;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		ft_free_ptr((void *) &head->next);
		head->next = malloc (sizeof(t_env));
		head->next->key = ft_strdup(key);
		head->next->value = ft_strdup(value);
		head->next->next = NULL;
		head->next->prev = head;
	}
}
