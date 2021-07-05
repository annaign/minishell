/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_redicrect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:06:25 by pshagwel          #+#    #+#             */
/*   Updated: 2020/12/16 00:06:27 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

extern t_env	g_e;

static char	*ft_new_line(char *line, char *str)
{
	char	*new_line;
	int		len;
	int		i;
	int		cat;

	len = ft_strlen(line);
	cat = 0;
	i = -1;
	while (++i < len)
		if (str[i] == '\0')
			cat++;
	if (!(new_line = malloc(sizeof(char) * (len - cat + 1))))
		return (FALSE);
	i = -1;
	len = 0;
	while (line[++i] != '\0')
	{
		if (str[i] != '\0')
			new_line[len++] = line[i];
	}
	new_line[len] = '\0';
	return (new_line);
}

static int	ft_print_err(int err, char **str)
{
	if (err == 0)
		msg_err(2, SH, "", "syntax error near unexpected token `<'");
	else if (err == 1)
		msg_err(2, SH, "", "syntax error near unexpected token `>'");
	else if (err == 2)
		msg_err(2, SH, "", "syntax error near unexpected token `>>'");
	ft_free(str);
	ft_clear_command();
	return (FALSE);
}

static int	ft_create_f(char *file, char **str, t_cmd *cmd, int n)
{
	if (!file)
		return (ft_print_err(n, str));
	if (n == 0)
		ft_lstadd_back(&(cmd->f_0), ft_lstnew(file));
	else if (n == 1)
		ft_lstadd_back(&(cmd->f_1), ft_lstnew(file));
	else if (n == 2)
		ft_lstadd_back(&(cmd->f_2), ft_lstnew(file));
	if (n == 0)
		cmd->rdr_last = (cmd->rdr_last == -1) ? n : cmd->rdr_last;
	else
		cmd->rdr_last = n;
	return (TRUE);
}

static char	*ft_trim_new_line(char **line, char **str)
{
	char	*tmp;
	char	*new_line;

	tmp = ft_new_line(*line, *str);
	ft_free(str);
	if (!tmp)
		ft_err_exit();
	ft_free(line);
	new_line = ft_strtrim(tmp, " ");
	ft_free(&tmp);
	if (!new_line)
		ft_err_exit();
	return (new_line);
}

int			ft_parse_redicrect(char **line, t_cmd *cmd)
{
	char	*str;
	int		i;

	str = ft_strdup(*line);
	i = 0;
	while (line[0][i] != '\0')
	{
		if (ft_strchr("\\\"'", line[0][i]))
			ft_check_quotes(*line, &i);
		if ((line[0][i] == '>' && line[0][i + 1] == '>') &&
			!(ft_create_f(ft_filename(*line, str, &i), &str, cmd, 2)))
			return (FALSE);
		else if ((line[0][i] == '>') &&
			!(ft_create_f(ft_filename(*line, str, &i), &str, cmd, 1)))
			return (FALSE);
		else if ((line[0][i] == '<') &&
			!(ft_create_f(ft_filename(*line, str, &i), &str, cmd, 0)))
			return (FALSE);
		i++;
	}
	*line = ft_trim_new_line(line, &str);
	return (TRUE);
}
