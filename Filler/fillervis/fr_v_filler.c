/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_v_filler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:18:16 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/15 18:29:02 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"


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


static t_game	*fr_game_create(char *str)
{
	t_game	*game;

	game = (t_game*)malloc(sizeof(t_game));
	game->map = NULL;
	game->piece = NULL;
	game->player = 0;
	free(str);
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
		if (ft_strstr(str, "=="))
			ft_printf("SCORE %s\n", str);
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
		free(gnl);
		size--;
	}
	free(str);
	fr_free_split(split);
}

int			fr_filler_print(t_mlx_ptr **mlx)
{
	char			*buff;

	while (get_next_line(0, &buff) > 0)
	{
		if ((*mlx)->game == NULL)
		{
			(*mlx)->game = fr_game_create(buff);
			continue ;
		}
		if (ft_strstr(buff, "Piece") == 0)
			fr_map_fill(buff, (*mlx)->game);
		else
		{
			if ((*mlx)->game->map == NULL)
				continue ;
			fr_piece_fill(buff, (*mlx)->game);
			fdf_print_map_mlx(*mlx);
			fr_map_history((*mlx)->game);
			mlx_do_sync((*mlx)->mlx_ptr);
		}
	}
	return (1);
}
