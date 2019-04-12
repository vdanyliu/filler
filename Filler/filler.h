#ifndef FILLER_H
# define FILLER_H

# include "libft/libft.h"

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
	int 			max_xy[2];
	t_map			*map;
	t_map			*piece;
	t_map			*enemy_map;
}					t_game;

typedef struct		s_sol
{
	int 			x;
	int 			y;
	int 			dist;
}					t_sol;

t_map				*fr_create_map_line(char *str);
t_map				*fr_add_map_line(char *str, t_map *head);
void				fr_free_split(char **split);
void				fr_filler(t_game *game);
t_map				*ft_free_piece(t_game *game);
void				fr_brute_force(t_game *game, t_sol *sol);
void				fr_map_size(t_map *map, t_game *game);
t_map				*add_map_node(int x, int y, char c);
int					fr_sum(t_map *a, t_map *b, int x, int y);
t_map				*ft_free_enemy(t_game *game);
char 				g_enemy;
char 				g_me;

# endif
