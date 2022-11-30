/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:46:45 by lpupier           #+#    #+#             */
/*   Updated: 2022/11/30 14:49:05 by lpupier          ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	char		*stash;
	static char	buffer[BUFFER_SIZE + 1];
	ssize_t		nb_byte_read;

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
	nb_byte_read = BUFFER_SIZE;
	while (!check_separator(stash) && nb_byte_read > 0)
	{
		nb_byte_read = read(fd, buffer, BUFFER_SIZE);
		buffer[nb_byte_read] = '\0';
		stash = ft_strjoin(stash, buffer, nb_byte_read);
	}
	clean_buffer(buffer);
	if (!stash[0])
	{
		free(stash);
		return (NULL);
	}
	return (recover_before_separator(stash));
}
