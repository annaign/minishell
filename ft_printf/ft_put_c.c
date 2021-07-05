/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <rmanfred@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 22:25:28 by rmanfred          #+#    #+#             */
/*   Updated: 2020/07/21 18:09:51 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_padding		set_flags_c(t_arg flag, t_padding padding)
{
	if (flag.zero && flag.width && !flag.minus)
		padding.zero = flag.width - 1;
	else
	{
		if (!flag.minus)
			padding.before = flag.width - 1;
		if (flag.minus)
			padding.after = flag.width - 1;
		if (flag.width < 0)
		{
			flag.width *= -1;
			padding.after = flag.width - 1;
		}
	}
	return (padding);
}

int				ft_put_c(unsigned char c, t_arg flag)
{
	int			count;
	t_padding	padding;

	padding = set_flags_c(flag, ft_set_flags_number());
	count = 0;
	count += padding_before(padding);
	count += ft_putchar(c);
	count += padding_after(padding);
	return (count);
}

int				ft_put_percent(t_arg flag)
{
	int			count;
	t_padding	padding;

	padding = set_flags_c(flag, ft_set_flags_number());
	count = 0;
	count += padding_before(padding);
	count += ft_putstr_number("%", padding);
	count += padding_after(padding);
	return (count);
}

int				ft_put_nothing(t_arg flag)
{
	int			count;
	t_padding	padding;

	padding = set_flags_c(flag, ft_set_flags_number());
	count = 0;
	count += padding_before(padding);
	count += padding_zero(padding);
	count += padding_after(padding);
	return (count);
}
