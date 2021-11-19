#include "ft_printf.h"

int	is_flg(char **cur, t_mod *mod)
{
	char		*flg;
	short int	offt;

	flg = ft_strchr(FLAGS, **cur);
	if (flg)
	{
		offt = flg - FLAGS;
		((short int *)mod)[offt] = 1;
		*cur += 1;
		return (1);
	}
	return (0);
}

int	is_nonzero_digit(char **cur, t_mod *mod)
{
	int	res;

	while (**cur == '0')
		(*cur)++;
	if (**cur < '0' || **cur > '9')
		return (0);
	res = ft_atoi(*cur);
	if ((mod->precision != -1))
		mod->width = res;
	else
		mod->precision = res;
	mod->arg = &res;
	*cur += number_digits(mod);
	mod->arg = NULL;
	return (1);
}

int	is_point(char **cur, t_mod *mod)
{
	if (**cur != '.')
		return (0);
	mod->precision = -1;
	*cur += 1;
	return (1);
}

int	is_asterisk(char **cur, t_mod *mod, va_list ap)
{
	int		arg;

	if (**cur != '*')
		return (0);
	arg = va_arg(ap, int);
	if ((arg < 0) && (mod->precision != -1))
	{
		mod->minus = 1;
		mod->width = -arg;
	}
	else if ((arg < 0) && (mod->precision == -1))
		mod->precision = -2;
	else if ((arg >= 0) && (mod->precision != -1))
		mod->width = arg;
	else if ((arg >= 0) && (mod->precision == -1))
		mod->precision = arg;
	*cur += 1;
	return (1);
}
