/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:40:10 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/03 14:40:12 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				pf_round_whole(char **whole, int i)
{
	int len;

	len = (int)ft_strlen(*whole) - 1;
	if (whole[0][len] % 2 == 0 && i == 2)
		return ;
	else if (i == 2)
	{
		pf_round_whole(whole, 1);
		return ;
	}
	whole[0][len] += 1;
	while (whole[0][len] == 58 && len-- >= 0)
	{
		whole[0][len + 1] = 48;
		len >= 0 ? whole[0][len] += 1 : 0;
	}
	if (len < 0)
	{
		*whole = pf_add_one_space_before(*whole);
		**whole = '1';
	}
}

static void				pf_round(char **whole, char *wrest, int i, double uni)
{
	if (i > 0)
	{
		if ((*(wrest + i--)) >= '5' && uni != 0.25)
			*(wrest + i) += 1;
		while (wrest[i] == 58 && i-- >= 0)
		{
			wrest[i + 1] = 48;
			i >= 0 ? wrest[i] += 1 : 0;
		}
	}
	else if (i == 0)
	{
		if (wrest[0] >= '5')
		{
			if (uni == 0.5)
				pf_round_whole(whole, 2);
			else
				pf_round_whole(whole, 1);
		}
	}
	if (i < 0)
		pf_round_whole(whole, 1);
}

static char				*pf_itoafloat(long double i, int num)
{
	char				*str;
	unsigned long long	newi;
	int					j;

	j = 0;
	str = ft_strnew(num);
	while (num-- > 0)
	{
		newi = (i *= 10);
		i -= newi;
		str[j++] = newi + 48;
	}
	return (str);
}

static void				pf_union_write(t_type *buff, char *whole, char *rest)
{
	char	*leak;
	char	*accurrest;
	char	*str1;

	accurrest = ft_strsub(rest, 0, (size_t)buff->accur->number);
	if ((buff->accur->number == 0 &&
	buff->flag->hesh == 1) || buff->accur->number > 0)
	{
		leak = whole;
		whole = ft_strjoin(whole, ".");
		free(leak);
	}
	leak = whole;
	whole = ft_strjoin(whole, accurrest);
	free(leak);
	free(accurrest);
	str1 = pf_spaces(buff, (buff->width->width - ft_strlen(whole)));
	str1 = pf_union(buff, str1, whole);
	g_len += write(1, str1, ft_strlen(str1));
	free(str1);
	free(rest);
}

void					pf_print_float(t_type *buff, long double num)
{
	unsigned long long	whole;
	t_float				flist;
	int					minus;

	minus = num >= 0 ? 0 : 1;
	num == 0 ? minus = ft_minuszero((double)num) : 0;
	if (pf_nan_inf(buff, num) == 1)
		return ;
	num < 0 ? num *= -1 : 0;
	whole = (unsigned long long)num;
	num -= whole;
	flist.whole = pf_itoabaseun(whole, 10);
	flist.rest = pf_itoafloat(num, (buff->accur->number + 2));
	pf_round(&(flist).whole, (flist).rest, buff->accur->number, num);
	if (minus || buff->flag->plus)
	{
		flist.whole = pf_add_one_space_before(flist.whole);
		*(flist).whole = (minus == 1) ? '-' : '+';
	}
	(buff->flag->space && *(flist).whole != '-' && *(flist).whole != '+') ?
		flist.whole = pf_add_one_space_before(flist.whole) : 0;
	pf_union_write(buff, flist.whole, flist.rest);
}
