/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:10:26 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/14 19:22:51 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static t_game	*fr_game_create(char *str)
{
	t_game	*game;
	char	*str2;

	game = (t_game*)malloc(sizeof(t_game));
	game->map = NULL;
	game->piece = NULL;
	str2 = ft_strstr(str, "p");
	game->player = *(str2 + 1) == '1' ? 1 : 2;
	free(str);
	g_enemy = game->player == 1 ? 'X' : 'O';
	g_me = g_enemy == 'X' ? 'O' : 'X';
	game->m[0] = -1;
	game->m[1] = -1;
	return (game);
}

static void		fr_map_fill(char *str, t_game *game)
{
	char	**split;
	char	*map;

	if (!ft_isdigit(*str))
	{
		free(str);
		return ;
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

t_map			*ft_free_enemy(t_game *game)
{
	t_map	*head;
	t_map	*line;
	t_map	*buff;

	head = game->e_m;
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
	game->e_m = NULL;
	return (NULL);
}

static void		fr_piece_fill(char *str, t_game *game)
{
	char	**split;
	int		size;
	char	*gnl;

	split = ft_strsplit(str, ' ');
	size = ft_atoi(split[1]);
	while (size > 0)
	{
		get_next_line(0, &gnl);
		if (ft_strlen(gnl) == 0)
			exit (0);
		if (game->piece == NULL)
			game->piece = fr_create_map_line(gnl);
		else
			game->piece = fr_add_map_line(gnl, game->piece);
		free(gnl);
		size--;
	}
	free(str);
	fr_free_split(split);
	fr_map_size(game->map, game);
}

int				main(void)
{
	char			*buff;
	t_game			*game;

	game = NULL;
	while (get_next_line(0, &buff) > 0)
	{
		if (game == NULL)
		{
			game = fr_game_create(buff);
			continue ;
		}
		if (ft_strstr(buff, "Piece") == 0)
			fr_map_fill(buff, game);
		else
		{
			fr_piece_fill(buff, game);
			fr_filler(game);
		}
	}
	return (0);
}
