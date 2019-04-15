/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:49:56 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/03 14:49:58 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct			s_flag
{
	char				minus;
	char				plus;
	char				space;
	char				hesh;
	char				zero;
}						t_flag;

typedef struct			s_width
{
	int					width;
	char				star;
}						t_width;

typedef struct			s_accuracy
{
	int					number;
	char				star;
}						t_accuracy;

typedef struct			s_specifier
{
	int					specifier;
}						t_specifier;

typedef struct			s_type
{
	int					type;
	int					spec;
	struct s_accuracy	*accur;
	struct s_width		*width;
	struct s_flag		*flag;
	struct s_type		*next;
}						t_type;

typedef struct			s_float
{
	char				*whole;
	char				*rest;
}						t_float;

int						ft_printf(const char *format, ...);
int						g_len;
void					pf_type_initiation(t_type **head, char *format);
t_type					*pf_create_type_lst();
void					pf_type_deafult_flags(t_type *buff, char *str);
void					pf_type_diouxx_flags(t_type *curr, char *str);
int						pf_is_type(char c);
void					pf_write_and_remalloc(char **str);
void					pf_skip_flag_remalloc(char **str);
void					pf_write_flag(va_list ptr, t_type **lst);
void					ft_free_t_type(t_type *head);
int						pf_type_group(int c);
void					pf_print_procent(t_type *buff);
void					pf_print_csp(t_type *buff, va_list ptr);
void					pf_print_diouxx(t_type *buff, va_list ptr);
char					*pf_spaces(t_type *buff, int i);
char					*pf_union(t_type *buff, char *str1, char *str2);
char					*pf_itoabase(long long i, int base);
char					*pf_itoabaseun(unsigned long long i, int base);
char					*pf_accur_fixdiouxx(int i, char *str);
char					*pf_plus_fix(char *str);
char					*pf_space_fix(char *str);
char					*pf_pointer_accur(int i, char *str);
char					*pf_add_one_space_before(char *str);
char					*pf_add_hash_flag(t_type *buff, char *str, int base);
void					pf_hesh_replace(char *str);
void					pf_bonus_rules(t_type *buff);
void					pf_print_float(t_type *buff, long double num);
long double				pf_powun(int nbr, int pow);
int						pf_nan_inf(t_type *buff, long double num);
int						ft_minuszero(double i);
int						pf_is_zero(char *str);
char					*pf_accur_fixd_p1(char *str);
void					pf_accir_fixd_p2(char *buff, char *new_str,
											char **new_str_buff);

#endif
