/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:40:32 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/03 14:40:36 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double					pf_powun(int nbr, int pow)
{
	long double	res;

	res = 1;
	while (pow-- >= 1)
		res *= nbr;
	return (res);
}

char						*pf_itoabase(long long i, int base)
{
	char	*str;
	int		j;
	int		minus;

	j = 1;
	minus = 0;
	if (i == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	if (i < 0)
	{
		minus = 1;
		i *= -1;
	}
	while (pf_powun(base, j) - 1 < i)
		j++;
	str = (char*)malloc(sizeof(char) * j + minus + 1);
	*(str + j + minus) = '\0';
	while (j-- > 0)
	{
		*(str + j + minus) = (i % base) + (i % base > 9 ? 'a' - 10 : '0');
		i /= base;
	}
	minus == 1 ? *str = '-' : 0;
	return (str);
}

char						*pf_itoabaseun(unsigned long long i, int base)
{
	char	*str;
	int		j;

	j = 1;
	while (pf_powun(base, j) - 1 < i)
		j++;
	str = (char*)malloc(sizeof(char) * j + 1);
	*(str + j) = '\0';
	while (j-- > 0)
	{
		*(str + j) = (i % base) + (i % base > 9 ? 'a' - 10 : '0');
		i /= base;
	}
	return (str);
}
