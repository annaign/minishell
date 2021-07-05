/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <rmanfred@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:32:14 by rmanfred          #+#    #+#             */
/*   Updated: 2020/07/21 17:54:14 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char		*ft_strjoin_x(char s1, char *s2)
{
	char		*str;
	int			i;
	int			j;

	i = 0;
	j = 1;
	if (!s1 && !s2)
		return (NULL);
	if (!(str = malloc(sizeof(char) * (ft_strlen_l(s2) + 2))))
		return (NULL);
	if (s1)
		str[0] = s1;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

int			ft_put_x(unsigned int num, t_arg flag)
{
	int			count;
	char		*to_fill;
	t_padding	padding;

	if (num == 0 && !(flag.precision == 0 && flag.dot))
	{
		to_fill = ft_strdup("0");
		if (!to_fill)
			return (-1);
	}
	else if (!(to_fill = ft_itoa_x(num, flag)))
		return (-1);
	padding = set_flags(&to_fill, flag, ft_set_flags_number());
	count = 0;
	count += padding_before(padding);
	count += ft_putstr_number(to_fill, padding);
	count += padding_after(padding);
	free(to_fill);
	return (count);
}
