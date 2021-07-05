/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 22:01:39 by pshagwel          #+#    #+#             */
/*   Updated: 2020/11/21 22:01:40 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

extern t_env	g_e;

static int		ft_count_quotes(char *str, char ch, int *i)
{
	char	ch_prev;

	ch_prev = str[*i];
	(*i)++;
	while (str[*i] != '\0')
	{
		if (str[*i] == '\\' && ch_prev == '\\')
		{
			(*i)++;
			ch_prev = '\0';
			continue ;
		}
		if (str[*i] == ch && (ch_prev != '\\' || ch == '\''))
			break ;
		ch_prev = str[*i];
		(*i)++;
	}
	if (str[*i] == '\0')
		return (FALSE);
	return (TRUE);
}

int				ft_check_quotes(char *s, int *i)
{
	if (s[*i] == '\\')
	{
		(*i)++;
		if (s[*i] == '\\' || s[*i] == '"' || s[*i] == '\'')
			(*i)++;
	}
	if ((s[*i] == '"' || s[*i] == '\'') && !(ft_count_quotes(s, s[*i], i)))
		return (FALSE);
	if (s[*i] == '\0')
		(*i)--;
	return (TRUE);
}

static int		ft_create_cmd_str(char *s, int *i, int *begin, char **str_cmd)
{
	int	tmp;

	tmp = *i + 1;
	while (s[tmp] != '\0' && s[tmp] == ' ')
		tmp++;
	if (s[*i + 1] == ';')
	{
		msg_err(2, SH, "", "syntax error near unexpected token `;;'");
		ft_clear_command();
		return (FALSE);
	}
	if ((*i == 0 && *i == *begin) || s[tmp] == ';')
	{
		msg_err(2, SH, "", "syntax error near unexpected token `;'");
		ft_clear_command();
		return (FALSE);
	}
	s[*i] = '\0';
	*str_cmd = ft_strtrim(&s[*begin], " ");
	*begin = *i + 1;
	return (TRUE);
}

static void		ft_parse_line(char *s, char sep)
{
	char		*str_cmd;
	int			begin;
	int			err;
	int			i;

	err = FALSE;
	str_cmd = NULL;
	begin = 0;
	i = -1;
	while (s[++i] != '\0')
	{
		if (!(ft_check_quotes(s, &i)) && (err = TRUE))
		{
			msg_err(2, SH, "", "not support multiline commands");
			ft_clear_command();
			break ;
		}
		if (s[i] == sep && (err = !ft_create_cmd_str(s, &i, &begin, &str_cmd)))
			break ;
		if (str_cmd && !(ft_parse_command(&str_cmd)))
			break ;
	}
	if (!err && begin < i)
		if ((str_cmd = ft_strtrim(&s[begin], " ")))
			ft_parse_command(&str_cmd);
}

void			ft_read_command(void)
{
	char	*tmp;
	int		ret;
	char	buf[1];

	tmp = NULL;
	ret = get_next_line(0, &tmp);
	if (ret == -1 || (ret == 0 && !tmp))
	{
		free(tmp);
		tmp = NULL;
		(ret == -1) ? ft_err_exit() : ft_read_exit();
	}
	while (ret == 0)
		ret = read(0, buf, 1);
	free(g_e.line);
	g_e.line = NULL;
	g_e.line = ft_strtrim(tmp, " ");
	free(tmp);
	tmp = NULL;
	ft_parse_line(g_e.line, ';');
}
