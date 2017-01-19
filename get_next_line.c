/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vportell <vportell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 14:49:24 by vportell          #+#    #+#             */
/*   Updated: 2016/11/29 14:48:05 by vportell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_file(t_file **file, t_file *temp, char **line)
{
	int		i;
	t_file	*prev;
	t_file	*curr;

	i = 0;
	*line = ft_strdup("");
	curr = *file;
	prev = *file;
	while (curr)
	{
		if (curr == temp)
			break ;
		prev = curr;
		curr = curr->next;
	}
	if (prev == curr)
		*file = curr->next;
	else if (curr->next)
		prev->next = curr->next;
	else if (!(curr->next))
		prev->next = NULL;
	ft_strdel(&(temp->str));
	free(curr);
}

t_file	*create_file(int fd)
{
	t_file *file;

	file = (t_file *)malloc(sizeof(t_file));
	file->fd = fd;
	file->s = 0;
	file->str = 0;
	file->next = NULL;
	return (file);
}

t_file	*get_file(t_file **file, int fd)
{
	t_file	*temp;

	if (*file)
	{
		temp = *file;
		while (temp->next)
		{
			if (temp->fd == fd)
				break ;
			temp = temp->next;
		}
		if (!(temp->next) && temp->fd != fd)
			temp->next = create_file(fd);
	}
	else
		*file = create_file(fd);
	temp = *file;
	while (temp)
	{
		if (temp->fd == fd)
			break ;
		temp = temp->next;
	}
	return (temp);
}

int		read_str(char **str, const int fd, int i)
{
	int		count;
	char	*temp;
	char	*buf;

	temp = 0;
	if (*str)
		return (0);
	buf = ft_strnew(BUFF_SIZE);
	while ((count = read(fd, buf, BUFF_SIZE)) > -1)
	{
		if (*str)
		{
			i = ft_strlen(*str);
			temp = ft_strsub(*str, 0, i);
			ft_strdel(str);
		}
		*str = ft_strnew(count + i + 1);
		temp ? ft_strcpy(*str, temp) : temp;
		ft_strncat(*str, buf, count);
		ft_strdel(&temp);
		count < 1 ? ft_strdel(&buf) : 0;
		if (count < 1)
			return (0);
	}
	return (-1);
}

int		get_next_line(const int fd, char **line)
{
	int				i;
	int				c;
	int				error;
	t_file			*t;
	static t_file	*file;

	c = 0;
	t = get_file(&file, fd);
	if (fd < 0 || line == NULL || (error = read_str(&(t->str), fd, c)) < 0)
		return (-1);
	if (t->s < (int)ft_strlen(t->str))
	{
		i = t->s - 1;
		while ((t->str)[++i])
			if ((t->str)[i] == '\n' && (c = 1))
				break ;
		if (i > 0 && (t->str)[i - 1] != 0 && (t->str)[i] == 0)
			c = 1;
		*line = (!(i - t->s)) ? ft_strdup("") :
		ft_strsub(t->str, t->s, i - t->s);
		t->s = i + 1;
	}
	else
		free_file(&file, t, line);
	return (c);
}
