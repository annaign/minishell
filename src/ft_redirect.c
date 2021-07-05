/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 00:11:46 by pshagwel          #+#    #+#             */
/*   Updated: 2020/12/05 00:11:49 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	g_e;

/*
** fd_old:
** 0, 1: close fd_old and open a file with the same fd = fd_old
** -1  : open and close all files
** -2  : open a file with a new fd
*/

int			ft_open_fd(t_list *lst, int flags, char mode, int fd_old)
{
	int		fd;
	char	*file;

	fd = -1;
	while (lst && lst->next)
	{
		file = (char *)lst->content;
		fd = (mode == 'r') ? open(file, flags) : open(file, flags, 0666);
		if (fd == -1)
		{
			msg_err(1, SH, file, strerror(errno));
			return (fd);
		}
		lst = lst->next;
		close(fd);
	}
	if (fd_old >= 0 || fd_old == -2)
		close(fd_old);
	file = (char *)lst->content;
	fd = (mode == 'r') ? open(file, flags) : open(file, flags, 0666);
	if (fd == -1)
		msg_err(1, SH, file, strerror(errno));
	return (fd);
}

int			ft_open_fd_select(t_cmd *cmd, int fd_old)
{
	int		fd;

	if (cmd->rdr_last == 1)
	{
		if (cmd->f_2)
		{
			fd = ft_open_fd(cmd->f_2, O_RDWR | O_CREAT | O_APPEND, 'a', -1);
			if (fd == -1)
				return (fd);
		}
		if (cmd->f_1)
			fd = ft_open_fd(cmd->f_1, O_RDWR | O_CREAT | O_TRUNC, 'w', fd_old);
	}
	else
	{
		if (cmd->f_1)
		{
			fd = ft_open_fd(cmd->f_1, O_RDWR | O_CREAT | O_TRUNC, 'w', -1);
			if (fd == -1)
				return (fd);
		}
		if (cmd->f_2)
			fd = ft_open_fd(cmd->f_2, O_RDWR | O_CREAT | O_APPEND, 'a', fd_old);
	}
	return (fd);
}

static void	ft_clode_fds(int fd0, int fd1)
{
	if (fd0 != -1)
		close(fd0);
	if (fd1 != -1)
		close(fd1);
}

static void	ft_redirect_child(t_cmd *cmd)
{
	int	fd0;
	int	fd1;

	fd0 = -1;
	fd1 = -1;
	ft_signals(0);
	if (cmd->f_0)
		if ((fd0 = ft_open_fd(cmd->f_0, O_RDONLY, 'r', 0)) == -1)
			exit(1);
	if (cmd->rdr_last > 0)
		if ((fd1 = ft_open_fd_select(cmd, 1)) == -1)
		{
			ft_free_memory();
			exit(1);
		}
	if (!(ft_builtin_function(cmd->cmd)))
	{
		execve((ft_get_path(cmd->cmd[0])), cmd->cmd, g_e.env);
		ft_clode_fds(fd0, fd1);
		msg_err(127, SH, cmd->cmd[0], "command not found");
		ft_free_memory();
		exit(127);
	}
	ft_clode_fds(fd0, fd1);
}

void		ft_run_redirect(t_cmd *cmd)
{
	pid_t	pid;

	g_e.exit_status = 0;
	ft_transform_cmd(cmd);
	ft_signals(-1);
	pid = fork();
	if (pid < 0)
		msg_err(1, SH, cmd->cmd[0], "fork error");
	else if (pid == 0)
		ft_redirect_child(cmd);
	else
		ft_parent_exit(cmd->cmd, pid);
}
