/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:03:59 by woliveir          #+#    #+#             */
/*   Updated: 2022/07/09 12:52:55 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_minishell.h"

static int	ft_printf_arg(const char *frase, va_list ap);
static int	ft_pointer(void *ptr);

int	ft_printf(const char *frase, ...)
{
	va_list			ap;
	int				ret;
	unsigned int	i;

	i = 0;
	ret = 0;
	va_start(ap, frase);
	while (frase[i])
	{
		if (frase[i] == '%' && (!ft_strchr("cspdiuxX%", frase[i + 1]) || \
		!frase[i + 1]))
			i++;
		else if (frase[i] == '%' && ft_strchr("cspdiuxX%", frase[i + 1]))
		{
			ret += ft_printf_arg(&frase[i + 1], ap);
			i += 2;
		}
		else
			ret += ft_putchar(frase[i++]);
	}
	va_end(ap);
	return (ret);
}

static int	ft_printf_arg(const char *frase, va_list ap)
{
	if (*frase == '%')
		return (ft_putchar(*frase));
	else if (*frase == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (*frase == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (*frase == 'd' || *frase == 'i')
		return (ft_putnbr(va_arg(ap, int)));
	else if (*frase == 'u')
		return (ft_putnbr_u(va_arg(ap, unsigned int)));
	else if (*frase == 'X')
		return (ft_puthex(va_arg(ap, unsigned int), "0123456789ABCDEF", 16));
	else if (*frase == 'x')
		return (ft_puthex(va_arg(ap, unsigned int), "0123456789abcdef", 16));
	else if (*frase == 'p')
		return (ft_pointer(va_arg(ap, void *)));
	else
		return (0);
}

static int	ft_pointer(void *ptr)
{
	if (ptr)
	{
		return (ft_putstr("0x") + ft_putpointer(ptr, \
		"0123456789abcdef", 16));
	}
	else
		return (ft_putstr(STRNULL));
}
