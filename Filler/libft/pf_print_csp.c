/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_csp%.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:41:17 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/03 14:41:19 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		pf_print_procent(t_type *buff)
{
	char	*str1;
	char	*str2;
	size_t	i;

	str2 = (char*)malloc(sizeof(char) * 2);
	str2[0] = '%';
	str2[1] = '\0';
	str1 = pf_spaces(buff, (buff->width->width - 1));
	str1 = pf_union(buff, str1, str2);
	i = ft_strlen(str1);
	g_len += i;
	write(1, str1, i);
	free(str1);
}

static void	pf_print_char(t_type *buff, char c)
{
	char	*str1;
	char	*str2;
	size_t	i;

	str2 = (char*)malloc(sizeof(char) * 2);
	str2[0] = c;
	str2[1] = '\0';
	str1 = pf_spaces(buff, (buff->width->width - 1));
	str1 = pf_union(buff, str1, str2);
	if (c == 0 && buff->flag->minus)
		g_len += write(1, "\0", 1);
	i = ft_strlen(str1);
	g_len += write(1, str1, i);
	if (c == 0 && !buff->flag->minus)
		g_len += write(1, "\0", 1);
	free(str1);
}

static void	pf_print_string(t_type *buff, char *str)
{
	char	*str1;
	char	*str2;
	size_t	i;
	char	*strnull;

	if (str == NULL)
	{
		strnull = ft_strdup("(null)");
		if (buff->accur->number == -1)
			str2 = ft_strdup(strnull);
		else
			str2 = ft_strsub(strnull, 0,
					strnull - (strnull - buff->accur->number));
		free(strnull);
	}
	else if (buff->accur->number == -1)
		str2 = ft_strdup(str);
	else
		str2 = ft_strsub(str, 0, str - (str - buff->accur->number));
	str1 = pf_spaces(buff, (buff->width->width - (int)ft_strlen(str2)));
	str1 = pf_union(buff, str1, str2);
	i = ft_strlen(str1);
	g_len += write(1, str1, i);
	free(str1);
}

static void	pf_print_pointer(t_type *buff, unsigned long long int j)
{
	char	*str1;
	char	*str2;
	char	*leak;

	str2 = pf_itoabase(j, 16);
	str2 = pf_pointer_accur(buff->accur->number, str2);
	leak = str2;
	str2 = ft_strjoin("0x", str2);
	free(leak);
	str1 = pf_spaces(buff, (buff->width->width - ft_strlen(str2)));
	if (j != 0 || buff->flag->zero == 0)
		str1 = pf_union(buff, str1, str2);
	else
	{
		leak = str1;
		str1 = ft_strjoin(str2, str1);
		free(leak);
		free(str2);
	}
	g_len += write(1, str1, ft_strlen(str1));
	free(str1);
}

void		pf_print_csp(t_type *buff, va_list ptr)
{
	if (buff->type == 1)
		pf_print_char(buff, va_arg(ptr, int));
	if (buff->type == 2)
		pf_print_string(buff, va_arg(ptr, char*));
	if (buff->type == 3)
		pf_print_pointer(buff, va_arg(ptr, unsigned long long int));
}
