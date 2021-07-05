/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:16:59 by pshagwel          #+#    #+#             */
/*   Updated: 2020/11/22 18:17:01 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** bash command: exit [n]
**    minishell: exit without any options
*/

#include "minishell.h"

extern t_env	g_e;

void	ft_read_exit(void)
{
	ft_free_memory();
	ft_printf("exit\n");
	exit(0);
}

void	ft_cmd_exit(char **arg, int print)
{
	int		i;
	int		err;

	err = (arg[1] == NULL) ? FALSE : TRUE;
	g_e.exit_status = 0;
	if (arg[1])
	{
		if (arg[2] != NULL)
		{
			g_e.exit_status = 1;
			ft_putstr_fd(SH"exit: too many arguments\n", 2);
			return ;
		}
		err = ((ft_strlen(arg[1])) == 0);
		i = -1;
		while (!err && arg[1][++i] != '\0')
			if (!(ft_isdigit(arg[1][i])))
				err = TRUE;
		g_e.exit_status = ft_atoi(arg[1]);
	}
	(print == 1) ? ft_printf("exit\n") : ft_printf("");
	if (err)
		msg_err(2, SH"exit: ", arg[1], "numeric argument required");
	ft_free_memory();
	exit(g_e.exit_status);
}
