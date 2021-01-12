#include <unistd.h>
/*
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
*/
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
		k = 0;
		used[0] = 0;
		while (i <= 255)
			used[i++] = 0;
		i = 0;
		while(args[1][i])
		{
			j = 0;
			while(args[2][j])
			{
				if (args[1][i] == args[2][j])
				{
					if (!used[(unsigned char)args[1][i]])
					{
						used[(unsigned char)args[1][i]] = 1;
						write(1, &args[1][i], 1);
					}
				}
//					if (!ft_elementof(args[1][i], used))
//					{
//						used[k] = args[1][i];
//						k++;
//						used[k] = 0;
//					}
				j++;
			}
			i++;
		}
//		i = 0;
//		while (used[i])
//			write(1, &used[i++], 1);
	}
	write(1, "\n", 1);
	return (0);
}