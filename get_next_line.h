/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vportell <vportell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 14:49:33 by vportell          #+#    #+#             */
/*   Updated: 2016/11/28 17:03:47 by vportell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"

# define BUFF_SIZE 8

typedef struct		s_file
{
	int				fd;
	int				s;
	char			*str;
	struct s_file	*next;
}					t_file;

int					get_next_line(const int fd, char **line);

#endif
