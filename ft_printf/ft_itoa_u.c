/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <rmanfred@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:40:51 by rmanfred          #+#    #+#             */
/*   Updated: 2020/07/20 17:58:46 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_digits_u(int dig, unsigned int n)
{
	while (n)
	{
		dig += 1;
		n /= 10;
	}
	return (dig);
}

char	*ft_get_mem_u(int dig, unsigned int n)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * (dig + 1))))
		return (NULL);
	str[dig] = '\0';
	if (n == 0)
		str[--dig] = 0 + '0';
	while (n > 0)
	{
		str[--dig] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_itoa_u(unsigned int n)
{
	int	dig;

	dig = 0;
	if (n == 0)
		dig = 1;
	else
		dig = ft_digits_u(dig, n);
	return (ft_get_mem_u(dig, n));
}
