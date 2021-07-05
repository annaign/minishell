/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <rmanfred@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:44:44 by rmanfred          #+#    #+#             */
/*   Updated: 2020/07/20 17:58:03 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_flag(int n)
{
	int	n_flag;

	n_flag = 0;
	if (n < 0)
		n_flag = 1;
	return (n_flag);
}

int		ft_digits(int dig, int n, int n_flag)
{
	while (n > 0)
	{
		dig += 1;
		n /= 10;
	}
	if (n_flag == 1)
		dig += 1;
	return (dig);
}

char	*ft_get_mem(int dig, int n, int n_flag)
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
	if (n_flag > 0)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int	dig;
	int	n_flag;

	dig = 0;
	n_flag = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	n_flag = ft_flag(n);
	if (n < 0)
		n *= -1;
	if (n == 0)
		dig = 1;
	else
		dig = ft_digits(dig, n, n_flag);
	return (ft_get_mem(dig, n, n_flag));
}
