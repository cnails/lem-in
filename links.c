/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 19:53:06 by cnails            #+#    #+#             */
/*   Updated: 2020/05/27 23:14:27 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	similar_links(t_lemin *data, t_link *link)
{
	t_link *head;

	head = data->head_link;
	while (head)
	{
		if (!head->is_used)
			if ((ft_strsim(link->next_room->name, head->next_room->name) &&\
					ft_strsim(link->prev_room->name, head->prev_room->name))\
					|| (ft_strsim(link->prev_room->name, head->next_room->name)\
					&& ft_strsim(link->next_room->name, head->prev_room->name)))
				ft_error("similar links\n");
		head = head->next;
	}
}

void	validate_links(t_lemin *data)
{
	t_link	*link;

	link = data->head_link;
	while (link)
	{
		link->is_used = true;
		similar_links(data, link);
		link->is_used = false;
		link = link->next;
	}
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
	ft_error("links error");
}

void	links_connection(t_lemin *data, char **line)
{
	t_link *link;

	link = (t_link *)ft_memalloc(sizeof(t_link));
	link->prev_room = find_room(data, line[0]);
	link->next_room = find_room(data, line[1]);
	link->is_used = false;
	link->is_unusefull = false;
	data->qty_links++;
	if (ft_strsim(link->prev_room->name, link->next_room->name))
		ft_error("link error\n");
	if (!data->links)
	{
		data->links = link;
		data->head_link = data->links;
	}
	else
	{
		data->links->next = link;
		data->links = data->links->next;
	}
}

void	split_link(t_lemin *data)
{
	char **split;

	split = ft_strsplit(data->var.line, '-');
	data->var.i = 0;
	while (split[data->var.i])
		data->var.i++;
	if (data->var.i != 2)
		ft_error("parse links\n");
	links_connection(data, split);
	free_split(split);
}

int		parse_links(t_lemin *data)
{
	split_link(data);
	free(data->var.line);
	while (get_next_line(0, &data->var.line))
	{
		if (!(data->var.line[0] == '#'))
			split_link(data);
		free(data->var.line);
	}
	validate_links(data);
	return (0);
}
