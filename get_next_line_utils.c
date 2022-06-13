/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdr@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:25:53 by microdri          #+#    #+#             */
/*   Updated: 2022/06/13 18:36:26 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	index;

	index = 0;
	while (str[index] != '\0')
		index++;
	return (index);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*temp;
	int		flag;
	int		len;

	flag = 0;
	if (!s2)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = 0;
		flag++;
	}
	len = ft_strlen(s1) + ft_strlen(s2);
	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	while (*s1)
		*temp++ = *s1++;
	while (*s2)
		*temp++ = *s2++;
	*temp = '\0';
	if (flag == 1)
		free(s1);
	return (temp - len);
}

char	*ft_strchr(char *s, int c)
{
	while (*s != (char) c)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return (s);
}
