/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dessin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghippoda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:57:04 by ghippoda          #+#    #+#             */
/*   Updated: 2017/10/19 20:18:08 by ghippoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	mlx_pixel_put_to_image(t_info *i, int x, int y, int color)
{
	int		size;

	if (x >= HEIGHT || y >= WIDTH || x <= 0 || y <= 0)
		return ;
	if (i->endian == 0)
	{
		size = ((y * i->szline) + (x * i->bpp / 8));
		i->data[size] = mlx_get_color_value(i->mlx, color);
		i->data[size + 1] = mlx_get_color_value(i->mlx, color >> 8);
		i->data[size + 2] = mlx_get_color_value(i->mlx, color >> 16);
	}
	else
	{
		size = ((y * i->szline) + (x * i->bpp / 8));
		i->data[size] = mlx_get_color_value(i->mlx, color >> 16);
		i->data[size + 1] = mlx_get_color_value(i->mlx, color >> 8);
		i->data[size + 2] = mlx_get_color_value(i->mlx, color);
	}
}

void		ft_draw_line_if(t_info *i, t_coord pos, t_coord dif, t_coord inc)
{
	int		add;
	int		j;
	int		color;

	j = 1;
	add = dif.x / 2;
	color = pos.color;
	while (j <= dif.x)
	{
		pos.x += inc.x;
		add += dif.y;
		if (add >= dif.x)
		{
			add -= dif.x;
			pos.y += inc.y;
		}
		mlx_pixel_put_to_image(i, pos.x + i->move_x, pos.y + i->move_y, color);
		j++;
	}
}

void		ft_draw_line_else(t_info *i, t_coord pos, t_coord dif, t_coord inc)
{
	int		add;
	int		j;
	int		color;

	add = dif.y / 2;
	j = 1;
	color = pos.color;
	while (j <= dif.y)
	{
		pos.y += inc.y;
		add += dif.x;
		if (add >= dif.y)
		{
			add -= dif.y;
			pos.x += inc.x;
		}
		mlx_pixel_put_to_image(i, pos.x + i->move_x, pos.y + i->move_y, color);
		j++;
	}
}

void		ft_draw_line(t_info *i, t_coord a, t_coord b)
{
	t_coord		pos;
	t_coord		dif;
	t_coord		inc;
	int			color;

	pos.x = a.x;
	pos.y = a.y;
	pos.z = a.z;
	pos.color = a.color;
	dif.x = b.x - a.x;
	dif.y = b.y - a.y;
	dif.z = b.z;
	inc.x = (dif.x > 0) ? 1 : -1;
	inc.y = (dif.y > 0) ? 1 : -1;
	dif.x = abs(dif.x);
	dif.y = abs(dif.y);
	color = a.color;
	if (dif.x > dif.y)
		ft_draw_line_if(i, pos, dif, inc);
	else
		ft_draw_line_else(i, pos, dif, inc);
}

t_coord		proj_para(t_coord a)
{
	t_coord c;
	float	cst1;
	float	cst2;

	cst1 = 0.5;
	cst2 = 0.5;
	if (a.proj == 1)
	{
		cst1 = 0.8;
		c.x = a.x + cst1 * a.z;
		c.y = a.y + (cst1 / 2) * a.z;
		return (c);
	}
	else
	{
		c.x = cst1 * a.x - cst2 * a.y;
		c.y = a.z + (cst1 / 2) * a.x + (cst2 / 2) * a.y;
		return (c);
	}
}
