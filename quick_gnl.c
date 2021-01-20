#include "q_get_next_line.h"

char *ft_strjoin(char *str, char c)
{
	int i = 0;
	char *new;

	while (str[i++]) ;
	new = (char *)malloc(sizeof(char) * (i + 3));
	i = 0;
	while (str[i])
	{
		printf("str[i] %c %d\n", str[i], i);
		new[i] = str[i];
		i++;
	}
	new[i++] = c;
	new[i] = 0;
	free(str);
	return(new);
}
int	get_next_line(char **line)
{
	char buf;

	if (!line)
		return (-1);
	*line = (char *)malloc(sizeof(char) * 1);
	*line[0] = '\0';
	while (read(0, &buf, 1) > 0)
	{
		printf("buf %c\n", buf);
		if (buf == '\n')
			return (1);
		else
		{
			*line = ft_strjoin(*line, buf);
		}	
	}
	return(read(0, &buf, 1));
}
