#include "ft_printf.h"
#include "libft.h"

static int	is_type(char **cur, t_mod *mod)
{
	char	*type;

	type = ft_strchr(TYPES, **cur);
	if (type)
	{	
		if (mod->precision == -1 && *(*cur - 1) == '.')
			mod->precision = 0;
		mod->type = **cur;
		*cur += 1;
		return (1);
	}
	return (0);
}

static void	put_crust(char **crust, t_mod *mod)
{
	mod->arg = malloc(sizeof(char));
	((char *)mod->arg)[0] = **crust;
	mod->type = 'c';
	*crust += 1;
}

char	*parser(char *conv, t_mod *mod, va_list ap)
{
	char	*cur;
	int		res;

	cur = conv + 1;
	res = 0;
	while (is_flg(&cur, mod))
		;
	if (is_nonzero_digit(&cur, mod))
		;
	else if (is_asterisk(&cur, mod, ap))
		;
	if (is_point(&cur, mod))
	{
		if (is_nonzero_digit(&cur, mod))
			;
		else if (is_asterisk(&cur, mod, ap))
			;
		else
			mod->precision = 0;
	}
	res = is_type(&cur, mod);
	if (!res)
		put_crust(&cur, mod);
	return (cur);
}
