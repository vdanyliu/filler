/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_brute_force.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:16:45 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/14 18:09:02 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int			fr_check_area(t_game *game, long long x, long long y)
{
	if (x > game->m[0])
		return (1);
	if (y > game->m[1])
		return (1);
	return (0);
}

static int			fr_c_s(t_map *map, long int x, long int y)
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

static int			fr_space_correct(t_game *g, t_map *map, t_map *piece,
		t_sol *brute)
{
	int		match;
	t_map	*bu;

	match = 0;
	while (piece)
	{
		bu = piece;
		while (bu)
		{
			if (bu->symbol == '*')
			{
				if (bu->x + brute->x > g->m[0] || bu->y + brute->y > g->m[1])
					return (0);
				match += fr_c_s(map, (bu->x + brute->x), (bu->y + brute->y));
			}
			if (bu->next == NULL && bu->down == NULL)
				match = fr_check_area(g, (bu->x + brute->x),
						(bu->y + brute->y)) == 1 ? 0 : match;
			bu = bu->next;
		}
		piece = piece->down;
	}
	match = match == 1 ? match : 0;
	return (match);
}

static int			fr_dist_analys(t_map *enemy, t_map *piece,
		t_sol *br, int *dist)
{
	int		dist_buff;
	t_map	*buff_head;
	t_map	*buff_line;

	dist_buff = *dist;
	while (enemy)
	{
		buff_head = piece;
		while (buff_head)
		{
			buff_line = buff_head;
			while (buff_line)
			{
				if (buff_line->symbol == '*')
					fr_sum(buff_line, enemy, br->x, br->y) < dist_buff ?
					dist_buff = fr_sum(buff_line, enemy, br->x, br->y) : 0;
				buff_line = buff_line->next;
			}
			buff_head = buff_head->down;
		}
		enemy = enemy->next;
	}
	if (dist_buff < *dist)
		return (*dist = dist_buff);
	return (0);
}

void				fr_brute_force(t_game *game, t_sol *sol, t_sol *brute)
{
	t_map	*map;
	t_map	*piece;
	int		dist;

	map = game->map;
	piece = game->piece;
	while (brute->y <= game->m[1])
	{
		brute->x = 0;
		while (brute->x <= game->m[0])
		{
			if (fr_space_correct(game, map, piece, brute))
			{
				dist = sol->dist;
				if (fr_dist_analys(game->e_m, piece, brute, &dist))
				{
					sol->x = brute->x;
					sol->y = brute->y;
					sol->dist = dist;
				}
			}
			brute->x++;
		}
		brute->y++;
	}
}
