/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghippoda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 20:41:44 by ghippoda          #+#    #+#             */
/*   Updated: 2017/02/01 14:52:49 by ghippoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_len(char *buf)
{
	int		i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

t_stock		*ft_fdsearch(int fd, t_stock **stock)
{
	if (!*stock)
	{
		if ((*stock = (t_stock*)malloc(sizeof(t_stock))) == NULL)
			return (NULL);
		(*stock)->fd = fd;
		(*stock)->res = "";
		(*stock)->next = NULL;
		return (*stock);
	}
	if ((*stock)->fd == fd)
		return (*stock);
	return (ft_fdsearch(fd, &((*stock)->next)));
}

void		ft_backslash(char **line, t_stock *memo)
{
	memo->res = ft_strsub(*line, (ft_len(*line) + 1),
			(ft_strlen(*line) - ft_len(*line)));
	*line = ft_strsubf(*line, 0, ft_len(*line));
}

int			get_next_line(const int fd, char **line)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	t_stock			*memo;
	static t_stock	*stock = NULL;

	if (fd < 0 || !line)
		return (-1);
	memo = ft_fdsearch(fd, &stock);
	ret = 1;
	*line = ft_strjoin(memo->res, "");
	while (ret && ft_len(*line) == -1)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		*line = ft_strjoinf(*line, buf);
	}
	if (ft_len(*line) != -1)
		ft_backslash(line, memo);
	else
		memo->res = "";
	return ((ft_strcmp(*line, "") == 0 && ft_strcmp(memo->res, "") == 0 &&
				ret == 0) ? 0 : 1);
}
