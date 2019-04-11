/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_part_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:41:28 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/03 14:41:33 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				pf_print_dexs(t_type *buff, long long int j)
{
	char	*str1;
	char	*str2;
	size_t	i;

	buff->spec == 1 ? str2 = pf_itoabase((signed short)j, 10) : 0;
	buff->spec == 2 ? str2 = pf_itoabase((signed char)j, 10) : 0;
	buff->spec == 3 ? str2 = pf_itoabase((signed long)j, 10) : 0;
	buff->spec == 4 ? str2 = pf_itoabase(j, 10) : 0;
	buff->spec == 0 ? str2 = pf_itoabase((signed int)j, 10) : 0;
	buff->spec == 5 ? str2 = pf_itoabase((intmax_t)j, 10) : 0;
	buff->spec == 6 ? str2 = pf_itoabase((ssize_t)j, 10) : 0;
	buff->flag->plus == 1 ? str2 = pf_plus_fix(str2) : 0;
	buff->flag->space == 1 ? str2 = pf_space_fix(str2) : 0;
	str2 = pf_accur_fixdiouxx(buff->accur->number, str2);
	str1 = pf_spaces(buff, (buff->width->width - ft_strlen(str2)));
	str1 = pf_union(buff, str1, str2);
	i = ft_strlen(str1);
	g_len += i;
	write(1, str1, i);
	free(str1);
}

static void				pf_print_dexuns(t_type *buff, unsigned long long j)
{
	char	*str1;
	char	*str2;
	size_t	i;

	buff->spec == 1 ? str2 = pf_itoabaseun((unsigned short)j, 10) : 0;
	buff->spec == 2 ? str2 = pf_itoabaseun((unsigned char)j, 10) : 0;
	buff->spec == 3 ? str2 = pf_itoabaseun((unsigned long)j, 10) : 0;
	buff->spec == 4 ? str2 = pf_itoabaseun(j, 10) : 0;
	buff->spec == 0 ? str2 = pf_itoabaseun((unsigned int)j, 10) : 0;
	buff->spec == 5 ? str2 = pf_itoabaseun((uintmax_t)j, 10) : 0;
	buff->spec == 6 ? str2 = pf_itoabaseun((size_t)j, 10) : 0;
	str2 = pf_accur_fixdiouxx(buff->accur->number, str2);
	str1 = pf_spaces(buff, (buff->width->width - ft_strlen(str2)));
	str1 = pf_union(buff, str1, str2);
	i = ft_strlen(str1);
	g_len += i;
	write(1, str1, i);
	free(str1);
}

static char				*pf_low_to_up_case(char *str)
{
	char	*buff;

	buff = str;
	while (*buff)
	{
		if (*buff >= 'a' && *buff <= 'z')
			*buff -= 32;
		buff++;
	}
	return (str);
}

static void				pf_print_ox(t_type *buff, unsigned long long j)
{
	char	*str1;
	char	*str2;
	size_t	i;
	int		base;

	base = buff->type == 6 ? 8 : 16;
	buff->spec == 1 ? str2 = pf_itoabaseun((unsigned short)j, base) : 0;
	buff->spec == 2 ? str2 = pf_itoabaseun((unsigned char)j, base) : 0;
	buff->spec == 3 ? str2 = pf_itoabaseun((unsigned long)j, base) : 0;
	buff->spec == 4 ? str2 = pf_itoabaseun(j, base) : 0;
	buff->spec == 0 ? str2 = pf_itoabaseun((unsigned int)j, base) : 0;
	buff->spec == 5 ? str2 = pf_itoabaseun((uintmax_t)j, base) : 0;
	buff->spec == 6 ? str2 = pf_itoabaseun((size_t)j, base) : 0;
	str2 = pf_accur_fixdiouxx(buff->accur->number, str2);
	buff->flag->hesh ? str2 = pf_add_hash_flag(buff, str2, base) : 0;
	str1 = pf_spaces(buff, (buff->width->width - ft_strlen(str2)));
	buff->type == 9 ? str2 = pf_low_to_up_case(str2) : 0;
	str1 = pf_union(buff, str1, str2);
	(buff->flag->hesh == 1 && (buff->type == 8 || buff->type == 9))
	&& buff->flag->zero == 1 ? pf_hesh_replace(str1) : 0;
	i = ft_strlen(str1);
	g_len += i;
	write(1, str1, i);
	free(str1);
}

void					pf_print_diouxx(t_type *buff, va_list ptr)
{
	if (buff->accur->number != -1)
		buff->flag->zero = 0;
	if (buff->type == 4 || buff->type == 5)
		pf_print_dexs(buff, va_arg(ptr, long long));
	if (buff->type == 7)
		pf_print_dexuns(buff, va_arg(ptr, unsigned long long));
	if (buff->type == 6 || buff->type == 8 || buff->type == 9)
		pf_print_ox(buff, va_arg(ptr, unsigned long long));
}
