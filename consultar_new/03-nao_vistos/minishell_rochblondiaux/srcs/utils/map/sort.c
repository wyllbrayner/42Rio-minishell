/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_swap(char **tab, int i, int i1)
{
	char	*temp;

	temp = tab[i1];
	tab[i1] = tab[i];
	tab[i] = temp;
}

int	ft_compare(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s2[i] == '\0')
		return (0);
	return (-s2[i]);
}

void	ft_sort_string_tab(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		j = i;
		while (tab[j])
		{
			if (ft_compare(tab[i], tab[j]) > 0)
				ft_swap(tab, i, j);
			j++;
		}
		i++;
	}
	tab[i] = 0;
}

void	print__(char **a, t_env *env)
{
	size_t	i;
	t_env	*tmp;
	char	*value;

	i = -1;
	while (a[++i])
	{
		tmp = get_map_element(env, a[i]);
		if (!tmp)
			value = "";
		else
			value = tmp->value;
		printf("declare -x %s=\"%s\"\n", a[i], value);
	}
}

void	print_sorted_map(t_env *env)
{
	char	**a;
	size_t	i;
	t_env	*tmp;

	a = malloc(sizeof(char *) * map_length(env) + 1);
	i = 0;
	tmp = env;
	while (env)
	{
		a[i++] = ft_strdup(env->key);
		env = env->next;
	}
	a[i] = NULL;
	ft_sort_string_tab(a);
	print__(a, tmp);
	free_array(a);
}
