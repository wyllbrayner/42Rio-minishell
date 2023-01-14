/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rblondia <rblondia@student.42-lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:04:49 by rblondia          #+#    #+#             */
/*   Updated: 2022/01/29 16:57:17 by rblondia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum s_prompt_mode {
	NORMAL,
	QUOTE,
	D_QUOTE,
	DELIMIT,
}		t_prompt_mode;

typedef enum s_redirection {
	INPUT,
	OUTPUT,
	DELIMITER,
	APPENDER,
	NO
}	t_redirection;

typedef enum s_quote {
	DOUBLE,
	SIMPLE,
	NONE
}	t_quote;

typedef enum s_token {
	AMPERSAND,
	PIPE,
	AND,
	OR,
	REDIRECTION,
	LITERAL,
	SEMI_COLON,
}	t_token;

#endif