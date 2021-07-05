/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <rmanfred@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:11:27 by rmanfred          #+#    #+#             */
/*   Updated: 2020/07/15 16:38:37 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char			*ft_itoa_x(unsigned int num, t_arg flag)
{
	char	*result;
	char	*tmp;
	char	hex;

	if (!(result = ft_strdup("")))
		return (NULL);
	while (num != 0)
	{
		if (num % 16 < 10)
			hex = num % 16 + 48;
		else if (flag.conversion == 'X')
			hex = num % 16 + 55;
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
