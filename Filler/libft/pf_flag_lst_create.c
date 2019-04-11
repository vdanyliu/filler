/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flag_lst_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:39:27 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/03 14:39:28 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flag			*pf_create_flag_lst(void)
{
	t_flag	*lst;

	lst = (t_flag*)malloc(sizeof(t_flag));
	lst->hesh = 0;
	lst->minus = 0;
	lst->plus = 0;
	lst->space = 0;
	lst->zero = 0;
	return (lst);
}

t_width			*pf_create_width_lst(void)
{
	t_width	*lst;

	lst = (t_width*)malloc(sizeof(t_width*));
	lst->star = 0;
	lst->width = 0;
	return (lst);
}

t_accuracy		*pf_create_accur_lst(void)
{
	t_accuracy	*lst;

	lst = (t_accuracy*)malloc(sizeof(t_accuracy));
	lst->number = -1;
	lst->star = 0;
	return (lst);
}

t_type			*pf_create_type_lst(void)
{
	t_type	*lst;

	lst = (t_type*)malloc(sizeof(t_type));
	lst->type = 0;
	lst->spec = 0;
	lst->accur = pf_create_accur_lst();
	lst->width = pf_create_width_lst();
	lst->flag = pf_create_flag_lst();
	lst->next = NULL;
	return (lst);
}
