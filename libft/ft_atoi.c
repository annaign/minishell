/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 18:26:46 by pshagwel          #+#    #+#             */
/*   Updated: 2020/05/22 18:26:47 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atoi_space(const char *str)
{
	char	*spaces;
	int		i;
	int		i_return;
	int		stop_loop;
	int		f_space;

	spaces = " \n\t\r\v\f";
	i_return = 0;
	f_space = 0;
	stop_loop = 0;
	while (stop_loop != 1 && str[i_return] != '\0')
	{
		i = 0;
		while (spaces[i] != '\0')
		{
			if (str[i_return] == spaces[i])
				f_space++;
			i++;
		}
		i_return++;
		if (f_space != i_return)
			stop_loop = 1;
	}
	return (f_space);
}

static int	ft_atoi_sign(char ch)
{
	if (ch == '+')
		return (1);
	if (ch == '-')
		return (-1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int stop_loop;
	int index;
	int minus;
	int number;

	stop_loop = 0;
	index = ft_atoi_space(str);
	minus = ft_atoi_sign(str[index]);
	if (minus != 0)
		index++;
	number = 0;
	while (stop_loop != 1 && str[index] != '\0')
	{
		if (str[index] < '0' || str[index] > '9')
			stop_loop = 1;
		else
		{
			if (minus == -1)
				number = number * 10 - (str[index] - 48);
			else
				number = number * 10 + (str[index] - 48);
		}
		index++;
	}
	return (number);
}
