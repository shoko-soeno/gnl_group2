/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:16:13 by ssoeno            #+#    #+#             */
/*   Updated: 2024/05/17 18:13:06 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

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

static void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*c_dst;
	const unsigned char	*c_src;
	char				sign;
	size_t				cur;

	c_src = (const unsigned char *)src;
	c_dst = (unsigned char *)dst;
	sign = (dst < src) * 2 - 1;
	cur = (sign == -1) * len;
	while (cur != (sign == 1) * len && (dst || src))
	{
		c_dst[cur - (sign == -1)] = c_src[cur - (sign == -1)];
		cur += sign;
	}
	return (dst);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	if (s1_len >= SIZE_MAX - s2_len - 1)
		return (NULL);
	str = (char *)malloc(sizeof(*s1) * (s1_len + s2_len + 1));
	ft_memmove(str, s1, s1_len);
	ft_memmove(str + s1_len, s2, s2_len);
	str[s1_len + s2_len] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	s_len;
	size_t	finish;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	finish = 0;
	if (start < s_len)
		finish = s_len - start;
	if (finish > len)
		finish = len;
	new = (char *)malloc(sizeof(char) * (finish + 1));
	if (!new)
		return (NULL);
	ft_memmove(new, s + start, finish + 1);
	return (new);
}
