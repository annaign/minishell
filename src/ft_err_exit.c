/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:59:01 by pshagwel          #+#    #+#             */
/*   Updated: 2020/11/22 16:59:02 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	g_e;

void	msg_err(int status, char *msg1, char *arg, char *msg2)
{
	g_e.exit_status = status;
	ft_putstr_fd(msg1, 2);
	if ((ft_strlen(arg)) > 0)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	else
		ft_putstr_fd("'' ", 2);
	ft_putstr_fd(msg2, 2);
	ft_putstr_fd("\n", 2);
}

void	msg_err2(int status, char *msg1, char *arg, char *msg2)
{
	g_e.exit_status = status;
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(msg2, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_err_exit(void)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	ft_free_memory();
	exit(1);
}

void	ft_main_arg_exit(char *arg)
{
	ft_printf("Run command without arguments: '%s'\n", arg);
	ft_free_memory();
	exit(0);
}
