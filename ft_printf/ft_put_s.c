/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <rmanfred@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:14:50 by rmanfred          #+#    #+#             */
/*   Updated: 2020/07/21 18:34:39 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_padding	set_flags_s(char **to_fill, t_arg flag, t_padding padding)
{
	if (flag.width > ft_strlen_l(*to_fill) && !flag.minus)
		padding.before = flag.width - ft_strlen_l(*to_fill);
	else if (flag.width > ft_strlen_l(*to_fill) && flag.minus)
		padding.after = flag.width - ft_strlen_l(*to_fill);
	else if (flag.width < 0)
	{
		flag.width *= -1;
		if (flag.width > ft_strlen_l(*to_fill))
			padding.after = flag.width - ft_strlen_l(*to_fill);
	}
	return (padding);
}

int			ft_putstr(char *str)
{
	int			index;

	index = 0;
	while (str[index] != '\0')
	{
		ft_putchar(str[index]);
		index++;
	}
	return (index);
}

char		*check_s_null(t_arg flag)
{
	char		*to_fill;
	char		*tmp;

	if (!(to_fill = ft_strdup("(null)")))
		return (NULL);
	if (flag.precision < ft_strlen_l(to_fill) && flag.dot
		&& !(flag.precision < 0))
	{
		tmp = to_fill;
		if (!(to_fill = ft_substr2(to_fill, 0, flag.precision)))
			return (NULL);
		free(tmp);
	}
	return (to_fill);
}

int			ft_put_s(char *str, t_arg flag)
{
	int			count;
	char		*to_fill;
	t_padding	padding;

	if (str == NULL)
	{
		if (!(to_fill = check_s_null(flag)))
			return (-1);
	}
	else if (flag.precision < ft_strlen_l(str) && flag.dot
			&& !(flag.precision < 0))
	{
		if (!(to_fill = ft_substr2(str, 0, flag.precision)))
			return (-1);
	}
	else if (!(to_fill = ft_strdup(str)))
		return (-1);
	padding = set_flags_s(&to_fill, flag, ft_set_flags_number());
	count = 0;
	count += padding_before(padding);
	count += ft_putstr(to_fill);
	count += padding_after(padding);
	free(to_fill);
	return (count);
}
