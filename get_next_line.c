/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdr@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:23:00 by microdri          #+#    #+#             */
/*   Updated: 2022/06/13 18:50:19 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

//# define BUFFER_SIZE 42 
#include <stdio.h>

char	*get_line(int fd, char *bank)
{	
	char *buffer;
	char *aux;
	int bytes_reads;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_reads = 1;
	while (bytes_reads > 0 && !ft_strchr(buffer, '\n'))
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
	while (bank[i] != '\n' && bank[i])
		i++;
	if (bank[i] == '\n')
		i++;
	line = malloc(sizeof(char) * i + 1);
	if (!line)
	{
		return (NULL);
	}
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
	if (bank[i] == '\0')
	{
		free(bank);
		return (NULL);
	}
	newline = malloc(sizeof(char) * ft_strlen(bank) - i + 1);
	if(!newline)
		return (NULL);
	count = -1;
	while (bank[i++])
			newline[++count] = bank[i];
	free(bank);
	newline[count] = '\0';
	return (newline);
}

char	*get_next_line(int fd)
{
	static char *bank;
	char *out;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	bank = get_line(fd, bank);
	if (!bank)
		return (NULL);
	out = get_until_lf(bank);
	bank = get_latter_lf(bank);

	return (out);
}
/*
int main()
{
	int blabla_fd = open("test.txt", O_RDONLY);
	int i = 0;
	char *line;

	while (i++ < 7)
	{
		line = get_next_line(blabla_fd);
		printf("%s", line);
		free(line);
	}
	close(blabla_fd);
}*/
