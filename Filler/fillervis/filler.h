#ifndef FILLER_H
# define FILLER_H

# include "libft/libft.h"
# include <mlx.h>
# include <math.h>

typedef struct 		s_map
{
	char 			symbol;
	int 			x;
	int 			y;
	struct s_map	*next;
	struct s_map	*down;
}					t_map;

typedef struct		s_game
{
	int 			player;
	int 			m[2];
	t_map			*map;
	t_map			*piece;
}					t_game;

typedef struct			s_mlx_ptr
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_game		*game;

}						t_mlx_ptr;

t_map				*fr_create_map_line(char *str);
t_map				*fr_add_map_line(char *str, t_map *head);
void				fr_free_split(char **split);
int					fr_filler_print(t_mlx_ptr **mlx);
t_map				*ft_free_piece(t_game *game);
void				fr_map_size(t_map *map, t_game *game);
t_map				*add_map_node(int x, int y, char c);
void				fdf_print_map_mlx(t_mlx_ptr *mlx);
void				fdf_put_lines(t_mlx_ptr *mlx, t_map *map);

# endif
