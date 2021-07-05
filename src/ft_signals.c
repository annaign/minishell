/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:53:12 by rmanfred          #+#    #+#             */
/*   Updated: 2020/12/09 12:53:14 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ctrl-D - register EOF and exit program
** ctrl-C - interrupt signal sends SIGINT to the job running in the foreground
** ctrl-\ - SIGQUIT
*/

#include "minishell.h"

t_env	g_e;

void		ft_check_waitpid_status(int status)
{
	if (WIFEXITED(status))
		g_e.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			g_e.exit_status = 130;
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_printf("Quit: 3");
			g_e.exit_status = 131;
		}
		ft_printf("\n");
	}
}

static void	ft_ctrl_c_handler(int sig)
{
	if (sig)
	{
		g_e.exit_status = 130;
		write(0, "\n", 1);
		ft_prompt();
	}
}

static void	ft_ctrl_slash_handler(int sig)
{
	if (sig)
		ft_putstr_fd("\b\b  \b\b", 2);
}

void		ft_signals(int sig)
{
	if (sig == -1)
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR)
			ft_putstr_fd("Signal SIGINT error\n", 2);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			ft_putstr_fd("Signal SIGQUIT error\n", 2);
	}
	else if (sig == 0)
	{
		if (signal(SIGINT, SIG_DFL) == SIG_ERR)
			ft_putstr_fd("Signal SIGINT error\n", 2);
		if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			ft_putstr_fd("Signal SIGQUIT error\n", 2);
	}
	else if (sig == 1)
	{
		if (signal(SIGINT, ft_ctrl_c_handler) == SIG_ERR)
			ft_putstr_fd("Signal SIGINT error\n", 2);
		if (signal(SIGQUIT, ft_ctrl_slash_handler) == SIG_ERR)
			ft_putstr_fd("Signal SIGQUIT error\n", 2);
	}
}
