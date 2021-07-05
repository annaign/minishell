/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:51:17 by rmanfred          #+#    #+#             */
/*   Updated: 2020/12/04 12:51:18 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	g_e;

static	char	*to_join(char *path, char *cmd)
{
	char		*res;
	char		*tmp;

	res = ft_strjoin_c(path, '/', 0);
	if (!res)
		ft_err_exit();
	tmp = res;
	res = ft_strjoin(res, cmd);
	if (!res)
		ft_err_exit();
	free(tmp);
	tmp = NULL;
	return (res);
}

static	char	*ft_search_in_path(char *cmd, int err, struct stat buf)
{
	int			i;
	char		*env_path;
	char		**paths;
	char		*res;

	i = -1;
	env_path = ft_get_env("PATH");
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	free(env_path);
	env_path = NULL;
	while (paths[++i])
	{
		res = to_join(paths[i], cmd);
		if (!(err = stat(res, &buf)))
		{
			ft_free_split_arr(paths);
			return (res);
		}
		free(res);
		res = NULL;
	}
	ft_free_split_arr(paths);
	return (res);
}

char			*ft_get_path(char *cmd)
{
	struct stat	buf;
	int			err;
	char		*res;

	err = FALSE;
	res = cmd;
	if (cmd[0] == '/' && !(err = stat(cmd, &buf)))
		return (res);
	else if (cmd[0] == '.')
	{
		err = stat(cmd, &buf);
		if (!err)
			return (cmd);
		if (err)
			ft_printf("%s\n", strerror(errno));
	}
	else if (res[0] != '\0')
	{
		res = ft_search_in_path(cmd, err, buf);
		if (res == NULL)
			res = cmd;
	}
	return (res);
}
