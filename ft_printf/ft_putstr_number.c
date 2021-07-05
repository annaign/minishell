/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:47:26 by rmanfred          #+#    #+#             */
/*   Updated: 2020/07/21 18:01:32 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	padding_before(t_padding padding)
{
	int	count;

	count = 0;
	while (padding.before > 0)
	{
		ft_putchar(' ');
		count++;
		padding.before--;
	}
	return (count);
}

int	padding_after(t_padding padding)
{
	int	count;

	count = 0;
	while (padding.after > 0)
	{
		ft_putchar(' ');
		count++;
		padding.after--;
	}
	return (count);
}

int	padding_zero(t_padding padding)
{
	int	count;

	count = 0;
	while (padding.zero > 0)
	{
		ft_putchar('0');
		count++;
		padding.zero--;
	}
	return (count);
}

int	ft_putstr_number(char *str, t_padding padding)
{
	int		index;
	int		count;

	index = 0;
	count = 0;
	if (str[index] == '-')
	{
		ft_putchar('-');
		count++;
		index++;
	}
	while (padding.zero > 0)
	{
		ft_putchar('0');
		count++;
		padding.zero--;
	}
	while (str[index] != '\0')
	{
		ft_putchar(str[index]);
		index++;
		count++;
	}
	return (count);
}
