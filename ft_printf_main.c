// ./a.out d $'|%10.15x|\n' 55

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_printf(char *f, ...);

int main(int n, char **s)
{
	if (s[1][0] == 's')
	{
		printf(s[2], s[3]);
		ft_printf(s[2], s[3]);
		printf(s[2], NULL);
		ft_printf(s[2], NULL);
		printf(s[2], "0");
		ft_printf(s[2], "0");
	}
	if (s[1][0] != 's')
	{
		printf(s[2], atoi(s[3]));
		ft_printf(s[2], atoi(s[3]));
		printf(s[2], NULL);
		ft_printf(s[2], NULL);
			printf(s[2], INT_MIN);
		ft_printf(s[2], INT_MIN);
			printf(s[2], INT_MAX);
		ft_printf(s[2], INT_MAX);
	}
	return (0);
}
