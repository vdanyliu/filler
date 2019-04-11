/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flags_parcer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:39:59 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/03 14:40:01 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_type_deafult_flags(t_type *curr, char *str)
{
	char	*buff;
	t_type	*type_buff;

	buff = str;
	type_buff = curr;
	while (*buff && pf_is_type(*buff) == 0)
	{
		if (curr->width->width == 0 && *(buff - 1) != '-')
			*buff == '0' ? type_buff->flag->zero = 1 : 0;
		*buff == '-' ? type_buff->flag->minus = 1 : 0;
		*buff == '+' ? type_buff->flag->plus = 1 : 0;
		*buff == ' ' ? type_buff->flag->space = 1 : 0;
		*buff == '#' ? type_buff->flag->hesh = 1 : 0;
		if (ft_isdigit(*buff) && *buff != '0' &&
		*(buff - 1) != '.' && type_buff->width->width == 0)
			type_buff->width->width = ft_atoi(buff);
		buff++;
	}
}

void	pf_type_diouxx_flags(t_type *curr, char *str)
{
	char	*buff;
	t_type	*type_buff;

	buff = str;
	type_buff = curr;
	while (*buff && pf_is_type(*buff) == 0)
	{
		if (*buff == 'h' && *(buff + 1) == 'h' && !(type_buff->spec))
			type_buff->spec = 2;
		if (*buff == 'l' && *(buff + 1) == 'l' && !(type_buff->spec))
			type_buff->spec = 4;
		if (*buff == 'h' && type_buff->spec == 0)
			type_buff->spec = 1;
		if ((*buff == 'l' || *buff == 'L') && type_buff->spec == 0)
			type_buff->spec = 3;
		if (*buff == '.' && type_buff->accur->number == -1)
			type_buff->accur->number = ft_atoi(buff + 1);
		if (*buff == 'j' && type_buff->spec == 0)
			type_buff->spec = 5;
		if (*buff == 'z' && type_buff->spec == 0)
			type_buff->spec = 6;
		else if (*buff == '.' && *(buff + 1) == '*')
			type_buff->accur->star = 1;
		buff++;
	}
}
