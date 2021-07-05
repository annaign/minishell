/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 18:26:46 by pshagwel          #+#    #+#             */
/*   Updated: 2020/05/22 18:26:47 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atof_space(const char *str)
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

double		ft_atof(const char *str)
{
	int		i;
	int		dot;
	double	sign;
	double	nb;

	i = ft_atof_space(str);
	sign = str[i] == '-' ? -1.0 : 1.0;
	i += (str[i] == '+' || str[i] == '-') ? 1 : 0;
	nb = 0;
	dot = 0;
	while (str[i] != '\0' && dot < 2)
	{
		if (str[i] == '.' && (++dot))
		{
			i++;
			continue;
		}
		else if (!ft_isdigit(str[i]))
			break ;
		if (dot == 1)
			sign /= 10.0;
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * sign);
}
