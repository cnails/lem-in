/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 12:42:43 by cnails            #+#    #+#             */
/*   Updated: 2020/08/17 22:25:26 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	parse_ants(t_lemin *data)
{
	while (get_next_line(0, &data->var.line))
	{
		printf("%s\n", data->var.line);
		if (ft_isdigit(data->var.line[0]))
		{
			data->qty_ants = ft_atoi(data->var.line);
			free(data->var.line);
			break ;
		}
		else if (data->var.line[0] == '#')
		{
			free(data->var.line);
			continue;
		}
		else
			ft_error("parse_ants");
		free(data->var.line);
	}
	// printf("qty ants = %d\n", data->qty_ants);
	ft_parse(data);
}

void		ft_parse(t_lemin *data)
{
	bool	start;
	bool	end;

	start = false;
	end = false;
	while (get_next_line(0, &data->var.line))
	{
		printf("%s\n", data->var.line);
		if (!ft_strcmp("##start", data->var.line))
		{
			parse_room(data, true, false);
			start = true;
		}
		else if (!ft_strcmp("##end", data->var.line))
		{
			parse_room(data, false, true);
			end = true;
		}
		else if (data->var.line[0] == '#')
			free(data->var.line);
		else
			parse_room(data, false, false);
	}
	if (!(start && end))
		ft_error("missing start or end\n");
	if (!data->head_link)
		ft_error("0 link\n");
}
