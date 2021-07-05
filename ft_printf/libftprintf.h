/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanfred <rmanfred@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:00:36 by rmanfred          #+#    #+#             */
/*   Updated: 2020/07/22 18:15:19 by rmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct	s_arg
{
	int		minus;
	int		dot;
	int		zero;
	int		width;
	int		precision;
	int		temp;
	char	conversion;
}				t_arg;

typedef struct	s_padding
{
	int		after;
	int		before;
	int		zero;
}				t_padding;

int				ft_printf(const char *str, ...);
t_arg			ft_set_flags(void);
int				ft_check_flag(const char **str);
t_arg			ft_get_flag(const char **str, va_list ap, t_arg flag);
int				ft_conversion(va_list ap, t_arg flag);
int				ft_putchar(char c);
int				ft_put_d_i(int num, t_arg flag);
char			*ft_itoa(int n);
char			*ft_get_mem(int dig, int n, int n_flag);
int				ft_digits(int dig, int n, int n_flag);
int				ft_flag(int n);
t_padding		ft_set_flags_number(void);
t_arg			get_negative(t_arg flag);
t_padding		set_neg_minus(t_arg flag, t_padding padding);
t_padding		set_flags(char **to_fill, t_arg flag, t_padding padding);
t_padding		set_flags_ptr(char **to_fill, t_arg flag, t_padding padding);
int				ft_putstr_number(char *str, t_padding padding);
int				ft_strlen_l(const char *str);
int				ft_strlen_neg(const char *str);
char			*ft_strchr(const char *s, int c);
int				ft_put_u(unsigned int num, t_arg flag);
char			*ft_itoa_u(unsigned int n);
char			*ft_get_mem_u(int dig, unsigned int n);
int				ft_digits_u(int dig, unsigned int n);
int				ft_put_x(unsigned int num, t_arg flag);
char			*ft_itoa_x(unsigned int num, t_arg flag);
char			*ft_strjoin_x(char s1, char *s2);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa_x(unsigned int num, t_arg flag);
char			*ft_strdup(const char *s);
int				ft_put_c(unsigned char c, t_arg flag);
t_padding		set_flags_c(t_arg flag, t_padding padding);
int				ft_put_s(char *str, t_arg flag);
char			*ft_substr2(char const *s, int start, int len);
t_padding		set_flags_s(char **to_fill, t_arg flag, t_padding padding);
int				ft_putstr(char *str);
int				ft_put_ptr(void *ptr, t_arg flag);
char			*ft_itoa_p(void *p);
int				ft_isdigit(int c);
int				ft_put_percent(t_arg flag);
int				ft_ptr_null(t_arg flag);
int				padding_before(t_padding padding);
int				padding_after(t_padding padding);
int				padding_zero(t_padding padding);
int				ft_put_nothing(t_arg flag);
char			*check_s_null(t_arg flag);

#endif
