/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanyliu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:15:04 by vdanyliu          #+#    #+#             */
/*   Updated: 2019/04/11 14:49:10 by vdanyliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_gnl	*gnl_create_head(int fd)
{
	t_gnl	*head;

	head = (t_gnl*)malloc(sizeof(t_gnl));
	head->fd = fd;
	head->str = ft_strdup("");
	head->next = NULL;
	return (head);
}

static t_gnl 	*gnl_get_curr(int fd, t_gnl *head)
{
	if (fd == head->fd)
		return (head);
	while (head->next)
	{
		head = head->next;
		if (fd == head->fd)
			return (head);
	}
	head->next = gnl_create_head(fd);
	return (head->next);
}

static char *gnl_copyline(char *str)
{
	char			*line;
	unsigned long	len;
	char 			*buff;

	buff = ft_strstr(str, "\n");
	if (buff == NULL)
		return (ft_strdup(""));
	len = (buff - str);
	line = ft_strsub(str, 0, len);
	return (line);
}

static char	*gnl_next_slash(char *str)
{
	char 			*strbuff;

	strbuff = ft_strstr(str, "\n");
	if (strbuff == NULL)
	{
		free(str);
		return (ft_strdup(""));
	}
	strbuff = ft_strdup(strbuff + 1);
	free (str);
	return (strbuff);
}

int 		get_next_line(const int fd, char **line)
{
	static t_gnl	*head = NULL;
	t_gnl 			*curr;
	char 			buff[BUFF_SIZE + 1];
	char 			*leak;
	ssize_t 		i;

	if (fd < 0 || read(fd, NULL, 0) < 0 || !line)
		return (-1);
	head == NULL ? head = gnl_create_head(fd) : 0;
	curr = gnl_get_curr(fd, head);
	if (ft_strchr(curr->str, '\n') == 0)
		while ((i = read(fd, buff, BUFF_SIZE)) > 0)
		{
			buff[i] = '\0';
			leak = curr->str;
			curr->str = ft_strjoin(curr->str, buff);
			free(leak);
			if (ft_strchr(buff, '\n') != 0)
				break;
		}
	*line = gnl_copyline(curr->str);
	if (ft_strlen(*line) == 0 && ft_strlen(curr->str) == 0)
		return (0);
	curr->str = gnl_next_slash(curr->str);
	return (1);
}