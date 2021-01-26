/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egillesp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:57:29 by egillesp          #+#    #+#             */
/*   Updated: 2021/01/06 12:52:47 by egillesp         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(int n, char **args)
{
	char used[255];
	int	i = 0;
	int	j = 0;

	if (n == 3)
	{
		while (i < 255)
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
				j++;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
