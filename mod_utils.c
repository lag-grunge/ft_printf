#include "ft_printf.h"

void	mod_zero(t_mod *mod)
{
	mod->minus = 0;
	mod->zero = 0;
	mod->hash = 0;
	mod->space = 0;
	mod->plus = 0;
	mod->width = 0;
	mod->precision = -2;
	mod->type = 0;
	mod->str_len = 0;
	mod->cp_str_len = 0;
	mod->sign = 0;
	mod->arg = NULL;
	mod->base_len = 10;
}

t_mod 	*mod_init(void)
{
	t_mod	*mod;

	mod = (t_mod *)malloc(sizeof(t_mod) * 1);
	mod_zero(mod);
	return (mod);
}

void	del_mod(t_mod *mod)
{
	mod_zero(mod);
	free(mod);
}
