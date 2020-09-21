/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 13:24:31 by cnails            #+#    #+#             */
/*   Updated: 2020/09/06 13:25:21 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	init(t_lemin *data)
{
	data->rooms = NULL;
	data->qty_ants = 0;
	data->qty_links = 0;
	data->head_link = NULL;
	data->head = NULL;
	data->links = NULL;
	data->ants_in_road = 0;
	data->qty_paths = 0;
	data->print_paths = false;
	data->ant_id = 1;
}

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
	room->ant_id = 0;
}
