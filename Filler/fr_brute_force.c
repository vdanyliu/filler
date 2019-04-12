/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_brute_force.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:16:45 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/12 18:18:12 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int 			fr_check_area(t_game *game, long long x, long long y)
{
	if (x > game->max_xy[0])
		return (1);
	if (y > game->max_xy[1])
		return (1);
	return (0);
}

static int 			fr_chek_star(t_map *map, long int x, long int y)
{
	t_map	*buff;

	buff = map;
	while (x-- > 0)
		buff = buff->next;
	while (y-- > 0)
		buff = buff->down;
	if (buff->symbol == g_me || buff->symbol == (g_me + 32))
		return (1);
	if (buff->symbol == g_enemy || buff->symbol == (g_enemy + 32))
		return (2);
	if (buff->symbol == '.')
		return (0);
	return (0);
}

static int			fr_space_correct(t_game *game, t_map *map, t_map *piece,  int x, int y)
{
	int 	match;
	t_map	*buff_phead;
	t_map	*buff_p;

	match = 0;
	buff_phead = piece;
	while (buff_phead)
	{
		buff_p = buff_phead;
		while (buff_p)
		{
			if (buff_p->symbol == '*')
			{
				if (buff_p->x + x > game->max_xy[0] || buff_p->y + y > game->max_xy[1])
					return (0);
				match += fr_chek_star(map, (buff_p->x + x), (buff_p->y + y));
			}
			if (buff_p->next == NULL && buff_p->down == NULL)
				match = fr_check_area(game, (buff_p->x + x),
						(buff_p->y + y)) == 1 ? 0 : match;
			buff_p = buff_p->next;
		}
		buff_phead = buff_phead->down;
	}
	if (match != 1)
		return (0);
	return (1);
}

static int 		fr_dist_analys(t_map *enemy, t_map *piece, int x, int y, int *dist)
{
	int 	i;
	int 	dist_buff;
	t_map	*buff_enem;
	t_map	*buff_head;
	t_map	*buff_line;

	buff_enem = enemy;
	dist_buff = *dist;
	while (buff_enem)
	{
		buff_head = piece;
		while (buff_head)
		{
			buff_line = buff_head;
			while (buff_line)
			{
				if (buff_line->symbol == '*')
				{
					i = fr_sum(buff_line, buff_enem, x, y);
					i < dist_buff ? dist_buff = i : 0;
				}
				buff_line = buff_line->next;
			}
			buff_head = buff_head->down;
		}
		buff_enem = buff_enem->next;
	}
	if (dist_buff < *dist)
	{
		*dist = dist_buff;
		return (1);
	}
	return (0);
}

void			fr_brute_force(t_game *game, t_sol *sol)
{
	t_map	*map;
	t_map	*piece;
	int 	x;
	int 	y;
	int 	dist;

	y = 0;
	map = game->map;
	piece = game->piece;
	while (y <= game->max_xy[1])
	{
		x = 0;
		while (x <= game->max_xy[0])
		{
			if (fr_space_correct(game, map, piece, x, y))
			{
				dist = sol->dist;
				if (fr_dist_analys(game->enemy_map, piece, x, y, &dist))
				{
					sol->x = x;
					sol->y = y;
					sol->dist = dist;
				}
			}
			x++;
		}
		y++;
	}
}