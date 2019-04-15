/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:55:41 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/15 15:34:56 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_map		*fdf_alloc_map_center(t_map *map)
{
	t_map	*buff;

	buff = map;
	while (buff->next != NULL)
		buff = buff->next;
	while (buff->down != NULL)
		buff = buff->down;
	return (buff);
}

t_map		*fdf_center_map(t_map *map)
{
	t_map		*head;
	t_map		*line;
	int			xc;
	int			yc;

	head = map;
	head = fdf_alloc_map_center(head);
	xc = 1000 - head->x / 2;
	yc = 800 - head->y / 2;
	head = map;
	while (head)
	{
		line = head;
		while (line)
		{
			line->x += xc;
			line->y += yc;
			line = line->next;
		}
		head = head->down;
	}
	return (map);
}

t_map		*fdf_size_map(t_map *map)
{
	t_map	*head;
	t_map	*line;

	head = map;
	while (head)
	{
		line = head;
		while (line)
		{
			line->x *= 10;
			line->y *= 10;
			line = line->next;
		}
		head = head->down;
	}
	map = fdf_center_map(map);
	return (map);
}

void			fdf_print_map_mlx(t_mlx_ptr *mlx)
{
	t_map	*head;
	t_map	*line;

	head = mlx->game->map;
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx->game->map = fdf_size_map(mlx->game->map);
	while (head)
	{
		line = head;
		while (line)
		{
			fdf_put_lines(mlx, line);
			line = line->next;
		}
		head = head->down;
	}
}
