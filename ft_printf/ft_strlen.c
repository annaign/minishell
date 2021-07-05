/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <rmanfred@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 16:35:46 by rmanfred          #+#    #+#             */
/*   Updated: 2020/07/15 15:29:46 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_strlen_l(const char *str)
{
	int		index;

	index = 0;
	while (str[index] != '\0')
		index++;
	return (index);
}

int	ft_strlen_neg(const char *str)
{
	int		index;
	int		count;

	index = 0;
	count = 0;
	if (str[index] == '-')
		index++;
	while (str[index++] != '\0')
		count++;
	return (count);
}
