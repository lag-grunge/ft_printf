#include "ft_printf.h"

char	*int_print(t_mod *mod, va_list ap)
{
	int		arg;
	char	*str;

	arg = va_arg(ap, int);
	mod->arg = (void *)&arg;
	mod->zero = mod->zero && mod->precision == -2 && !mod->minus;
	mod->space = mod->space && !mod->plus;
	mod->sign = arg < 0 || mod->plus || mod->space;
	if (mod->precision > 0)
		mod->precision = mod->precision + mod->sign;
	mod->arg_len = number_digits(mod);
	mod->str_len = max(3, mod->precision, mod->arg_len, mod->width);
	mod->cp_str_len = mod->str_len;
	str = (char *)ft_calloc(mod->str_len + 1, sizeof(char));
	set_suffix(str, mod);
	if (!mod->precision && !arg)
		;
	else
		set_digits(str, mod);
	set_prefix(str, mod);
	return (str);
}

char	*char_print(t_mod *mod, va_list ap)
{
	char	arg;
	char	*str;
	char	*tmp;

	tmp = NULL;
	if (!mod->arg)
	{
		arg = va_arg(ap, int);
		mod->arg = (void *)&arg;
	}
	else
		tmp = mod->arg;
	mod->arg_len = 1;
	mod->str_len = max(2, 1, mod->width);
	mod->cp_str_len = mod->str_len;
	str = (char *)ft_calloc(mod->str_len + 1, sizeof(char));
	set_suffix(str, mod);
	set_string(str, mod);
	set_prefix(str, mod);
	if (tmp)
		free(tmp);
	return (str);
}

char	*str_print(t_mod *mod, va_list ap)
{
	char	*str;
	char	*tmp;

	tmp = NULL;
	mod->arg = (void *)va_arg(ap, char *);
	if (!mod->arg)
		mod->arg = "(null)";
	mod->arg_len = ft_strlen(mod->arg);
	if (mod->precision != -2)
	{
		mod->arg_len = min(2, mod->arg_len, mod->precision);
		mod->precision = mod->arg_len;
	}
	mod->str_len = max(2, mod->arg_len, mod->width);
	mod->cp_str_len = mod->str_len;
	str = (char *)ft_calloc(mod->str_len + 1, sizeof(char));
	set_suffix(str, mod);
	set_string(str, mod);
	set_prefix(str, mod);
	return (str);
}

char	*pointer_print(t_mod *mod, va_list ap)
{
	char	*str;
	void	*arg;

	arg = va_arg(ap, void *);
	mod->arg = &arg;
	mod->zero = mod->zero && mod->precision == -2 && !mod->minus;
	mod->base_len = 16;
	mod->hash = 2;
	if (mod->precision > 0)
		mod->precision = mod->precision + mod->hash;
	mod->arg_len = ul_number_digits(mod);
	mod->str_len = max(3, mod->precision, mod->arg_len, mod->width);
	mod->cp_str_len = mod->str_len;
	str = (char *)ft_calloc(mod->str_len + 1, sizeof(char));
	set_suffix(str, mod);
	if (!mod->precision && !arg)
		;
	else
		set_ul_digits(str, mod);
	set_prefix(str, mod);
	return (str);
}

char	*unsigned_int_print(t_mod *mod, va_list ap)
{
	unsigned int	arg;
	char			*str;

	arg = va_arg(ap, int);
	mod->arg = (void *)&arg;
	mod->zero = mod->zero && mod->precision == -2 && !mod->minus;
	if (mod->type == 'x' || mod->type == 'X')
	{
		if (mod->hash)
			mod->hash = (arg != 0) * 2;
		mod->base_len = 16;
	}
	else if (mod->type == 'u')
		mod->hash = 0;
	if (mod->precision > 0)
		mod->precision = mod->precision + mod->hash;
	mod->arg_len = u_number_digits(mod);
	mod->str_len = max(3, mod->precision, mod->arg_len, mod->width);
	mod->cp_str_len = mod->str_len;
	str = (char *)ft_calloc(mod->str_len + 1, sizeof(char));
	set_suffix(str, mod);
	if (!(!mod->precision && !arg))
		set_u_digits(str, mod);
	set_prefix(str, mod);
	return (str);
}
