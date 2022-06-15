/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdr@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:23:00 by microdri          #+#    #+#             */
/*   Updated: 2022/06/15 20:25:52 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line(int fd, char *bank)
{	
	char *buffer;
	char *aux;
	int bytes_reads;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_reads = 1;
	while (bytes_reads != 0 && !ft_strchr(bank, '\n'))
	{
		bytes_reads = read(fd, buffer, BUFFER_SIZE);
		if (bytes_reads == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_reads] = '\0';
		aux = bank;
		bank = ft_strjoin(bank, buffer);
		free(aux);
	}
	free(buffer);
	return (bank);
}

char	*get_until_lf(char *bank)
{
	char *line;
	int i;
	int count;

	
	i = 0;
	if (!bank[0])
		return (NULL);
	while (bank[i] != '\n' && bank[i] != '\0')
		i++;
	if (bank[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	count = 0;
	while (count < i)
	{
		line[count] = bank[count];
		count++;
	}
	line[count] = '\0';
	return (line);
}

char	*get_latter_lf(char *bank)
{
	char *newline;
	int i;
	int count;

	i = 0;
	while (bank[i] != '\0' &&  bank[i] != '\n')
		i++;
	if (!bank[i])
	{
		free(bank);
		return (NULL);
	}
	newline = malloc((ft_strlen(bank) - i + 1) * sizeof(char));
	if(!newline)
		return (NULL);
	count = 0;
	while (bank[i++])
			newline[count++] = bank[i];
	newline[count] = '\0';
	free(bank);
	return (newline);
}

char	*get_next_line(int fd)
{
	static char *bank[4096] = {0};
	char *out;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	bank[fd] = get_line(fd, bank[fd]);
	if (!bank[fd])
		return (NULL);
	out = get_until_lf(bank[fd]);
	bank[fd] = get_latter_lf(bank[fd]);

	return (out);
}

