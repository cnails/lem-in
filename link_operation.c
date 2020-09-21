/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 22:44:00 by cnails            #+#    #+#             */
/*   Updated: 2020/09/21 12:32:55 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		set_directions(t_lemin *data)
{
	t_link *head;
	t_room *tmp;

	head = data->head_link;
	while (head)
	{
		if (head->prev_room->bfs > head->next_room->bfs)
		{
			tmp = head->next_room;
			head->next_room = head->prev_room;
			head->prev_room = tmp;
		}
		head = head->next;
	}
}

void		count_inp_out(t_lemin *data, size_t nbr)
{
	t_link *head;

	head = data->head_link;
	data->var.is_true = false;
	while (head)
	{
		if (!head->is_unusefull)
		{
			head->prev_room->output += nbr;
			head->next_room->input += nbr;
			if (head->next_room->is_end)
				data->var.is_true = true;
		}
		head = head->next;
	}
	if (!data->var.is_true)
		ft_error(data, "no way");
}
