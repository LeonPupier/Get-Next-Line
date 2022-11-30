/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:46:45 by lpupier           #+#    #+#             */
/*   Updated: 2022/11/30 17:47:32 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	idx;

	idx = 0;
	while (s[idx])
		idx++;
	return (idx);
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
	while (!check_separator(stash) && nb_byte_read > 0)
	{
		nb_byte_read = read(fd, buffer, BUFFER_SIZE);
		buffer[nb_byte_read] = '\0';
		stash = ft_strjoin(stash, buffer, nb_byte_read);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*stash;
	static char	buffer[BUFFER_SIZE + 1];

	if (fd < 0 || read(fd, 0, 0) || BUFFER_SIZE <= 0)
	{
		buffer[0] = 0;
		return (NULL);
	}
	if (ft_strlen(buffer) > 0)
		stash = ft_strdup(buffer);
	else
	{
		stash = malloc(sizeof(char));
		if (stash == NULL)
			return (NULL);
		stash[0] = '\0';
	}
	stash = loop_gnl(fd, buffer, stash);
	clean_buffer(buffer);
	if (!stash[0])
	{
		free(stash);
		return (NULL);
	}
	return (recover_before_separator(stash));
}
