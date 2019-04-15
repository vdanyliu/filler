/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_usefull.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:57:05 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/14 16:45:27 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		fr_sum(t_map *a, t_map *b, int x, int y)
{
	int		sum1;
	int		sum2;

	sum1 = a->x + x - b->x;
	sum1 = sum1 < 0 ? -sum1 : sum1;
	sum2 = a->y + y - b->y;
	sum2 = sum2 < 0 ? -sum2 : sum2;
	return (sum1 + sum2);
}
