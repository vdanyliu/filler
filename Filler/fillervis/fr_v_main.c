/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_v_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:10:26 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/15 18:44:54 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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

static t_mlx_ptr	*mlx_ptr_init(void)
{
	t_mlx_ptr	*mlx_ptrs;

	mlx_ptrs = (t_mlx_ptr*)(malloc)(sizeof(*mlx_ptrs));
	mlx_ptrs->mlx_ptr = mlx_init();
	mlx_ptrs->win_ptr = mlx_new_window(mlx_ptrs->mlx_ptr, 2000, 1600, "Filler");
	mlx_ptrs->game = NULL;
	return (mlx_ptrs);
}

static int			key_release(int keycode, void *param)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

static int			closeprog(void *param)
{
	(void)param;
	exit(0);
}

static void			fdf_mlx_manipulation(t_mlx_ptr *mlx)
{
	mlx_hook((mlx)->win_ptr, 17, 0, closeprog, (void *) 0);
	mlx_hook((mlx)->win_ptr, 2, 0, key_release, (void *) mlx);
}

int				main(void)
{
	t_mlx_ptr		*mlx;

	mlx = mlx_ptr_init();
	//mlx_hook(g_image.mlx_window, 2, 5, exit_1, &filler);
	ft_printf("Start Visualise\n");
	fdf_mlx_manipulation(mlx);
	mlx_loop_hook(mlx->mlx_ptr, fr_filler_print, &mlx);
	mlx_loop(mlx->mlx_ptr);
	//fdf_mlx_manipulation(mlx);
	return (0);
}
