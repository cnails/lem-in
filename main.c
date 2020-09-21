/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 11:55:09 by cnails            #+#    #+#             */
/*   Updated: 2020/09/21 13:17:09 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_error(t_lemin *data, char *str)
{
	if (data->print_errors)
	{
		printf("ERROR: %s\n", str);
	}
	else
		printf("ERROR\n");
	exit(1);
}

void		free_links(t_lemin *data)
{
	t_link	*link;

	while (data->head_link)
	{
		link = data->head_link->next;
		free(data->head_link);
		data->head_link = link;
	}
}

void		free_rooms(t_lemin *data)
{
	t_room	*room;

	while (data->head)
	{
		room = data->head->next;
		free(data->head->name);
		free(data->head);
		data->head = room;
	}
}

void		print_help(void)
{
	printf("\n\033[0;32m\t\t\tHELP\033[0m\n\n");
	printf("\033[0;35m-e\033[0m\tDetailed error description\n");
	printf("\033[0;35m-p\033[0m\tRemaining paths\n");
	printf("\033[0;35m-c\033[0m\tCount of paths\n");
}

/*

CODE	COLOR
[0;31m	Red
[1;31m	Bold Red
[0;32m	Green
[1;32m	Bold Green
[0;33m	Yellow
[01;33m	Bold Yellow
[0;34m	Blue
[1;34m	Bold Blue
[0;35m	Magenta
[1;35m	Bold Magenta
[0;36m	Cyan
[1;36m	Bold Cyan
[0m	Reset

*/

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
			data->print_help = true;
		else
			data->print_unknown = str[i];
		i++;
	}
}

void flags(t_lemin *data)
{
	if (data->print_count)
		printf("\n\033[0;33mCount of paths: \033[0;32m%zu\033[0m\n", data->var.i);
	if (data->print_paths)
		print_paths(data);
	if (data->print_unknown)
	{
		printf("\n\033[0;31m!UNKNOWN command \"%c\"\033[0m\nPlease read HELP\n",
				data->print_unknown);
		print_help();
	}
	else if (data->print_help)
		print_help();
}

void free_all(t_lemin *data)
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
	{
		if (av[1][0] == '-')
			parse_flags(data, av[1]);
	}
	// TODO: validaciya - coords can be only INT
	parse_ants(data);
	bfs(data);
	delete_same_bfs(data);
	set_directions(data);
	count_inp_out(data, 1);
	while (delete_dead_links(data))
		count_inp_out(data, 0);
	inp_forks(data);
	count_paths(data);
	printf("\n");
	alg(data);
	flags(data);
	free_all(data);
	return (0);
}
