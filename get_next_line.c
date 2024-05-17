/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:02:36 by ssoeno            #+#    #+#             */
/*   Updated: 2024/05/17 18:41:00 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdbool.h>

static char	*free_and_nullize(char **p)
{
	free(*p);
	*p = NULL;
	return (NULL);
}

static bool	pack(char **basin, char *cup)
{
	char	*bk;

	if (*basin == NULL)
		*basin = ft_substr(cup, 0, ft_strlen(cup));
	else
	{
		bk = *basin; //ft_strjoin(*basin, s) が新しいメモリ領域を確保
		//*basin と s を連結した新しい文字列をその領域に格納
		//*basin はこの新しいメモリアドレスに更新される。
		*basin = ft_strjoin(*basin, cup); //basinのnull終端の後ろに連結していく
		free(bk); //旧アドレスをfree
	}
	return (*basin != NULL); //メモリ確保に成功したか
}

static bool	read_from_file(char **basin, int fd)
{
	char	cup[BUFFER_SIZE + 1];
	ssize_t	rv;

	//basinがNULLの場合(初回読み込み時)or 改行がない時ループに入る。
	while (!*basin || !ft_strchr(*basin, '\n'))
	{
		rv = read(fd, cup, BUFFER_SIZE);
		if (rv < 0) //読み取り失敗
			return (false);
		if (rv == 0 && *basin == NULL) //何も読み込めていない
			return (false);
		cup[rv] = '\0';
		if (!(pack(basin, cup))) //packが失敗
			return (false);
		if (rv < BUFFER_SIZE);
			break; //fileの終わりに到達
	}
	return (true);
}

static char	*extract_line(char **basin)
{
	char	*p_endl;
	char	*p_nl;
	ssize_t	line_length;
	char	*basin_bk;
	char	*line;

	p_endl = ft_strchr(*basin, '\n');
	p_nl = *basin + ft_strlen(*basin);
	basin_bk = *basin; //basinのアドレスを一時保存
	*basin = NULL; //元のデータを指していたポインタを一時的にNULLに設定
	//新しいデータ（新しい行の開始位置）を *basinに割り当てる準備
	//誤って旧データにアクセスしてしまうのを防ぐ。
	if (!p_endl || p_endl + 1 == p_nl) //改行がない（EOF）or 改行の次がヌル終端
		line_length = p_endl - basin + 1;
	else
		line_length = ft_strlen(basin);
	line = (char *)malloc((line_length + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, basin, line_length + 1);
	if (line == NULL || *basin)
	line[line_length] = '\0';
	return (free(basin_bk), line);
}

static bool	*obtain_remaining(char **basin, char *cup)
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
	remaining = (char *)malloc((remaining_length + 1) * sizeof(char));
	if (remaining == NULL)
		return (free(basin), NULL);
	ft_strlcpy(remaining, endl + 1, remaining_length + 1);
	remaining[endl] ='\0';
	return (*basin != NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*static_basin;

	if(!read_from_file(&static_basin, fd))
		return (free_and_nullize(&static_basin));
	return (extract_line(&static_basin));
}

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