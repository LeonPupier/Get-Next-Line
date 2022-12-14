/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:47:07 by lpupier           #+#    #+#             */
/*   Updated: 2022/12/01 10:27:35 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	idx;
	char	*new_s1;

	len = ft_strlen(s1);
	idx = 0;
	new_s1 = malloc(sizeof(char) * (len + 1));
	if (!new_s1)
		return (NULL);
	while (idx < len)
	{
		new_s1[idx] = s1[idx];
		idx++;
	}
	new_s1[idx] = '\0';
	return (new_s1);
}

static int	loop_join(char *new_str, char *s1, char *s2, size_t idx_max)
{
	size_t	count;
	size_t	count_s2;
	size_t	len_s1;

	len_s1 = ft_strlen(s1);
	count = 0;
	while (count < len_s1)
	{
		new_str[count] = s1[count];
		count++;
	}
	count_s2 = 0;
	while (count_s2 < idx_max)
	{
		new_str[count] = s2[count_s2];
		count_s2++;
		count++;
	}
	return (count);
}

char	*ft_strjoin(char *s1, char *s2, size_t idx_max)
{
	size_t	count;
	size_t	len_s1;
	char	*new_str;

	len_s1 = ft_strlen(s1);
	new_str = malloc(sizeof(char) * (len_s1 + BUFFER_SIZE + 1));
	if (new_str == NULL)
	{
		free(s1);
		return (NULL);
	}
	count = loop_join(new_str, s1, s2, idx_max);
	free(s1);
	new_str[count] = '\0';
	return (new_str);
}

static char	*allocate_new_str(char *str, int idx)
{
	char	*new_str;

	if (str[idx])
		new_str = malloc(sizeof(char) * (idx + 2));
	else
		new_str = malloc(sizeof(char) * (idx + 1));
	if (new_str == NULL)
		return (NULL);
	return (new_str);
}

char	*recover_before_separator(char *str)
{
	char	*new_str;
	int		idx;

	if (!str)
		return (NULL);
	idx = 0;
	while (str[idx] && str[idx] != '\n')
		idx++;
	new_str = allocate_new_str(str, idx);
	if (new_str == NULL)
		return (free(str), NULL);
	idx = 0;
	while (str[idx] && str[idx] != '\n')
	{
		new_str[idx] = str[idx];
		idx++;
	}
	if (str[idx])
	{
		new_str[idx] = '\n';
		new_str[idx + 1] = '\0';
	}
	else
		new_str[idx] = '\0';
	return (free(str), new_str);
}
