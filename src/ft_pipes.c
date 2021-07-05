/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:51:17 by rmanfred          #+#    #+#             */
/*   Updated: 2020/12/04 12:51:18 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	g_e;

void		ft_read_f(t_cmd *cmd)
{
	if (cmd->f_0)
	{
		if ((cmd->fdin = ft_open_fd(cmd->f_0, O_RDONLY, 'r', -2)) == -1)
		{
			ft_free_memory();
			exit(1);
		}
	}
	if (cmd->rdr_last > 0)
	{
		if ((cmd->fdout = ft_open_fd_select(cmd, -2)) == -1)
		{
			close(cmd->fdin);
			ft_free_memory();
			exit(1);
		}
	}
}

static void	ft_err_pipe(t_cmd *cmd[], int i)
{
	char	*err_prev;

	err_prev = NULL;
	if (cmd[i]->pipe)
	{
		ft_dup2(cmd[i]->err_pipe[1], 2, "fd 2 error");
	}
	if (i > 0)
	{
		if (!(ft_read_fd(cmd[i - 1]->err_pipe[0], &err_prev)))
			ft_err_exit();
		ft_putstr_fd(err_prev, 2);
		free(err_prev);
		err_prev = NULL;
		close(cmd[i - 1]->err_pipe[0]);
	}
}

static void	ft_pipes_child(t_cmd *cmd[], int i)
{
	if (cmd[i]->pipe)
	{
		if (cmd[i]->fdout != -1)
			ft_dup2(cmd[i]->fdout, cmd[i]->fdpipe[1], cmd[i]->cmd[0]);
		ft_dup2(cmd[i]->fdpipe[1], 1, cmd[i]->cmd[0]);
	}
	else
	{
		if (cmd[i]->fdout != -1)
			ft_dup2(cmd[i]->fdout, 1, cmd[i]->cmd[0]);
	}
	if (cmd[i]->fdin != -1)
		(i) ? ft_dup2(cmd[i]->fdin, cmd[i - 1]->fdpipe[0], cmd[i]->cmd[0]) :
			ft_dup2(cmd[i]->fdin, 0, cmd[i]->cmd[0]);
	if (i > 0)
		ft_dup2(cmd[i - 1]->fdpipe[0], 0, cmd[i]->cmd[0]);
	ft_err_pipe(cmd, i);
	if (!ft_builtin_function(cmd[i]->cmd))
	{
		execve(ft_get_path(cmd[i]->cmd[0]), cmd[i]->cmd, g_e.env);
		msg_err(127, SH, cmd[i]->cmd[0], "command not found");
		ft_free_memory();
		exit(127);
	}
}

static void	ft_close(t_cmd *cmd[], int i)
{
	if (cmd[i]->pipe)
	{
		close(cmd[i]->fdpipe[1]);
		close(cmd[i]->err_pipe[1]);
	}
	if (i > 0)
	{
		close(cmd[i - 1]->fdpipe[0]);
		close(cmd[i - 1]->err_pipe[0]);
	}
}

void		ft_run_pipe(t_cmd *cmd[])
{
	pid_t		pid;
	int			i;

	i = -1;
	while (cmd[++i] != NULL)
	{
		ft_transform_cmd(cmd[i]);
		if (cmd[i]->pipe && pipe(cmd[i]->fdpipe) != 0)
			ft_err_exit();
		if (cmd[i]->pipe && pipe(cmd[i]->err_pipe) != 0)
			ft_err_exit();
		pid = fork();
		if (pid < 0)
			msg_err(1, SH, "", strerror(errno));
		else if (pid == 0)
		{
			ft_read_f(cmd[i]);
			ft_pipes_child(cmd, i);
		}
		ft_close(cmd, i);
	}
	ft_parent_exit(cmd[--i]->cmd, pid);
}
