/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 13:10:24 by sdalton           #+#    #+#             */
/*   Updated: 2021/07/07 22:11:46 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*conv_string(t_mod *mod, va_list ap)
{
	char	*str;
	char	t;

	str = NULL;
	t = mod->type;
	if (t == 'd' || t == 'i')
		str = int_print(mod, ap);
	else if (t == 's')
		str = str_print(mod, ap);
	else if (t == 'c')
		str = char_print(mod, ap);
	else if (t == 'x' || t == 'X' || t == 'u')
		str = unsigned_int_print(mod, ap);
	else if (t == 'p')
		str = pointer_print(mod, ap);
	return (str);
}

static void	add_str(t_str *str, char *cur_substr, short int ret)
{
	char	*tmp;

	if (!str->str)
		str->str = cur_substr;
	else
	{
		tmp = str->str;
		str->str = ft_calloc(str->ret + ret, sizeof(char));
		ft_memcpy((void *)str->str, (const void *)tmp, str->ret);
		ft_memcpy((void *)str->str + str->ret, (const void *)cur_substr, ret);
		free(tmp);
		free(cur_substr);
	}
	str->ret += ret;
}

static int	pr_str(t_str *str, t_mod *mod, va_list ap)
{
	char		*cur_substr;
	short int	ret;
	char		*verb;
	char		*conv;

	cur_substr = NULL;
	ret = 0;
	verb = str->verb;
	conv = str->conv;
	if (!conv)
		cur_substr = ft_strdup(verb);
	else if (conv - verb >= 0)
		cur_substr = ft_substr(verb, 0, conv - verb);
	else if (conv - verb < 0)
		cur_substr = conv_string(mod, ap);
	if (!cur_substr)
		return (0);
	if ((conv && conv - verb >= 0) || !conv)
		ret = ft_strlen(cur_substr);
	else if (conv && conv - verb < 0)
		ret = mod->cp_str_len;
	add_str(str, cur_substr, ret);
	return (str->str != NULL);
}

static void	get_string(t_str *str, const char *fmt, va_list ap)
{
	t_mod	*mod;

	str->str = NULL;
	str->verb = (char *)fmt;
	str->conv = ft_strchr(str->verb, '%');
	str->ret = 0;
	mod = mod_init();
	while (str->conv && pr_str(str, mod, ap))
	{
		str->verb = parser(str->conv, mod, ap);
		if (!pr_str(str, mod, ap))
			break ;
		str->conv = ft_strchr(str->verb, '%');
		mod_zero(mod);
	}
	pr_str(str, mod, ap);
	del_mod(mod);
	va_end(ap);
}

int	ft_printf(const char *fmt, ...)
{
	va_list		ap;
	t_str		*str;
	short int	ret;

	va_start(ap, fmt);
	str = (t_str *)malloc(sizeof(t_str) * 1);
	get_string(str, fmt, ap);
	ret = str->ret;
	va_end(ap);
	if (!str)
		return (-1);
	write(1, str->str, ret);
	free(str->str);
	free(str);
	return (ret);
}
