#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	get_next_line(char **line);
char *ft_strjoin(char *str, char c);

#endif
