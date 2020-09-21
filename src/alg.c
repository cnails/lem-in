/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 17:22:36 by cnails            #+#    #+#             */
/*   Updated: 2020/09/06 13:20:13 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	print_step(t_room *room, int ant_id)
{
	printf("L%d-%s ", ant_id, room->name);
}

void	clear_rooms(t_lemin *data)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		head->next_room->is_used = false;
		head->prev_room->is_used = false;
		head = head->next;
	}
}

int		calc_len(t_lemin *data, t_link *link)
{
	if (link == NULL)
		return (-9999999);
	if (link->next_room->is_end)
		return (1);
	return (1 + calc_len(data, find_link(data, link->next_room)));
}

void	alg(t_lemin *data)
{
	calc_len_paths(data);
	form_paths(data);
	while (data->qty_ants || data->ants_in_road)
	{
		clear_rooms(data);
		if (data->ants_in_road)
			move_ants(data);
		move_ants_from_start(data);
		printf("\n");
	}
}
