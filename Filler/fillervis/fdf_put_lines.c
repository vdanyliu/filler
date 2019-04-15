/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_put_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:59:51 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/15 15:12:06 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		fr_color(t_map *map)
{
	if (map->symbol == '.')
		return (8947848);
	if (map->symbol == 'X' || map->symbol == 'x')
		return (255);
	return (16776960);
}

static void		fdf_put_line(t_mlx_ptr *mlx, t_map *map0, t_map *map1)
{
	int		dx[2];
	int		dy[2];
	int		d[2];
	int		y;
	int		x;

	dx[0] = (map1->x - map0->x);
	dy[0] = (map1->y - map0->y);
	dx[1] = map0->x < map1->x ? 1 : -1;
	dy[1] = map0->y < map1->y ? 1 : -1;
	d[0] = dx[0] > dy[0] ? dx[0] / 2 : 0 - dy[0] / 2;
	x = map0->x;
	y = map0->y;
	while (42)
	{
		mlx_pixel_put(mlx->win_ptr, mlx->win_ptr, x, y,
				fr_color(map0));
		if (x == map1->x && y == map1->y)
			break ;
		d[1] = d[0];
		d[0] = d[1] > -dx[0] ? d[0] - dy[0] : d[0];
		x = d[1] > -dx[0] ? x + dx[1] : x;
		d[0] = d[1] < dy[0] ? d[0] + dx[0] : d[0];
		y = d[1] < dy[0] ? y + dy[1] : y;
	}
}

void			fdf_put_lines(t_mlx_ptr *mlx, t_map *map)
{
	if (map->next != NULL)
		fdf_put_line(mlx, map, map->next);
	if (map->down != NULL)
		fdf_put_line(mlx, map, map->down);
}
