/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 03:23:55 by ssoeno            #+#    #+#             */
/*   Updated: 2024/05/16 03:25:27 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1 
# endif
# if BUFFER_SIZE <= 0
#  error BUFFER_SIZE must be > 0
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_gnl_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t nmemb, size_t size);

#endif