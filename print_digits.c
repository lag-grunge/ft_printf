#include "ft_printf.h"

void	set_digits(char *str, t_mod *mod)
{
	char	*base;
	int		arg;
	int		sign;

	arg = *(long int *)mod->arg;
	base = "0123456789";
	sign = 1 - 2 * (arg < 0);
	str[--mod->str_len] = base[sign * (arg % mod->base_len)];
	arg /= sign * mod->base_len;
	while (arg)
	{
		str[--mod->str_len] = base[arg % mod->base_len];
		arg /= mod->base_len;
	}
}

void	set_u_digits(char *str, t_mod *mod)
{
	char			*base;
	unsigned int	arg;

	arg = *(int *)mod->arg;
	if (mod->type == 'x')
		base = "0123456789abcdef";
	else if (mod->type == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789";
	str[--mod->str_len] = base[arg % mod->base_len];
	arg /= mod->base_len;
	while (arg)
	{
		str[--mod->str_len] = base[arg % mod->base_len];
		arg /= mod->base_len;
	}
}

void	set_ul_digits(char *str, t_mod *mod)
{
	char	*base;
	size_t	arg;

	arg = *(long int *)mod->arg;
	base = "0123456789abcdef";
	str[--mod->str_len] = base[arg % mod->base_len];
	arg /= mod->base_len;
	while (arg)
	{
		str[--mod->str_len] = base[arg % mod->base_len];
		arg /= mod->base_len;
	}
}
