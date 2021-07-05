/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_d_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <rmanfred@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 14:13:42 by rmanfred          #+#    #+#             */
/*   Updated: 2020/07/21 18:00:27 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_padding	ft_set_flags_number(void)
{
	t_padding	padding;

	padding.before = 0;
	padding.zero = 0;
	padding.after = 0;
	return (padding);
}

t_arg		get_negative(t_arg flag)
{
	if (flag.width < 0)
	{
		flag.minus = 1;
		flag.width *= (-1);
	}
	return (flag);
}

t_padding	set_neg_minus(t_arg flag, t_padding padding)
{
	if (flag.minus)
	{
		padding.after = padding.before;
		padding.before = 0;
	}
	return (padding);
}

t_padding	set_flags(char **to_fill, t_arg flag, t_padding padding)
{
	flag = get_negative(flag);
	if (flag.zero && flag.width && !flag.minus && !(flag.dot
		&& flag.precision >= 0))
		padding.zero = flag.width - ft_strlen_l(*to_fill);
	else if (flag.precision >= flag.width)
	{
		flag.width = 0;
		if (flag.precision >= ft_strlen_l(*to_fill))
			padding.zero = flag.precision - ft_strlen_neg(*to_fill);
	}
	else if (flag.precision < flag.width)
	{
		if (flag.precision >= ft_strlen_l(*to_fill))
		{
			padding.before = flag.width - flag.precision;
			if (ft_strchr(*to_fill, '-'))
				padding.before--;
			padding.zero = flag.precision - ft_strlen_neg(*to_fill);
		}
		else
			padding.before = flag.width - ft_strlen_l(*to_fill);
		padding = set_neg_minus(flag, padding);
	}
	return (padding);
}

int			ft_put_d_i(int num, t_arg flag)
{
	int			count;
	char		*to_fill;
	t_padding	padding;
	char		*tmp;

	if (!(to_fill = ft_itoa(num)))
		return (-1);
	if (num == 0 && flag.precision == 0 && flag.dot == 1)
	{
		tmp = to_fill;
		if (!(to_fill = ft_strdup("")))
		{
			free(tmp);
			return (-1);
		}
		free(tmp);
	}
	padding = set_flags(&to_fill, flag, ft_set_flags_number());
	count = 0;
	count += padding_before(padding);
	count += ft_putstr_number(to_fill, padding);
	count += padding_after(padding);
	free(to_fill);
	return (count);
}
