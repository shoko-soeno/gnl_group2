/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:02:36 by ssoeno            #+#    #+#             */
/*   Updated: 2024/05/18 13:34:26 by ssoeno           ###   ########.fr       */
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
		bk = *basin;
		*basin = ft_strjoin(*basin, cup);
		free(bk);
	}
	return (*basin != NULL);
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
		if (rv < BUFFER_SIZE)
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

	if (!basin || !*basin)  // ポインタがNULLでないことを確認
		return NULL;
	p_endl = ft_strchr(*basin, '\n');
	if (p_endl)
		line_length = p_endl - *basin + 1;
	else
		line_length = ft_strlen(*basin);
	line = (char *)malloc((line_length + 1) * sizeof(char));
	line[line_length] = '\0';
	if (!line)
		return (NULL);
	ft_strlcpy(line, *basin, line_length + 1);
	if (p_endl)
	{
		if (*(p_endl + 1) == '\0')
			*basin = NULL; //改行の後に文字がなければNULLを設定
		else
			*basin = p_endl + 1; //改行の後に文字があればその開始位置を設定
	}
	else
	{
		*basin = NULL;//改行がなければNULLを設定
	}
	
	return (line);
}

// static char	*extract_line(char **p_store)
// {
// 	char	*p_nl; //*p_store 内の最初の改行文字の位置を指す
// 	char	*p_end; //*p_store が指す文字列の末尾（ヌル文字の前）を指す
// 	char	*origin;
// 	char	*line;

// 	p_nl = ft_strchr(*p_store, '\n');
// 	p_end = *p_store + ft_strlen(*p_store);
// 	//文字列の最後（ヌル文字の直前）を指すポインタを p_end に格納
// 	origin = *p_store;
// 	*p_store = NULL;
// 	if (p_nl == NULL || p_nl + 1 == p_end)
// 	//改行が見つからない場合、または改行が文字列の最後にある場合（改行の直後にヌル文字がくる場合）
// 		line = ft_substr(origin, 0, p_end - origin);//*p_store の全内容を line にコピー
// 	else
// 	{
// 		line = ft_substr(origin, 0, p_nl - origin + 1);//改行を含む行を抽出
// 		*p_store = ft_substr(origin, p_nl - origin + 1, p_end - p_nl);
// 		//改行の次の文字から文字列の終わりまでを新たな *p_store として設定
// 		if (line == NULL || *p_store == NULL)
// 		{
// 			nullize_free(&line);
// 			nullize_free(p_store);
// 		}
// 	}
// 	free(origin);
// 	return (line);
// }

char	*get_next_line(int fd)
{
	char		*line;
	static char	*static_basin;

	if(!read_from_file(&static_basin, fd))
		return (free_and_nullize(&static_basin));
	return (extract_line(&static_basin));
}

#include <stdio.h>
#include <fcntl.h>
__attribute__((destructor))
static void destructor() {
	system("leaks -q a.out");
}
int main()
{
	int     fd;
	char    *next_line;
	int     count;

	count = 0;
	fd = open("example.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("%s", "Error opening file");
		return (1);
	}
	while (1)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		count++;
		printf("[%d]:%s\n", count, next_line);
		free(next_line);
		next_line = NULL;
	}
	close(fd);
	// system("leaks a.out");
	return (0);
}