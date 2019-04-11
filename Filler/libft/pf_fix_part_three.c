/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_fix_part_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:00:23 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/03 16:00:25 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*pf_accur_fixd_p1(char *str)
{
	char	*leak;

	leak = str;
	*str == '0' ? str = ft_strdup("") : 0;
	*str == '+' ? str = ft_strdup("+") : 0;
	*str == ' ' ? str = ft_strdup(" ") : 0;
	free(leak);
	return (str);
}

void		pf_accir_fixd_p2(char *buff, char *new_str, char **new_str_buff)
{
	*buff == '-' ? *new_str = '-' : 0;
	*buff == '+' ? *new_str = '+' : 0;
	*buff == ' ' ? *new_str = ' ' : 0;
	(*new_str_buff)++;
}
