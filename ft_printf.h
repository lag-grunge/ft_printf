#ifndef FT_PRINTF_H	
# define FT_PRINTF_H
# define FLAGS "-0# +"
# define TYPES "cspdiuXx"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_mod {
	short int	minus;
	short int	zero;
	short int	hash;
	short int	space;
	short int	plus;
	short int	sign;
	short int	width;
	short int	precision;
	char		type;
	void		*arg;
	short int	arg_len;
	short int	str_len;
	short int	cp_str_len;
	short int	base_len;
}				t_mod;

typedef struct s_str {
	char			*str;
	char			*verb;
	char			*conv;
	short int		ret;
}				t_str;

int		ft_printf(const char *fmt, ...);

char	*parser(char *conv, t_mod *mod, va_list ap);
int		is_flg(char **cur, t_mod *mod);
int		is_nonzero_digit(char **cur, t_mod *mod);
int		is_point(char **cur, t_mod *mod);
int		is_asterisk(char **cur, t_mod *mod, va_list ap);

char	*int_print(t_mod *mod, va_list ap);
char	*str_print(t_mod *mod, va_list ap);
char	*char_print(t_mod *mod, va_list ap);
char	*pointer_print(t_mod *mod, va_list ap);
char	*unsigned_int_print(t_mod *mod, va_list ap);

void	set_suffix(char *str, t_mod *mod);
void	set_digits(char *str, t_mod *mod);
void	set_u_digits(char *str, t_mod *mod);
void	set_ul_digits(char *str, t_mod *mod);
void	set_string(char *str, t_mod *mod);
void	set_prefix(char *str, t_mod *mod);
void	set_sign_or_hash(char *str, t_mod *mod);

t_mod	*mod_init(void);
void	del_mod(t_mod *mod);
void	mod_zero(t_mod *mod);

int		number_digits(t_mod *mod);
int		u_number_digits(t_mod *mod);
int		ul_number_digits(t_mod *mod);
int		max(size_t n, int a, ...);
int		min(size_t n, int a, ...);

#endif
