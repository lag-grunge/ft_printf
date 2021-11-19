#include "ft_printf.h"

void	set_suffix(char *str, t_mod *mod)
{
	size_t	bound;

	if (mod->width != mod->str_len || !mod->minus)
		return ;
	bound = max(2, mod->precision, mod->arg_len);
	while (mod->str_len > (int)bound)
		str[--mod->str_len] = ' ';
	return ;
}

void	set_sign_or_hash(char *str, t_mod *mod)
{
	if (mod->sign)
	{
		if (*(int *)mod->arg < 0)
			str[--mod->str_len] = '-';
		else if (mod->space)
			str[--mod->str_len] = ' ';
		else if (mod->plus)
			str[--mod->str_len] = '+';
		mod->sign = 0;
	}
	else if (mod->hash)
	{
		if (mod->type == 'x' || mod->type == 'p')
			str[--mod->str_len] = 'x';
		else if (mod->type == 'X')
			str[--mod->str_len] = 'X';
		str[--mod->str_len] = '0';
	}
	return ;
}

void	set_prefix(char *str, t_mod *mod)
{
	short int	bound;

	if (mod->zero)
	{
		bound = max(2, mod->sign, mod->hash);
		while (mod->str_len > bound)
			str[--mod->str_len] = '0';
		set_sign_or_hash(str, mod);
	}
	else
	{
		while (mod->precision-- > mod->arg_len)
			str[--mod->str_len] = '0';
		set_sign_or_hash(str, mod);
		while (mod->str_len > 0)
			str[--mod->str_len] = ' ';
	}
}

void	set_string(char *str, t_mod *mod)
{
	char	*arg;
	size_t	i;

	arg = (char *)mod->arg;
	i = mod->arg_len;
	while (i > 0)
		str[--mod->str_len] = arg[--i];
}
