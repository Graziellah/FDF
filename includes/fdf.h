/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghippoda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 01:51:44 by ghippoda          #+#    #+#             */
/*   Updated: 2017/10/19 20:18:05 by ghippoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define HEIGHT 2000
# define WIDTH 2000
# define ZOOM 20
# define MOVE_X 200
# define MOVE_Y 200
# define PARA 1
# define ISO 2
# define RIGHT 124
# define LEFT 123
# define UP 126
# define DOWN 125
# define P 35
# define I 34
# define ESC 53
# define ZOOM_P 78
# define ZOOM_M 69
# define KEYPRESSMASK (1L<<0)
# define KEYPRESS 2
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>

typedef struct				s_coord
{
	int						x;
	int						y;
	int						z;
	int						proj;
	int						color;
}							t_coord;

typedef struct				s_map
{
	int						**tab;
	int						i;
	int						j;
}							t_map;

typedef struct				s_info
{
	void					*mlx;
	void					*win;
	void					*img;
	int						img_2_win;
	char					*data;
	int						bpp;
	int						endian;
	int						szline;
	int						proj;
	int						zoom;
	int						zoom_max;
	int						move_x;
	int						move_y;
	int						height;
	int						width;
	int						x;
	int						y;
	t_map					*map;
}							t_info;

int							ft_len(char *str);
int							ft_count_words(char *str, char c);
int							**ft_creatmap(char **tab, t_map *map);
int							ft_count_words2(char *str, int y);
int							ft_count_tab(char **tab);
t_coord						proj_para(t_coord a);
void						ft_draw_line(t_info *i, t_coord a, t_coord b);
int							ft_init_param(int **tab, t_map *map);
void						ft_fill_map(t_info *i);
int							ft_color(t_coord a, t_coord b);
#endif
