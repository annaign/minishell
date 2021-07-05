/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 12:47:55 by pshagwel          #+#    #+#             */
/*   Updated: 2020/05/16 12:47:57 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_len(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
	{
		n /= -10;
		len += 2;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_itoa_len(n);
	str = malloc(sizeof(char) * (len + 1));
	if (str)
	{
		str[len--] = '\0';
		if (n == 0)
			str[0] = '0';
		if (n < 0)
		{
			str[0] = '-';
			str[len--] = -1 * (n % 10) + '0';
			n /= -10;
		}
		while (n > 0 && len >= 0)
		{
			str[len--] = n % 10 + '0';
			n /= 10;
		}
	}
	return (str);
}
