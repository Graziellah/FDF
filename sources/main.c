/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghippoda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 03:29:30 by ghippoda          #+#    #+#             */
/*   Updated: 2017/10/21 21:29:26 by ghippoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		ft_check_number(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_control(void)
{
	ft_putstr("Controls:\n-----------\n");
	ft_putstr("P = Parallel projection\nI = Isometric projection\n");
	ft_putstr("UP = Move right \nDOWN = Move down\nLEFT = Move left\n");
	ft_putstr("RIGHT = Move right\n+ = Zoom +\n- = Zoom -\n");
	ft_putstr("MOUSE = Move map on cursor\n");
}

void	ft_init_tmp(t_map *tmp)
{
	tmp->tab = NULL;
	tmp->i = 0;
	tmp->j = 0;
}

char	**ft_split_by_gnl(int fd, t_map *tmp, char *av)
{
	char	**tab;
	char	*str;
	int		i;
	int		test;

	i = 0;
	str = "";
	while ((test = get_next_line(fd, &str)))
	{
		if (test == -1)
			return (0);
		tmp->i++;
	}
	close(fd);
	fd = open(av, O_RDONLY);
	if (!(tab = (char**)malloc(sizeof(char*) * (tmp->i + 1))))
		return (0);
	while (get_next_line(fd, &str))
	{
		tab[i] = str;
		i++;
	}
	tab[i] = NULL;
	close(fd);
	return (tab);
}

int		main(int ac, char **av)
{
	int		**map;
	int		fd;
	char	**tab;
	t_map	tmp;

	ft_init_tmp(&tmp);
	fd = open(av[1], O_RDONLY);
	if (ac != 2 || fd < 0 || !(tab = ft_split_by_gnl(fd, &tmp, av[1])))
	{
		ft_putstr("Error\n");
		return (0);
	}
	tmp.i = ft_count_tab(tab);
	map = ft_creatmap(tab, &tmp);
	if (!map)
	{
		ft_putstr("Map error line\n");
		return (0);
	}
	ft_control();
	if (ft_init_param(map, &tmp) != 0)
		return (0);
	return (0);
}
