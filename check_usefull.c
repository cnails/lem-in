/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_usefull.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 14:01:29 by cnails            #+#    #+#             */
/*   Updated: 2020/08/23 22:30:07 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	dont work :(
*/

void	delete_unusefull(t_lemin *data, t_link *tmp)
{
	t_link *head;
	t_link *prev;

	// printf("del link %s(%d)(%d)-%s\n", tmp->prev_room->name, tmp->prev_room->input, tmp->prev_room->output, tmp->next_room->name);
	prev = NULL;
	head = data->head_link;
	while (head && head != tmp)
	{
		prev = head;
		head = head->next;
	}
	if (!prev && head)
		data->head_link = head->next;
	else if (head)
		prev->next = head->next;
	if (tmp->prev_room->output > 0)
		tmp->prev_room->output--;
	if (tmp->next_room->input > 0)
		tmp->next_room->input--;
	free(tmp);
	tmp = NULL;
}

void	delete_same_bfs(t_lemin *data)
{
	t_link *head;
	t_link *next;

	head = data->head_link;
	while (head->next)
	{
		next = head->next;
		if (head->next_room->bfs == head->prev_room->bfs)
			delete_unusefull(data, head);
		else if (!head->next_room->bfs && !head->next_room->is_start)
			delete_unusefull(data, head);
		else if (!head->prev_room->bfs && !head->prev_room->is_start)
			delete_unusefull(data, head);
		head = next;
	}
}

void	del_dead_link(t_lemin *data, t_room *room)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		if (head->next_room == room)
		{
			if (head->prev_room->output == 1)
				del_dead_link(data, head->prev_room);
			delete_unusefull(data, head);
			break;
		}
		head = head->next;
	}
}

int		delete_dead_links(t_lemin *data)
{
	t_link	*head;
	t_link	*next;
	int		flag;

	flag = 0;
	head = data->head_link;
	while (head)
	{
		next = head->next;
		if (!head->next_room->output && !head->next_room->is_end)
		{
			if (head->prev_room->output == 1)
				del_dead_link(data, head->prev_room);
			delete_unusefull(data, head);
			flag = 1;
		}
		head = next;
	}
	return (flag);
}
