/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_parse_input_output.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:19 by acapela-          #+#    #+#             */
/*   Updated: 2022/12/19 18:37:06 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

//5!
int	symbol_here(char *cursor, int *jump, int *type)
{
	char	**symbols;
	int		i;
	int		len;

	symbols = (char **) ft_calloc(4, sizeof(char *));
	symbols[0] = ft_strdup(">>");
	symbols[1] = ft_strdup("<<");
	symbols[2] = ft_strdup(">");
	symbols[3] = ft_strdup("<");
	i = -1;
	while (++i < 4)
	{
		len = ft_strlen(symbols[i]);
		if (ft_strncmp(cursor, symbols[i], len) == 0)
		{
			if (jump)
				*jump = len;
			if (type)
				*type = i;
			ft_mtx_free_chr(symbols);
			return (1);
		}
	}
	ft_mtx_free_chr(symbols);
	return (0);
}

//4!
char	*get_symbol(t_cmd *curr_cmd, char *cursor, int *jump)
{
	char	*cut;
	int		i;
	char	*tmp;

	i = 0;
	i += *jump;
	while (cursor[i])
	{
		if (symbol_here(&cursor[i], NULL, NULL)
			|| cursor[i] == ' ')
			break ;
		i++;
	}
	cut = ft_substr(cursor, 0, i);
	tmp = ft_substr(&cut[*jump], 0, i);
	ft_free_ptr((void *) &curr_cmd->symbol_path);
	curr_cmd->symbol_path = ft_strtrim(tmp, " ");
	ft_free_ptr((void *) &tmp);
	return (cut);
}

//3!
int	has_symbols(char *cmd_line)
{
	int	len;

	len = ft_strlen(cmd_line);
	if ((ft_strnstr(cmd_line, ">>", len) != NULL)
		|| (ft_strnstr(cmd_line, "<<", len) != NULL)
		|| (ft_strnstr(cmd_line, ">", len) != NULL)
		|| (ft_strnstr(cmd_line, "<", len) != NULL))
		return (1);
	return (0);
}

//2!
int	glued(t_cmd **curr_cmd)
{
	char	*tmp;

	tmp = ft_super_replace_all((*curr_cmd)->cmd_line, 20,
			"< ", "<",
			"< ", "<",
			" <", "<",
			"<< ", "<<",
			" <<", "<<",
			"> ", ">",
			" >", ">",
			">> ", ">>",
			" >>", ">>",
			"./ ", "./");
	tmp = trim_many_spaces(tmp, "");
	(*curr_cmd)->cmd_line = tmp;
	return (0);
}

//1!
int	parse_input_output(t_cmd *curr_cmd)
{
	int		i;
	char	*cut;
	int		type;
	int		jump;

	type = 0;
	jump = 2;
	cut = NULL;
	glued(&curr_cmd);
	while (has_symbols(curr_cmd->cmd_line))
	{
		i = -1;
		while (curr_cmd->cmd_line[++i])
		{
			if (!symbol_here(&(curr_cmd->cmd_line[i]), &jump, &type))
				continue ;
			cut = get_symbol(curr_cmd, &(curr_cmd->cmd_line[i]), &jump);
			if (execute_symbol(curr_cmd, type, cut))
				return (1);
			curr_cmd->cmd_line = ft_str_replace(curr_cmd->cmd_line, cut, "");
			ft_free_ptr((void *) &cut);
			break ;
		}
	}
	return (0);
}
