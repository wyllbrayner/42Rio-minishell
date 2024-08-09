/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/07/09 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>

# ifdef __linux__
#  define STRNULL "(nil)"
# else
#  define STRNULL "(null)"
# endif

int		ft_printf(const char *fornat, ...);
int		ft_putpointer(void *nbr, char *base, size_t t_base);
int		ft_puthex(unsigned int nbr, char *base, size_t t_base);
int		ft_putchar(char c);
int		ft_putnbr(int nbr);
int		ft_putstr(char *str);
int		ft_putnbr_u(unsigned int nbr);
int		ft_nbrlen(unsigned long n, size_t t_base);
char	*ft_nbr_to_str(unsigned long n, char *base, size_t t_base);

#endif
