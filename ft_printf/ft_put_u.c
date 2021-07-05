/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <rmanfred@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:46:42 by rmanfred          #+#    #+#             */
/*   Updated: 2020/07/21 17:54:41 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_put_u(unsigned int num, t_arg flag)
{
	int			count;
	char		*to_fill;
	t_padding	padding;
	char		*tmp;

	if (!(to_fill = ft_itoa_u(num)))
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
