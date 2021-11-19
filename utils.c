#include "ft_printf.h"

int	number_digits(t_mod *mod)
{
	int			res;
	short int	sign;
	int			n;

	res = 0;
	n = *(int *)mod->arg;
	sign = mod->sign;
	if (!n && mod->precision != 0)
		res = 1;
	while (n)
	{
		n /= mod->base_len;
		res++;
	}
	return (res + sign);
}

int	u_number_digits(t_mod *mod)
{
	int				res;
	short int		hash;
	unsigned int	un;

	res = 0;
	un = *(int *)mod->arg;
	hash = mod->hash;
	if (!un && mod->precision != 0)
		res = 1;
	while (un)
	{
		un /= mod->base_len;
		res++;
	}
	return (res + hash);
}

int	ul_number_digits(t_mod *mod)
{
	int			res;
	short int	hash;
	size_t		uln;

	res = 0;
	uln = *(long int *)mod->arg;
	hash = mod->hash;
	if (!uln && mod->precision != 0)
		res = 1;
	while (uln)
	{
		uln /= mod->base_len;
		res++;
	}
	return (res + hash);
}

int	max(size_t n, int a, ...)
{
	va_list	ap;
	int		b;
	size_t	i;
	int		max;

	i = 1;
	va_start(ap, a);
	max = a;
	while (i < n)
	{
		b = va_arg(ap, int);
		if (max < b)
			max = b;
		i++;
	}
	va_end(ap);
	return (max);
}

int	min(size_t n, int a, ...)
{
	va_list	ap;
	int		b;
	size_t	i;
	int		min;

	i = 1;
	va_start(ap, a);
	min = a;
	while (i < n)
	{
		b = va_arg(ap, int);
		if (min > b)
			min = b;
		i++;
	}
	va_end(ap);
	return (min);
}
