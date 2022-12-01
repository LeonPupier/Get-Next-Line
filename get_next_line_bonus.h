/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:45:31 by lpupier           #+#    #+#             */
/*   Updated: 2022/12/01 13:37:44 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

// Buffer size management
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

// Libraries
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

// Functions
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2, size_t idx_max);
void	*ft_memset(void *b, int c, size_t len);
char	*recover_before_separator(char *str);

void	ft_bzero(void *s, size_t n);

#endif