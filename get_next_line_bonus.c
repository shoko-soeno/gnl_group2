/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:02:36 by ssoeno            #+#    #+#             */
/*   Updated: 2024/05/16 03:23:29 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	if (!s)
		return (NULL);
	ch = (char)c;
	while (*s != ch)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char	*read_from_file(char *basin, int fd)
{
	char	*cup;
	ssize_t	red;

	if (!basin)
		basin = ft_calloc(1, sizeof(char));
	if (!basin)
		return (NULL);
	cup = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!cup)
		return (free(cup), free(basin), NULL);
	red = 1;
	while (!ft_strchr(basin, '\n') && red > 0)
	{
		red = read(fd, cup, BUFFER_SIZE);
		if (red < 0)
			return (free(cup), free(basin), NULL);
		cup[red] = '\0';
		basin = ft_gnl_strjoin(basin, cup);
		if (!basin)
			return (free(cup), free(basin), NULL);
	}
	free(cup);
	return (basin);
}

char	*extract_line(char *basin)
{
	char	*endl;
	ssize_t	line_length;
	char	*line;

	if (!*basin)
		return (NULL);
	endl = ft_strchr(basin, '\n');
	if (endl)
		line_length = endl - basin + 1;
	else
		line_length = ft_strlen(basin);
	line = (char *)ft_calloc(line_length + 1, sizeof(char));
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, basin, line_length + 1);
	return (line);
}

char	*obtain_remaining(char *basin)
{
	char	*endl;
	char	*remaining;
	int		remaining_length;

	endl = ft_strchr(basin, '\n');
	if (!endl)
		return (free(basin), NULL);
	remaining_length = ft_strlen(endl + 1);
	if (remaining_length == 0)
		return (free(basin), NULL);
	remaining = (char *)ft_calloc(remaining_length + 1, sizeof(char));
	if (remaining == NULL)
		return (free(basin), NULL);
	ft_strlcpy(remaining, endl + 1, remaining_length + 1);
	return (free(basin), remaining);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*basin[OPEN_MAX];

	basin[fd] = read_from_file(basin[fd], fd);
	if (!basin[fd])
		return (NULL);
	line = extract_line(basin[fd]);
	basin[fd] = obtain_remaining(basin[fd]);
	return (line);
}

// #if 0
// #include <stdio.h>
// #include <fcntl.h>
// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }
// int main(int ac, char **av)
// {
// 	int     fd;
// 	char    *next_line;
// 	int     count;
// 	(void)ac;
// 	count = 0;
// 	fd = open(av[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("%s", "Error opening file");
// 		return (1);
// 	}
// 	while (1)
// 	{
// 		next_line = get_next_line(fd);
// 		if (next_line == NULL)
// 			break ;
// 		count++;
// 		printf("[%d]:%s", count, next_line);
// 		free(next_line);
// 	close(fd);
// 		next_line = NULL;
// 	}
// 	fd = open(av[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("%s", "Error opening file");
// 		return (1);
// 	}
// 	while (1)
// 	{
// 		next_line = get_next_line(fd);
// 		if (next_line == NULL)
// 			break ;
// 		count++;
// 		printf("[%d]:%s", count, next_line);
// 		free(next_line);
// 		next_line = NULL;
// 	}
// 	close(fd);
// 	// system("leaks a.out");
// 	return (0);
// }
// void	*malloc(size_t n)
// {
// 	static int i = 0;
// 	++i;
// 	printf("%ith malloc(%zu)\n", i, n);
// 	if (i < N)
// 		return calloc(n, 1);
// 	return NULL;
// }
// void	free(void *p)
// {
// 	static int i = 0;
// 	++i;
// 	printf("%ith free(%p)\n", i, p);
// 	realloc(p, 0);
// }
// #endif