// ./a.out d $'|%10.15x|\n' 55


#include <stdio.h>
#include <limits.h>
#include <strings.h>
#include <stdlib.h>

int	ft_printf(char *f, ...);

int main(int n, char **s)
{
	(void)n;
	if (s[1][0] == 's')
	{
	printf(s[2], s[3]);
	ft_printf(s[2], s[3]);
	}
	else
	{
	printf(s[2], atoi(s[3]));
	ft_printf(s[2], atoi(s[3]));
	}

	if (s[1][0] == 's')
	{
	printf(s[2], NULL);
	ft_printf(s[2], NULL);
	}
	else
	{
	printf(s[2], INT_MAX);
	ft_printf(s[2], INT_MAX);
	printf(s[2], INT_MIN);
	ft_printf(s[2], INT_MIN);
	}

	while (2) ;
	return (0);
	
}
