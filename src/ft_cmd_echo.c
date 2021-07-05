/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:35:14 by rmanfred          #+#    #+#             */
/*   Updated: 2020/11/23 11:35:16 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** bash command: echo [-neE] [arg …]
**    minishell: echo with option ’-n’
*/

#include "minishell.h"

t_env	g_e;

static int		ft_check_option_n(char *arg)
{
	int			i;

	i = 0;
	g_e.sign.f_init_n = 1;
	while (arg[i])
	{
		while (arg[i] == 32)
			i++;
		if (arg[i] == '-' && arg[i + 1] == 'n')
		{
			i++;
			while (arg[i] == 'n')
				i++;
			if (arg[i] != '\0')
				return (0);
			else
				return (1);
		}
		else
			return (0);
	}
	return (0);
}

void			ft_cmd_echo(char **arg)
{
	int			i;

	i = 1;
	g_e.exit_status = 0;
	g_e.sign.f_option_n = 0;
	while (arg[i] != NULL)
	{
		if ((ft_check_option_n(arg[i])))
			i++;
		else
			break ;
	}
	if (i > 1)
		g_e.sign.f_option_n = 1;
	while (arg[i] != NULL)
	{
		ft_printf("%s", arg[i]);
		if (arg[++i] != NULL)
			ft_printf(" ");
	}
	if (g_e.sign.f_option_n == 0)
		ft_printf("\n");
}
