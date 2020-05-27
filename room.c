/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 12:54:06 by cnails            #+#    #+#             */
/*   Updated: 2020/05/25 18:11:29 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	init_room(t_room *room)
{
	room->bfs = 0;
	room->is_empty = true;
	room->head = NULL;
	room->input = 0;
	room->is_used = false;
	room->is_inter = false;
	room->is_start = false;
	room->is_end = false;
	room->name = NULL;
	room->next = NULL;
	room->output = 0;
	room->x = 0;
	room->y = 0;
}

void	validate_room(t_lemin *data, t_room *room)
{
	t_room *head;

	head = data->head;
	while (head)
	{
		if ((head->x == room->x && head->y == room->y) ||\
			((ft_strlen(head->name) == ft_strlen(room->name))\
				&& !ft_strcmp(head->name, room->name)))
			ft_error("room validate\n");
		head = head->next;
	}
}

void	parse_room_data(t_lemin *data, t_room *room, char **line)
{
	room->name = ft_strdup(line[0]);
	data->var.i = 0;
	while(line[1][data->var.i])
	{
		if (!ft_isdigit(line[1][data->var.i]))
			ft_error("coord error\n");
		data->var.i++;
	}
	room->x = ft_atoi(line[1]);
	data->var.i = 0;
	while(line[2][data->var.i])
	{
		if (!ft_isdigit(line[2][data->var.i]))
			ft_error("coord error\n");
		data->var.i++;
	}
	room->y = ft_atoi(line[2]);
	validate_room(data, room);
}

bool	parse_coords_room(t_lemin *data, t_room *room, char *line)
{
	char **split;

	data->var.i = 0;
	split = ft_strsplit(line, ' ');
	if (line[0] == 'L')
		ft_error("error room\n");
	while (split[data->var.i])
		data->var.i++;
	if (data->var.i == 1)
	{
		free_split(split);
		return (true);
	}
	if (data->var.i != 3)
		ft_error("room error\n");
	parse_room_data(data, room, split);
	free_split(split);
	return (false);
}

void	append_room(t_lemin *data, t_room *room)
{
	if (!data->rooms)
	{
		data->rooms = room;
		data->head = data->rooms;
	}
	else
	{
		data->rooms->next = room;
		data->rooms = data->rooms->next;
	}
}

void	parse_room(t_lemin *data, bool start, bool end)
{
	t_room *room;
	
	room = (t_room *)ft_memalloc(sizeof(t_room));
	init_room(room);
	if (start || end)
	{
		room->is_start = start;
		room->is_end = end;
		if (room->is_end)
			room->bfs = INT_MAX;
		free(data->var.line);
		if (get_next_line(0, &data->var.line) == -1)
			ft_error("parse_room");
	}
	else
		room->is_inter = true;
	if (!parse_coords_room(data, room, data->var.line))
	{
		free(data->var.line);
		append_room(data, room);
	}
	else
	{
		free(room);
		parse_links(data);
	}
}
