/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:32:43 by pshagwel          #+#    #+#             */
/*   Updated: 2020/11/22 19:32:44 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** bash command: export [-fn] [-p] [name[=value]]
**    minishell: export without any options
*/

#include "minishell.h"

extern t_env	g_e;

static void	ft_sort_env(char ***env)
{
	int		len;
	int		i;
	int		j;
	char	*tmp;

	len = 0;
	while (env[0][len])
		len++;
	if (len < 2)
		return ;
	i = -1;
	while (++i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(env[0][i], env[0][j]) > 0)
			{
				tmp = env[0][i];
				env[0][i] = env[0][j];
				env[0][j] = tmp;
			}
			j++;
		}
	}
}

static void	ft_export_print(char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i] != NULL)
	{
		if (env[i][0] == '_')
			continue;
		ft_printf("declare -x ");
		j = -1;
		while (env[i][++j] != '=')
			write(1, &(env[i][j]), 1);
		ft_printf("=\"%s\"\n", env[i] + j + 1);
	}
}

static int	ft_export_parse_var(char *arg, char **var, size_t len)
{
	size_t	i;

	i = -1;
	while (arg[++i] != '\0')
		if (arg[i] == '=')
			break ;
	arg[i] = '\0';
	if (!(ft_check_env_var(arg)))
		return (FALSE);
	if (i < len)
		arg[i] = '=';
	*var = ft_strdup(arg);
	return (TRUE);
}

static int	ft_export_var(char *arg)
{
	int		i;
	char	*var;
	size_t	len;

	len = ft_strlen(arg);
	if (!(ft_export_parse_var(arg, &var, len)))
		return (FALSE);
	if (!var)
		ft_err_exit();
	i = ft_env_search_var(arg);
	if (i != -1)
	{
		free(g_e.env[i]);
		g_e.env[i] = var;
	}
	else if (ft_strchr(var, '='))
		ft_env_add_var(var);
	return (TRUE);
}

void		ft_cmd_export(char **arg)
{
	char	**env;
	int		i;

	g_e.exit_status = 0;
	if (!arg[1])
	{
		if (!g_e.env)
			return ;
		env = NULL;
		ft_copy_env(&env, g_e.env);
		ft_sort_env(&env);
		ft_export_print(env);
		ft_free_split_arr(env);
		return ;
	}
	i = 0;
	while (arg[++i] != NULL)
	{
		if ((ft_strlen(arg[i])) == '\0' || arg[i][0] == '=' ||
			!(ft_export_var(arg[i])))
			msg_err2(1, SH"export", arg[i], "not a valid identifier");
	}
}
