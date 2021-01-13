#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	get_next_line(char **line);
void	ft_bzero(void *s, size_t n);
char *ft_strjoin(char *dst, char *src);
char *ft_strcpy(char *dst, char *src);
int	ft_eol(char *buf, char *bufover);
int	ft_strlen(char *str);

#endif
