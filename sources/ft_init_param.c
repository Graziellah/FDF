/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghippoda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 19:22:37 by ghippoda          #+#    #+#             */
/*   Updated: 2017/02/20 19:19:53 by ghippoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		mlx_change(t_info *i)
{
	mlx_destroy_image(i->mlx, i->img);
	i->img = mlx_new_image(i->mlx, HEIGHT, HEIGHT);
	i->data = mlx_get_data_addr(i->img, &(i->bpp), &(i->szline), &(i->endian));
	ft_fill_map(i);
	mlx_put_image_to_window(i->mlx, i->win, i->img, 0, 0);
}

int			my_key_func(int keycode, t_info *i)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(i->mlx, i->img);
		mlx_destroy_window(i->mlx, i->win);
		exit(0);
	}
	if (keycode == ZOOM_M)
		i->zoom /= 0.8;
	if (keycode == ZOOM_P && i->zoom > i->zoom_max)
		i->zoom *= 0.8;
	if (keycode == RIGHT)
		i->move_x += 10;
	if (keycode == LEFT)
		i->move_x -= 10;
	if (keycode == UP)
		i->move_y -= 10;
	if (keycode == DOWN)
		i->move_y += 10;
	if (keycode == I)
		i->proj = ISO;
	if (keycode == P)
		i->proj = PARA;
	mlx_change(i);
	return (0);
}

void		ft_init_map(int **tmp, t_map *map, t_info *i)
{
	map->tab = tmp;
	i->map = map;
	i->win = mlx_new_window(i->mlx, HEIGHT, WIDTH, "fdf");
	i->img = mlx_new_image(i->mlx, HEIGHT, WIDTH);
	i->data = mlx_get_data_addr(i->img, &(i->bpp), &(i->szline), &(i->endian));
	i->move_x = MOVE_X;
	i->move_y = MOVE_Y;
	i->proj = PARA;
	i->zoom = ZOOM;
}

int			ft_mouse_hook(int button, int x, int y, t_info *i)
{
	if (button == 1)
	{
		i->move_x = x;
		i->move_y = y;
	}
	mlx_change(i);
	return (0);
}

int			ft_init_param(int **tab, t_map *map)
{
	t_info	i;

	if (!(i.mlx = mlx_init()))
		return (0);
	ft_init_map(tab, map, &i);
	while ((map->j + map->i) * i.zoom > 2400)
		i.zoom = (int)(0.95 * (double)i.zoom);
	i.zoom_max = i.zoom;
	ft_fill_map(&i);
	mlx_mouse_hook(i.win, ft_mouse_hook, &i);
	mlx_key_hook(i.win, my_key_func, &i);
	mlx_hook(i.win, KEYPRESS, KEYPRESSMASK, my_key_func, &i);
	mlx_put_image_to_window(i.mlx, i.win, i.img, 0, 0);
	mlx_loop(i.mlx);
	return (0);
}
