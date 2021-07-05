/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:33:23 by rmanfred          #+#    #+#             */
/*   Updated: 2020/12/02 16:33:25 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	g_e;

static	void	ft_parse_simple(char *arg)
{
	int			i;

	i = 0;
	while (arg[i] != '\'' && arg[i] != '\"' && arg[i] != '$'
			&& arg[i] != '\\' && arg[i] && arg[i] != 32)
	{
		if (!(g_e.sign.ret = ft_strjoin_c(g_e.sign.ret, arg[i], 1)))
			ft_err_exit();
		i++;
	}
	ft_parse_arg(&arg[i]);
}

static	void	ft_check_list_env(char *tmp)
{
	int			j;
	char		*ret;

	j = 0;
	while (g_e.env[j])
	{
		if ((strncmp(g_e.env[j], tmp, ft_strlen(tmp))) == 0
			&& g_e.env[j][ft_strlen(tmp)] == '=')
		{
			if (!(ret = ft_strdup(&g_e.env[j][ft_strlen(tmp) + 1])))
				ft_err_exit();
			if (!(g_e.sign.ret = ft_strjoin_free(g_e.sign.ret, ret)))
				ft_err_exit();
			break ;
		}
		j++;
	}
}

void			ft_parse_dollar(char *ar)
{
	int			i;
	char		*tmp;

	i = 1;
	if (!ft_isalnum(ar[i]) && ar[i] != '\\' && ar[i] != '\'' && ar[i] != '\"')
		ft_parse_tool(&ar[i]);
	else if (ar[i] == '\\')
		ft_back_slash(ar);
	else
	{
		while (ft_isalnum(ar[i]) || ar[i] == '_')
			i++;
		if (!(tmp = ft_substr(ar, 1, i - 1)))
			ft_err_exit();
		ft_check_list_env(tmp);
		g_e.sign.num = ft_strlen(tmp);
		free(tmp);
		tmp = NULL;
		if (g_e.sign.f_d_qoute != 1)
		{
			ft_parse_arg(&ar[i]);
			g_e.sign.num = 0;
		}
	}
}

void			ft_parse_arg(char *arg)
{
	int			i;

	i = 0;
	if (arg[i] == 32 && g_e.sign.f_space == 1)
		g_e.sign.ret = ft_strjoin_c(g_e.sign.ret, 32, 1);
	g_e.sign.f_space = 1;
	while (arg[i] == 32)
		i++;
	if (arg[i] != '\'' && arg[i] != '\"' && arg[i] != '$'
		&& arg[i] != '\\' && arg[i] != '\0')
		ft_parse_simple(&arg[i]);
	else if (arg[i] == '$')
		ft_parse_dollar(&arg[i]);
	else if (arg[i] == '\'')
		ft_single_quote(&arg[i]);
	else if (arg[i] == '\\')
		ft_back_slash(&arg[i]);
	else if (arg[i] == '\"')
		ft_double_quote(&arg[i]);
}

char			*ft_parse_str(char *arg)
{
	char		*ret;

	ft_init_parse();
	ft_parse_arg(arg);
	if (!(ret = ft_strdup(g_e.sign.ret)))
		ft_err_exit();
	free(g_e.sign.ret);
	g_e.sign.ret = NULL;
	return (ret);
}
