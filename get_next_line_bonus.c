/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:46:45 by lpupier           #+#    #+#             */
/*   Updated: 2022/12/01 13:56:12 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	idx;

	idx = 0;
	while (s[idx])
		idx++;
	return (idx);
}

static int	check_separator(char *str)
{
	int	idx;

	idx = 0;
	if (!str)
		return (0);
	while (str[idx])
	{
		if (str[idx] == '\n')
			return (1);
		idx++;
	}
	return (0);
}

static void	clean_buffer(char *buffer)
{
	size_t	idx;
	size_t	len_buffer;

	idx = 0;
	while (buffer[idx] && buffer[idx] != '\n')
		idx++;
	if (buffer[idx] == '\0')
	{
		buffer[0] = '\0';
		return ;
	}
	idx++;
	len_buffer = 0;
	while (buffer[idx + len_buffer])
	{
		buffer[len_buffer] = buffer[idx + len_buffer];
		len_buffer++;
	}
	buffer[len_buffer] = '\0';
}

static char	*loop_gnl(int fd, char *buffer, char *stash)
{
	ssize_t		nb_byte_read;

	nb_byte_read = BUFFER_SIZE;
	while (!check_separator(stash) && nb_byte_read > 0 && stash != NULL)
	{
		nb_byte_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_byte_read == -1)
		{
			buffer = 0;
			return (NULL);
		}
		buffer[nb_byte_read] = '\0';
		stash = ft_strjoin(stash, buffer, nb_byte_read);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*stash;
	static char	buffer[OPEN_MAX][BUFFER_SIZE + 1];

	if (fd < 0 || fd > OPEN_MAX || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (ft_bzero(buffer[fd], BUFFER_SIZE + 1), NULL);
	stash = malloc(sizeof(char));
	if (stash == NULL)
		return (NULL);
	stash[0] = '\0';
	if (ft_strlen(buffer[fd]) > 0)
		stash = ft_strjoin(stash, buffer[fd], ft_strlen(buffer[fd]));
	stash = loop_gnl(fd, buffer[fd], stash);
	if (stash == NULL)
		return (NULL);
	clean_buffer(buffer[fd]);
	if (!stash[0])
		return (free(stash), NULL);
	return (recover_before_separator(stash));
}
