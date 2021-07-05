/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_external.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:57:09 by pshagwel          #+#    #+#             */
/*   Updated: 2020/11/30 17:57:10 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	g_e;

void		ft_parent_exit(char **arg, pid_t pid)
{
	int		status;

	g_e.pid = pid;
	status = 0;
	if ((waitpid(pid, &status, WUNTRACED)) == -1)
		msg_err(1, SH, arg[0], "waitpid error");
	ft_check_waitpid_status(status);
	ft_signals(1);
	g_e.pid = 0;
}

static void	ft_cmd_child(char **arg)
{
	char	*path;

	path = ft_get_path(arg[0]);
	execve(path, arg, g_e.env);
	msg_err(127, SH, arg[0], "command not found");
	ft_free_memory();
	exit(127);
}

void		ft_cmd_external(char **arg)
{
	pid_t	pid;

	g_e.exit_status = 0;
	ft_signals(-1);
	pid = fork();
	if (pid < 0)
		msg_err(1, SH, arg[0], "fork error");
	else if (pid == 0)
	{
		ft_signals(0);
		ft_cmd_child(arg);
	}
	else
		ft_parent_exit(arg, pid);
}
