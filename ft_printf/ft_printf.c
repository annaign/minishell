/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <rmanfred@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:18:08 by rmanfred          #+#    #+#             */
/*   Updated: 2020/07/22 18:52:01 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_arg	ft_set_flags(void)
{
	t_arg		flag;

	flag.minus = 0;
	flag.zero = 0;
	flag.dot = 0;
	flag.width = 0;
	flag.precision = 0;
	flag.temp = 0;
	return (flag);
}

int		ft_check_flag(const char **str)
{
	if (**str == 'd' || **str == 'i' || **str == 'u' || **str == 'c' ||
		**str == 's' || **str == 'p' || **str == 'x'
		|| **str == 'X' || **str == '%')
		return (1);
	return (0);
}

t_arg	ft_get_flag(const char **str, va_list ap, t_arg flag)
{
	(*str)++;
	while (**str && !ft_check_flag(str))
	{
		if (**str == '-')
			flag.minus = 1;
		else if ((**str == '0') && !flag.minus && !flag.dot && !flag.width)
			flag.zero = 1;
		else if (**str == '.')
			flag.dot = 1;
		else if (ft_isdigit(**str) && (flag.dot == 1))
			flag.precision = flag.precision * 10 + **str - '0';
		else if (ft_isdigit(**str) && !flag.dot)
			flag.width = flag.width * 10 + **str - '0';
		else if (**str == '*' && flag.dot)
			flag.precision = va_arg(ap, int);
		else if (**str == '*' && !flag.dot)
			flag.width = va_arg(ap, int);
		else
			break ;
		(*str)++;
	}
	flag.conversion = **str;
	return (flag);
}

int		ft_conversion(va_list ap, t_arg flag)
{
	if (flag.conversion == 'c')
		return (ft_put_c(va_arg(ap, int), flag));
	else if (flag.conversion == 's')
		return (ft_put_s(va_arg(ap, char *), flag));
	else if (flag.conversion == 'p')
		return (ft_put_ptr(va_arg(ap, void *), flag));
	else if (flag.conversion == 'd' || flag.conversion == 'i')
		return (ft_put_d_i(va_arg(ap, int), flag));
	else if (flag.conversion == 'u')
		return (ft_put_u(va_arg(ap, unsigned int), flag));
	else if (flag.conversion == 'x' || flag.conversion == 'X')
		return (ft_put_x(va_arg(ap, unsigned int), flag));
	else if (flag.conversion == '%')
		return (ft_put_percent(flag));
	else if (flag.conversion)
		return (ft_put_c(flag.conversion, flag));
	else
		return (ft_put_nothing(flag));
	return (0);
}

int		ft_printf(const char *str, ...)
{
	va_list		ap;
	int			count;
	int			check_count;

	va_start(ap, str);
	count = 0;
	check_count = 0;
	while (*str)
	{
		check_count = count;
		if (*str == '%')
			count += ft_conversion(ap, ft_get_flag(&str, ap, ft_set_flags()));
		else
			count += ft_putchar(*(str));
		if (count < check_count || !*str)
			break ;
		str++;
	}
	va_end(ap);
	return ((count < check_count) ? -1 : count);
}
