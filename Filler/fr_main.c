/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:10:26 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/11 19:38:09 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static t_game	*fr_game_create(char *str, int fd)
{
	t_game	*game;
	char	*str2;

	game = (t_game*)malloc(sizeof(t_game));
	game->map = NULL;
	game->piece = NULL;
	game->map_list = NULL;
	str2 = ft_strstr(str, "p");
	game->player = *(str2 + 1) == '1' ? 1 : 2;
	free(str);
	return (game);
}

static void		fr_map_fill(char *str, t_game *game)
{
	char	**split;
	char	*map;

	if (!ft_isdigit(*str))
	{
		free(str);
		return;
	}
	split = ft_strsplit(str, ' ');
	map = split[1];
	if (game->map == NULL)
		game->map = fr_create_map_line(map);
	else
		game->map = fr_add_map_line(map, game->map);
	fr_free_split(split);
	free(str);
}

void			debug_map_print(t_map *map, int fd)
{
	t_map	*line;

	while (map)
	{
		line = map;
		while (line)
		{
			dprintf(fd, "x = %i, y = %i, symbol = %c\n", line->x, line->y, line->symbol);
			line = line->next;
		}
		map = map->down;
	}
}

static void		fr_piece_fill(char	*str, t_game *game)
{
	char 	**split;
	int 	size;
	char 	*gnl;

	split = ft_strsplit(str, ' ');
	size = ft_atoi(split[1]);
	while (size > 0)
	{
		get_next_line(0, &gnl);
		if (game->piece == NULL)
			game->piece = fr_create_map_line(gnl);
		else
			game->piece = fr_add_map_line(gnl, game->piece);
		free(gnl);
		size--;
	}
}

int				main(void)
{
	char			*buff;
	int 			fd;
	t_game			*game;

	game = NULL;
	fd = open("./debug.txt", O_RDWR);
	while (get_next_line(0, &buff) > 0)
	{
		if (game == NULL)
		{
			game = fr_game_create(buff, fd);
			dprintf(fd, "Player = %i\n", game->player);
			continue ;
		}
		if (ft_strstr(buff, "Piece") == 0)
		{
			fr_map_fill(buff, game);
			//debug_map_print(game->map, fd);
			dprintf(fd, "GNL = %s\n", buff);
		}
		else
		{
			fr_piece_fill(buff, game);
			debug_map_print(game->piece, fd);
			fr_filler(game);
		}
	}
	return (0);
}