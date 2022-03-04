/* Write a function named get_next_line which prototype should be:
char *get_next_line(int fd);

Your function must return a line that has been read from the file descriptor passed as
parameter. What we call a "line that has been read" is a succesion of 0 to n 
characters that end with '\n' (ascii code 0x0a) or with End Of File (EOF).
The line should be returned including the '\n' in case there is one at the end of the
line that has been read. When you've reached the EOF, you must store the current
buffer in a char * and return it. If the buffer is empty you must return NULL.

In case of error return NULL. In case of not returning NULL, the pointer should be
free-able. Your program will be compiled with the flag -D BUFFER_SIZE=xx, which has to
be used as the buffer size for the read calls in your functions.

Your function must be memory leak free. When you've reached the EOF, your function
should keep 0 memory allocated with malloc, except the line that has been returned.

Caling your function get_next_line in a lop will therefore allow you to read the text
avaiable on a file descriptor one line at a time until the end of the text, no matter
the size of either the text or one of its lines.

Make sure that your function behaves wel when it reads from a file, from the standard
output, from a redirection, etc...

No call to another function will be done on the file descriptor between 2 calls of
get_next_line. Finally we consider that get_next_line has an undefined behaviour when
reading from a binary file.*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char    *get_next_line(int fd)
{
    char    stock[10000];
    char    buf[1];
    char    *line;
    int        i;

    i = 0;
    if (fd < 0 || BUFFER_SIZE <= 0){
        return (NULL);}
	stock[i] = '\0';
    while (read(fd, buf, 1) == 1)
    {
        stock[i] = buf[0];
        stock[i + 1] = '\0';
        if (stock[i] == '\n')
            break ;
        i++;
    }
    if (stock[0] == '\0'){
		return (NULL);}
    line = malloc(i + 2);
    i = 0;
    while (stock[i])
    {
        line[i] = stock[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}

int main(void)
{
	char	*line;
	int		fd = 0;
	int		loop = 1;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error while opening file\n");
		return (1);
	}
	while (loop)
	{
		line = get_next_line(fd);
		if (line != NULL)
		{
			printf("%s", line);
			free(line);
		}
		else
			loop = 0;
	}
	free(line);
	close(fd);
	return (0);
}
