/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_fix_part_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:39:10 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/03 14:39:13 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void					pf_hesh_replace(char *str)
{
	char	*buff;
	char	tmp;

	buff = str;
	while (*buff && (*buff != 'x' && *buff != 'X'))
		buff++;
	if (*buff)
	{
		tmp = *buff;
		*buff = *(str + 1);
		*(str + 1) = tmp;
	}
}

char					*pf_space_fix(char *str)
{
	char	*buff;
	char	*str_buff;
	int		i;
	char	*new_str;

	if (*str == '-' || *str == '+')
		return (str);
	i = ft_strlen(str);
	buff = (char*)malloc(sizeof(char) * i + 2);
	*buff = ' ';
	new_str = buff;
	buff++;
	str_buff = str;
	while (*str_buff)
		*buff++ = *str_buff++;
	*buff = '\0';
	free(str);
	return (new_str);
}

void					pf_bonus_rules(t_type *buff)
{
	if (buff->flag->minus)
		buff->flag->zero = 0;
	if (buff->type > 10 && buff->type <= 20)
	{
		buff->type = buff->type - 10;
		buff->spec = 4;
	}
	if (buff->type == 10)
		buff->accur->number == -1 ? buff->accur->number = 6 : 0;
}

int						pf_nan_inf(t_type *buff, long double num)
{
	char	*str;
	char	*str1;

	if (num != num)
		str = ft_strdup("nan");
	else if (num * 2 == num && num != 0)
	{
		str = ft_strdup("inf");
		if (num < 0)
		{
			str = pf_add_one_space_before(str);
			*str = '-';
		}
	}
	else
		return (0);
	str1 = pf_spaces(buff, (buff->width->width - ft_strlen(str)));
	str1 = pf_union(buff, str1, str);
	g_len += write(1, str1, ft_strlen(str1));
	free(str1);
	return (1);
}

int						ft_minuszero(double num)
{
	long long	*ptr;
	long long	bits;

	ptr = (long long*)(&num);
	bits = *ptr;
	bits = bits >> 63;
	if (bits < 0)
		return (1);
	return (0);
}
