/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 13:03:01 by cnails            #+#    #+#             */
/*   Updated: 2020/09/06 13:29:42 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		count_sum(t_lemin *data, t_link *link)
{
	t_link	**head;
	int		sum;
	int		i;

	sum = 0;
	i = 0;
	head = data->paths;
	while (head[i] != link)
	{
		if (head[i]->length > 0)
			sum += link->length - head[i]->length;
		i++;
	}
	return (sum);
}

void	move_ants_dop_func(t_lemin *data)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		if (head->ant_id && !head->next_room->ant_id)
		{
			head->next_room->ant_id = head->ant_id;
			head->ant_id = 0;
		}
		head = head->next;
	}
}

void	check_move_ants(t_lemin *data, t_link *head)
{
	if (!head->next_room->is_end)
		head->next_room->ant_id = head->prev_room->ant_id;
	head->next_room->is_used = true;
	print_step(head->next_room, head->prev_room->ant_id);
	head->prev_room->ant_id = 0;
	if (head->next_room->is_end)
		data->ants_in_road--;
}

void	move_ants(t_lemin *data)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		if (head->prev_room->ant_id && !head->length &&\
		!head->prev_room->is_used)
		{
			if (!head->ant_id)
				if (head->next_room->ant_id)
				{
					head->ant_id = head->prev_room->ant_id;
					print_step(head->next_room,\
					head->prev_room->ant_id);
					head->prev_room->ant_id = 0;
					if (head->next_room->is_end)
						data->ants_in_road--;
				}
			if (!head->next_room->ant_id)
				check_move_ants(data, head);
		}
		head = head->next;
	}
	move_ants_dop_func(data);
}

void	move_ants_from_start(t_lemin *data)
{
	t_link **paths;

	paths = data->paths;
	data->var.x = 0;
	while ((int)data->var.x < data->qty_paths && data->qty_ants)
	{
		if (data->qty_ants > count_sum(data, paths[data->var.x]) &&\
		paths[data->var.x]->length >= 0)
		{
			make_step(data, paths[data->var.x]);
		}
		data->var.x++;
	}
}
