/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_sign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 18:10:45 by rmanfred          #+#    #+#             */
/*   Updated: 2020/12/02 18:10:47 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	g_e;

static	void	ft_slash_helper(char *tmp, char *ret, char *arg)
{
	int			i;

	i = 0;
	if (tmp != NULL)
		ret = ft_strjoin_free(tmp, ret);
	if (!ret)
		ft_err_exit();
	if (ret[0] == '\0')
		ret = ft_strjoin_c(ret, '\\', 1);
	if (!(g_e.sign.ret = ft_strjoin_free(g_e.sign.ret, ret)))
		ft_err_exit();
	if (g_e.sign.f_d_qoute != 1 && arg[i] != '\0')
		ft_parse_arg(&arg[++i]);
}

void			ft_back_slash(char *arg)
{
	int			i;
	char		*ret;
	char		*tmp;

	i = 1;
	tmp = NULL;
	if (arg[0] == '$')
	{
		tmp = ft_strdup("$");
		i = 2;
	}
	if (arg[i] == '\\')
		ret = ft_strdup("\\");
	else if (arg[i] == '\"' && g_e.sign.f_d_qoute == 1)
		ret = ft_strdup("\"");
	else
	{
		if (arg[i] != '\0' && arg[i] != '"'
			&& (g_e.sign.f_d_qoute == 1 || (i > 1 && arg[i - 2] == '"')))
			ret = ft_strdup("\\");
		else
			ret = ft_strdup("");
		ret = ft_strjoin_c(ret, arg[i], 1);
	}
	ft_slash_helper(tmp, ret, &arg[i]);
}

void			ft_single_quote(char *arg)
{
	int			i;

	i = 1;
	while (arg[i] != '\'' && arg[i] != '\0')
	{
		if (!(g_e.sign.ret = ft_strjoin_c(g_e.sign.ret, arg[i], 1)))
			ft_err_exit();
		i++;
	}
	ft_parse_arg(&arg[++i]);
}

void			ft_double_quote(char *arg)
{
	int			i;

	i = 1;
	while (arg[i] != '\"' && arg[i] != '\0')
	{
		if (arg[i] == '$' && arg[i + 1] != '\"')
		{
			g_e.sign.f_d_qoute = 1;
			if (arg[i + 1] != '$' && arg[i + 1] != '?')
				g_e.sign.num = 0;
			ft_parse_dollar(&arg[i]);
			i += (g_e.sign.num + 1);
			g_e.sign.num = 1;
		}
		else if (arg[i] == '\\')
		{
			g_e.sign.f_d_qoute = 1;
			ft_back_slash(&arg[i]);
			i += 2;
		}
		else if (!(g_e.sign.ret = ft_strjoin_c(g_e.sign.ret, arg[i++], 1)))
			ft_err_exit();
	}
	g_e.sign.f_d_qoute = 0;
	ft_parse_arg(&arg[++i]);
}
