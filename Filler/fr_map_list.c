/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_map_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:58:54 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/12 17:52:41 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_map			*add_map_node(int x, int y, char c)
{
	t_map	*node;

	node = (t_map*)malloc(sizeof(t_map));
	node->next = NULL;
	node->down = NULL;
	node->x = x;
	node->y = y;
	node->symbol = c;
	return (node);
}

t_map			*fr_create_map_line(char *str)
{
	t_map	*head;
	t_map	*curr;
	int 	x;

	x = 0;
	head = add_map_node(-1, -1, 'h');
	curr = head;
	while (*str)
	{
		curr->next = add_map_node(x, 0, *str);
		curr = curr->next;
		x++;
		str++;
	}
	curr = head;
	head = head->next;
	free(curr);
	return (head);
}

t_map			*fr_add_map_line(char *str, t_map *head)
{
	int 	y;
	t_map	*buff;
	t_map	*down;

	buff = head;
	y = 1;
	while (head->down)
	{
		head = head->down;
		y++;
	}
	head->down = fr_create_map_line(str);
	down = head->down;
	while (down)
	{
		down->y = y;
		head->down = down;
		head = head->next;
		down = down->next;
	}
	return (buff);
}

void			fr_free_split(char **split)
{
	char 	**head;

	head = split;
	while (*split)
	{
		free(*split);
		split++;
	}
	free(head);
}

t_map			*ft_free_piece(t_game *game)
{
	t_map	*head;
	t_map	*line;
	t_map	*buff;

	head = game->piece;
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
	game->piece = NULL;
	return (NULL);
}