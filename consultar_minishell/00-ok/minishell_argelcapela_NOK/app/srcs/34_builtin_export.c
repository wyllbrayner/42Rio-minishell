/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   34_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:42 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/13 16:53:58 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<_minishell.h>

static void	add_env_by_key_2(t_ms *ms, char *key, char *value, char *tmp)
{
	char	*value_replaced;

	value_replaced = ft_str_replace_all(ft_strdup(value), T_SPACE, " ");
	if (ms_is_in_env(ms, key))
		update_env_value(ms->envs, key, value_replaced);
	else
		ms_add_env(&ms->envs, key, value_replaced);
	ft_free_ptr((void *) &value_replaced);
	ft_free_ptr((void *) &tmp);
	ms->p->cmds->exit_code = 0;
}

static void	add_env_by_key(t_ms *ms, const t_cmd *curr_cmd)
{
	char	*key;
	char	*value;
	int		equal_index;
	char	*tmp;

	equal_index = ft_str_indexof(curr_cmd->cmd_splited_by_space[1], \
	"=", ft_strlen(curr_cmd->cmd_splited_by_space[1]));
	if (equal_index == -1)
		return ;
	tmp = ft_substr(curr_cmd->cmd_splited_by_space[1], 0, equal_index);
	key = tmp;
	value = curr_cmd->cmd_splited_by_space[1] + equal_index + 1;
	add_env_by_key_2(ms, key, value, tmp);
}

static int	check_export_errors(t_ms *ms, char *check,
int aux, t_cmd *curr_cmd)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(curr_cmd->cmd_line + 6,
			0, ft_strlen(curr_cmd->cmd_line));
	tmp2 = ft_strtrim(tmp, " ");
	ft_free_ptr((void *) &tmp);
	i = -1;
	while (check[++i])
	{	
		if ((!ft_isalnum(check[i]) && check[i] != '=') || ft_isdigit(check[0]))
		{
			ft_printf_to_fd(aux, "miniheaven: export:\
 `%s': not a valid identifier\n", tmp2);
			ft_free_ptr((void *) &tmp2);
			ms->p->cmds->exit_code = 1;
			ft_free_ptr((void *) &check);
			return (1);
		}
	}
	ft_free_ptr((void *) &tmp2);
	ft_free_ptr((void *) &check);
	return (0);
}

int	ms_export_checks(t_cmd *curr_cmd, char **check)
{
	char	**split;

	if (ft_strnstr(curr_cmd->my_prompt->this_p_line, \
"env", ft_strlen(curr_cmd->my_prompt->this_p_line)) != NULL)
		return (1);
	(*check) = curr_cmd->cmd_splited_by_space[1];
	if (ft_strrchr((*check), '=') == NULL)
		return (1);
	else if (ft_strncmp((*check), "=", ft_strlen((*check))) == 0)
	{
		ft_printf_to_fd(2, "miniheaven: export:\
 `=': not a valid identifier\n");
		return (1);
	}
	else
	{
		split = ft_split((*check), '=');
		(*check) = ft_strdup(split[0]);
		ft_mtx_free((void **) split);
	}
	return (0);
}

void	ms_export(t_ms *ms, t_cmd *curr_cmd)
{
	int		aux;
	int		clo;
	char	*check;

	clo = 0;
	aux = 0;
	aux = bridge_builtion_other_cmds(curr_cmd, curr_cmd->my_prompt, &clo);
	if (!curr_cmd->cmd_splited_by_space[1]
		|| *curr_cmd->cmd_splited_by_space[1] == '\0'
		|| *curr_cmd->cmd_splited_by_space[1] == ' ')
		print_sorted_env(ms, aux);
	else if (ms_export_checks(curr_cmd, &check))
		return ;
	else if (check_export_errors(ms, check, aux, curr_cmd) == 0)
		add_env_by_key(ms, curr_cmd);
	ms->p->cmds->exit_code = 0;
	if (clo)
		close(aux);
}
