#ifndef FILLER_FILLER_H
# define FILLER_FILLER_H

# include "libft/libft.h"

typedef struct 		s_map
{
	char 			symbol;
	int 			x;
	int 			y;
	struct s_map	*next;
	struct s_map	*down;
}					t_map;

typedef struct		s_piece
{
	char			symbol;
	int 			x;
	int 			y;
	struct s_piece	*next;
}					t_piece;

typedef struct		s_game
{
	int 			player;
	t_map			*map;
	t_map			*piece;
	t_map			*map_list;
}					t_game;

t_map				*fr_create_map_line(char *str);
t_map				*fr_add_map_line(char *str, t_map *head);
void				fr_free_split(char **split);
void				fr_filler(t_game *game);

# endif
