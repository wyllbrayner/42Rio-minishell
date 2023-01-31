/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_to_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 03:31:12 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 06:25:23 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_to_fd(int fd, const char *format, ...)
{
	char	*fmt;
	va_list	vl;
	int		len;

	va_start(vl, format);
	fmt = prepare_to_translation (format, &vl);
	va_end(vl);
	len = ft_putstr_fd (fmt, fd);
	ft_free_ptr ((void *) &fmt);
	return (len);
}

int	ft_pf_error(const char *format, ...)
{
	char	*fmt;
	va_list	vl;
	int		len;

	va_start(vl, format);
	fmt = prepare_to_translation (format, &vl);
	va_end(vl);
	len = ft_putstr_fd (fmt, 2);
	ft_free_ptr ((void *) &fmt);
	return (len);
}
