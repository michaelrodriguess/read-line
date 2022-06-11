/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microdri <microdr@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:23:00 by microdri          #+#    #+#             */
/*   Updated: 2022/06/11 16:15:21 by microdri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

//# define BUFFER_SIZE 42 
#include <stdio.h>

char	*get_until_lf(char *bank)
{
	char *line;
	int i;
	int count;

	i = 0;
	while (bank[i] != '\0' && bank[i] != '\n')
		i++;
	if (bank[i] == '\n')
		i++;
	line = malloc(sizeof(char) * i + 1);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	count = 0;
	while (count <= i)
	{
		line[count] = bank[count];
		count++;
	}
	line[count - 1] = '\0';
	return (line);
}

char	*get_latter_lf(char *bank)
{
	char *newline;
	int i;
	int j;

	i = 0;
	while (bank[i] != '\0' && bank[i] != '\n')
		i++;
	if (bank[i] == '\0')
	{
		free(bank);
		return (NULL);
	}
	newline = malloc(sizeof(char) * ft_strlen(bank) - i);
	if(!newline)
		return (NULL);
	j = 0;
	while (bank[i++])
			newline[j++] = bank[i];
	free(bank);
	newline[j] = '\0';
	return (newline);
}

char	*get_next_line(int fd)
{
	char *buffer;
	char *aux;
	static char *bank;
	int bytes_reads;
	
	if (!bank)
		bank = malloc(1);
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
	
	aux = malloc(sizeof(char));		
	if (ft_strchr(buffer, '\n'))
		aux = get_until_lf(bank);
	free(buffer);
	if (bytes_reads == '\0')
		aux = get_until_lf(bank);
	bank = get_latter_lf(bank);
	return (aux);

}
/*
int main()
{
	int blabla_fd = open("test-read.txt", O_RDONLY);
		
	
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));
	printf("%s", get_next_line(blabla_fd));

	close(blabla_fd);
}*/
