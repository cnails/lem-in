/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 13:17:09 by cnails            #+#    #+#             */
/*   Updated: 2020/09/21 12:32:55 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_link	*find_link(t_lemin *data, t_room *room)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		if (head->prev_room == room)
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_link	*find_link_by_len(t_lemin *data, int len)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		if (head->length == len && !head->is_used)
		{
			head->is_used = true;
			return (head);
		}
		head = head->next;
	}
	return (NULL);
}

t_room	*find_room(t_lemin *data, char *name)
{
	t_room *head;

	head = data->head;
	while (head)
	{
		if (ft_strsim(head->name, name))
			return (head);
		head = head->next;
	}
	ft_error(data, "links error");
	return (NULL);
}
