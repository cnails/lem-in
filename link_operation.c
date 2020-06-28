/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 22:44:00 by cnails            #+#    #+#             */
/*   Updated: 2020/06/28 14:07:27 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		print_room(t_lemin *data)
{
	t_room *head;

	head = data->head;
	while (head)
	{
		printf("%s input = %ld output = %ld\n", head->name, head->input, head->output);
		head = head->next;
	}
}

void		print_links(t_lemin *data)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		printf("%s->%s\n", head->prev_room->name, head->next_room->name);
		head = head->next;
	}
}

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

void		count_inp_out(t_lemin *data)
{
	t_link *head;

	head = data->head_link;
	data->var.is_true = false;
	while (head)
	{
		if (!head->is_unusefull)
		{
			head->prev_room->output++;
			head->next_room->input++;
			if (head->next_room->is_end)
				data->var.is_true = true;
		}
		head = head->next;
	}
	if (!data->var.is_true)
		ft_error("no way");
	// print_room(data);
}
