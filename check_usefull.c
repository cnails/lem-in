/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_usefull.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 14:01:29 by cnails            #+#    #+#             */
/*   Updated: 2020/05/25 18:24:53 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	delete_same_bfs(t_lemin *data)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		if (head->next_room->bfs == head->prev_room->bfs)
			head->is_ususefull = true;
		if (!head->next_room->bfs && !head->next_room->is_start)
			head->is_ususefull = true;
		if (!head->prev_room->bfs && !head->prev_room->is_start)
			head->is_ususefull = true;
		head = head->next;
	}
}
