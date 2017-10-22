/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghippoda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 19:30:23 by ghippoda          #+#    #+#             */
/*   Updated: 2017/10/12 16:44:54 by ghippoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void		ft_view(t_coord a, t_coord b, t_info *i)
{
	a.color = ft_color(a, b);
	if (i->proj == 2)
	{
		a.x *= i->zoom;
		a.y *= i->zoom;
		b.x *= i->zoom;
		b.y *= i->zoom;
		a.z *= i->zoom / -4;
		b.z *= i->zoom / -4;
	}
	else
	{
		a.x *= i->zoom / 2;
		a.y *= i->zoom / 2;
		b.x *= i->zoom / 2;
		b.y *= i->zoom / 2;
		a.z *= i->zoom / -6;
		b.z *= i->zoom / -6;
	}
	a = proj_para(a);
	b = proj_para(b);
	ft_draw_line(i, a, b);
}

static void		fill_coord(t_coord *a, int x, int y, int z)
{
	a->x = x;
	a->y = y;
	a->z = z;
}

t_coord			init_t_coord1(int proj)
{
	t_coord		a;

	a.x = -1;
	a.y = -1;
	a.z = -1;
	a.proj = proj;
	a.color = 0x00FF0000;
	return (a);
}

void			ft_check_point(t_coord *a, t_coord *b, t_coord *c, t_info *i)
{
	if ((i->x + 1) < i->map->j)
	{
		fill_coord(b, i->x + 1, i->y, i->map->tab[i->y][i->x + 1]);
		ft_view(*a, *b, i);
	}
	if ((i->y + 1) < i->map->i)
	{
		fill_coord(c, i->x, i->y + 1, i->map->tab[i->y + 1][i->x]);
		ft_view(*a, *c, i);
	}
}

void			ft_fill_map(t_info *info)
{
	t_coord		a;
	t_coord		b;
	t_coord		c;

	info->x = 0;
	a = init_t_coord1(info->proj);
	b = init_t_coord1(info->proj);
	c = init_t_coord1(info->proj);
	while (info->x < info->map->j)
	{
		info->y = 0;
		while (info->y < info->map->i)
		{
			fill_coord(&a, info->x, info->y, info->map->tab[info->y][info->x]);
			ft_check_point(&a, &b, &c, info);
			info->y++;
		}
		info->x++;
	}
}
