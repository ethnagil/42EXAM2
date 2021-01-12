#include <unistd.h>

int ft_elementof(char c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int main(int n, char **args)
{
	char used[255];
	int	i;
	int	j;
	int	k;

	if (n == 3)
	{
		j = 0;
		i = 0;
		k = 1;
		used[0] = 0;
		while (k < 3)
		{
			while(args[k][i])
			{
				if (!ft_elementof(args[k][i], used))
				{
					used[j] = args[k][i];
					j++;
					used[j] = 0;
				}
				i++;
			}
			k++;
			i = 0;
		}
		i = 0;
		while (used[i])
			write(1, &used[i++], 1);
	}
	write(1, "\n", 1);
	return (0);
}