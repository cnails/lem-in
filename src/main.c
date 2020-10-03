/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 11:55:09 by cnails            #+#    #+#             */
/*   Updated: 2020/09/23 12:42:23 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		parse_flags(t_lemin *data, char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'e')
			data->print_errors = true;
		else if (str[i] == 'p')
			data->print_paths = true;
		else if (str[i] == 'c')
			data->print_count = true;
		else if (str[i] == 'h')
			print_help();
		else if (str[i] == 'a')
			data->print_count_ants = true;
		else
			data->print_unknown = str[i];
		i++;
	}
}

void		flags(t_lemin *data)
{
	if (data->print_count)
		ft_printf("\n\033[0;33mCount of paths: \033[0;32m%d\033[0m\n",
				data->qty_paths);
	if (data->print_paths)
		print_paths(data);
	if (data->print_unknown)
	{
		ft_printf("\n\033[0;31m!UNKNOWN cmd \"%c\"\033[0m\nPlease read HELP\n",
				data->print_unknown);
		print_help();
	}
}

void		free_all(t_lemin *data)
{
	free_rooms(data);
	free_links(data);
	free(data->paths);
	free(data);
}

int			main(int ac, char **av)
{
	t_lemin	*data;

	data = (t_lemin *)ft_memalloc(sizeof(t_lemin));
	init(data);
	if (ac >= 2)
		if (av[1][0] == '-')
			parse_flags(data, av[1]);
	parse_ants(data);
	bfs(data);
	delete_same_bfs(data);
	set_directions(data);
	count_inp_out(data, 1);
	while (delete_dead_links(data))
		count_inp_out(data, 0);
	inp_forks(data);
	count_paths(data);
	ft_printf("\n");
	alg(data);
	flags(data);
	free_all(data);
	return (0);
}
