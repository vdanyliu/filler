/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_filler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:18:16 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/14 19:04:46 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		fr_enemy_list(t_game *game, t_map *en,
		t_map *map_head, t_map *map_buff)
{
	game->e_m = NULL;
	map_head = game->map;
	while (map_head)
	{
		map_buff = map_head;
		while (map_buff)
		{
			if (map_buff->symbol == g_enemy || map_buff->symbol == g_enemy + 32)
			{
				if (game->e_m == NULL)
				{
					game->e_m = add_map_node(map_buff->x, map_buff->y, g_enemy);
					en = game->e_m;
				}
				else
				{
					en->next = add_map_node(map_buff->x, map_buff->y, g_enemy);
					en = en->next;
				}
			}
			map_buff = map_buff->next;
		}
		map_head = map_head->down;
	}
}

void			fr_map_size(t_map *map, t_game *game)
{
	t_map *map_buff;

	if (map == NULL)
		exit(0);
	map_buff = map;
	while (map_buff->down)
		map_buff = map_buff->down;
	while (map_buff->next)
		map_buff = map_buff->next;
	game->m[0] = map_buff->x;
	game->m[1] = map_buff->y;
}

static void		fr_map_history(t_game *game)
{
	t_map	*line;
	t_map	*head;
	t_map	*buff;

	head = game->map;
	while (head)
	{
		line = head->next;
		while (line)
		{
			buff = line;
			line = line->next;
			free(buff);
		}
		buff = head;
		head = head->down;
		free(buff);
	}
	game->map = ft_free_piece(game);
}

static t_sol	*fr_solution_init(void)
{
	t_sol	*solution;

	solution = (t_sol*)malloc(sizeof(t_sol));
	solution->x = 42;
	solution->y = 42;
	solution->dist = 10000000;
	return (solution);
}

void			fr_filler(t_game *game)
{
	t_sol	*sol;
	t_sol	*brute;

	brute = fr_solution_init();
	brute->x = 0;
	brute->y = 0;
	fr_enemy_list(game, 0, 0, 0);
	sol = fr_solution_init();
	fr_brute_force(game, sol, brute);
	ft_printf("%i %i\n", sol->y, sol->x);
	fr_map_history(game);
	game->e_m = ft_free_enemy(game);
	free(sol);
	free(brute);
}
