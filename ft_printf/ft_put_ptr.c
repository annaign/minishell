/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <rmanfred@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:18:12 by rmanfred          #+#    #+#             */
/*   Updated: 2020/07/21 18:39:34 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char			*ft_itoa_p(void *p)
{
	char				*result;
	char				*tmp;
	char				hex;
	unsigned long int	num;

	num = (unsigned long int)p;
	if (!(result = ft_strdup("")))
		return (NULL);
	while (num != 0)
	{
		if (num % 16 < 10)
			hex = num % 16 + 48;
		else
			hex = num % 16 + 55 + 32;
		tmp = result;
		if (!(result = ft_strjoin_x(hex, result)))
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
		num /= 16;
	}
	return (result);
}

t_padding		set_flags_ptr(char **to_fill, t_arg flag, t_padding padding)
{
	flag = get_negative(flag);
	if (flag.zero && flag.width && !flag.minus && !flag.dot)
		padding.zero = flag.width - ft_strlen_l(*to_fill) - 2;
	else if (flag.precision >= flag.width)
	{
		flag.width = 0;
		if (flag.precision > ft_strlen_l(*to_fill))
			padding.zero = flag.precision - ft_strlen_neg(*to_fill);
	}
	else if (flag.precision < flag.width)
	{
		if (flag.precision > ft_strlen_l(*to_fill))
		{
			padding.before = flag.width - flag.precision - 2;
			padding.zero = flag.precision - ft_strlen_l(*to_fill);
		}
		else
			padding.before = flag.width - ft_strlen_l(*to_fill) - 2;
		padding = set_neg_minus(flag, padding);
	}
	return (padding);
}

int				ft_ptr_null(t_arg flag)
{
	int					count;
	char				*to_fill;
	t_padding			padding;

	count = 0;
	if (flag.dot && !(to_fill = ft_strdup("0x")))
		return (-1);
	else if (!flag.dot && !(to_fill = ft_strdup("0x0")))
		return (-1);
	padding = ft_set_flags_number();
	if (flag.width > ft_strlen_l(to_fill) && !flag.minus)
		padding.before = flag.width - ft_strlen_l(to_fill);
	else if (flag.minus || flag.width < 0)
	{
		if (flag.width < 0)
			flag.width *= -1;
		padding.after = flag.width - ft_strlen_l(to_fill);
	}
	if (flag.precision)
		padding.zero = flag.precision;
	count += padding_before(padding);
	count += ft_putstr_number(to_fill, padding);
	count += padding_after(padding);
	free(to_fill);
	return (count);
}

int				ft_put_ptr(void *ptr, t_arg flag)
{
	int				count;
	char			*to_fill;
	t_padding		padding;

	if (ptr == NULL || ptr == 0)
		return (ft_ptr_null(flag));
	if (!(to_fill = ft_itoa_p(ptr)))
		return (-1);
	padding = set_flags_ptr(&to_fill, flag, ft_set_flags_number());
	count = 0;
	count += padding_before(padding);
	count += ft_putstr("0x");
	count += ft_putstr_number(to_fill, padding);
	count += padding_after(padding);
	free(to_fill);
	return (count);
}
