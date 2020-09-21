/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 12:54:06 by cnails            #+#    #+#             */
/*   Updated: 2020/09/21 12:32:55 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

bool		is_valid_int(int nbr, char *str)
{
	char *tmp;

	tmp = ft_itoa(nbr);
	if (ft_strcmp(tmp, str))
	{
		free(tmp);
		return (false);
	}
	return (true);
}

void	parse_room_data(t_lemin *data, t_room *room, char **line)
{
	room->name = ft_strdup(line[0]);
	if (!is_valid_int(ft_atoi(line[1]), line[1]))
		ft_error(data, "first coordinate of room is not valid");
	room->x = ft_atoi(line[1]);
	if (!is_valid_int(ft_atoi(line[2]), line[2]))
		ft_error(data, "second coordinate of room is not valid");
	room->y = ft_atoi(line[2]);
	validate_room(data, room);
}

bool	parse_coords_room(t_lemin *data, t_room *room, char *line)
{
	char **split;

	data->var.i = 0;
	split = ft_strsplit(line, ' ');
	if (line[0] == 'L')
		ft_error(data, "invalid room name");
	while (split[data->var.i])
		data->var.i++;
	if (data->var.i == 1)
	{
		free_split(split);
		return (true);
	}
	if (data->var.i != 3)
		ft_error(data, "invalid third argument");
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

void	parse_room_dop(t_lemin *data, t_room *room)
{
	free(data->var.line);
	append_room(data, room);
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
			ft_error(data, "invalid data");
		printf("%s\n", data->var.line);
	}
	else
		room->is_inter = true;
	if (!parse_coords_room(data, room, data->var.line))
		parse_room_dop(data, room);
	else
	{
		free(room);
		parse_links(data);
	}
}
