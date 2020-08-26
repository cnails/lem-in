/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 18:26:23 by cnails            #+#    #+#             */
/*   Updated: 2020/08/26 19:25:38 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		validate_bfs(t_lemin *data)
{
	t_room *head;

	head = data->head;
	while (head)
	{
		if (!(head->bfs || head->is_start))
			return (0);
		head = head->next;
	}
	return (1);
}

void	condition_check(t_lemin *data, t_link *head)
{
	if (((head->prev_room->bfs && (!head->next_room->bfs\
		|| head->prev_room->bfs < head->next_room->bfs)) ||\
		head->prev_room->is_start) && !head->next_room->is_start &&\
		!head->prev_room->is_end)
		head->next_room->bfs = head->prev_room->bfs + 1;
	if (((head->next_room->bfs && (!head->prev_room->bfs\
	|| head->next_room->bfs < head->prev_room->bfs)) ||\
	head->next_room->is_start) && !head->prev_room->is_start &&\
	!head->next_room->is_end)
		head->prev_room->bfs = head->next_room->bfs + 1;
	if (head->prev_room->bfs && head->next_room->is_end)
		data->var.is_true = true;
	if (head->next_room->is_end)
		head->next_room->bfs = INT_MAX;
	if (head->prev_room->is_end)
		head->prev_room->bfs = INT_MAX;
}

void	bfs(t_lemin *data)
{
	t_link *head;

	data->var.is_true = false;
	data->var.x = 0;
	while (data->var.x < (data->qty_links + 1))
	{
		data->var.x++;
		head = data->head_link;
		while (head)
		{
			condition_check(data, head);
			head = head->next;
		}
		if (validate_bfs(data))
			break ;
	}
	if (!data->var.is_true)
		ft_error("no way");
}
