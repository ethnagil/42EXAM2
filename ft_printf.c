/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egillesp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:17:50 by egillesp          #+#    #+#             */
/*   Updated: 2021/01/26 13:18:10 by egillesp         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct s_struct
{
	int	zeros;
	int spaces;
	int neg;
	char type;
}				t_struct;

int ft_strlen(char *s)
{
	int j = 0;

	if (!s)
		return (0);
	while (s[j])
		j++;
	return (j);
}

int		ft_write(char *pstr, int len)
{
	write(1, pstr, len);
	return (len);
}

char *ft_strdup(char *s)
{
	int j = 0;
	char *new;

	if (!s)
		return(s);
	j = ft_strlen(s);
	new = (char *)malloc(sizeof(char) * (j + 1));
	if (new)
	{
		j = 0;
		while(s[j])
		{
			new[j] = s[j];
			j++;
		}
		new[j] = '\0';
	}
	return(new);
}

char *ft_itoa_base(unsigned long n, char *base)
{
	int b = 0;
	int l = 0;
	char *new;
	unsigned long n2;

	if (n == 0)
	{
		new = ft_strdup("0");
		return(new);
	}
	n2 = n;
	b = ft_strlen(base);
	while (n2 > 0)
	{
		l++;
		n2 = n2 / b;
	}
	new = (char *)malloc(sizeof(char) * (l + 1));
	if (new)
	{
		new[l] = '\0';
		while (n > 0)
		{
			new[--l] = base[n % b];
			n = n/b;
		}
	}
	return(new);
}

int		ft_apply_flags(char *pstr, t_struct *flags)
{
	int slen = 0;
	int len = 0;

	slen = ft_strlen(pstr);
	if (flags->zeros >= 0)
	{
		if ((flags->type == 's') &&  (flags->zeros < slen))
		{
			pstr[flags->zeros] = '\0';
			flags->zeros = 0;
		}
		else if ((flags->type != 's') && (slen == 1) && (pstr[0] == '0') && (flags->zeros == 0))
			pstr[0] = '\0';
		else if ((flags->zeros > slen) && (flags->type != 's'))
			flags->zeros = flags->zeros - slen;
		else
			flags->zeros = 0;
	}
	if (flags->zeros == -1)
		flags->zeros = 0;
	slen = ft_strlen(pstr);
	flags->spaces = flags->spaces-flags->zeros-slen;
	if (flags->neg == -1)
		flags->spaces--;
	while (flags->spaces-- > 0)
		len += ft_write(" ", 1);
	if (flags->neg == -1)
		len += ft_write("-", 1);
	while (flags->zeros-- > 0)
		len += ft_write("0", 1);
	return (len);
}

int		ft_print_var(char *f, va_list args, t_struct flags)
{
	char 		*pstr = NULL;
	long		n;
	int			len = 0;

		if (flags.type == 's')
			pstr = ft_strdup(va_arg(args, char*));
		if (flags.type == 'd')
		{
			n = va_arg(args, int);
			if (n < 0)
				flags.neg = -1;
			pstr = ft_itoa_base((unsigned long)(n * flags.neg), "0123456789");
		}
		if (flags.type == 'x')
			pstr = ft_itoa_base((unsigned long)va_arg(args, unsigned int), "0123456789abcdef");
		if (!pstr)
			pstr = ft_strdup("(null)");
		len += ft_apply_flags(pstr, &flags);
		len += ft_write(pstr, ft_strlen(pstr));
		free (pstr);
		return (len);
}

int ft_printf(const char *f, ... )
{
	va_list	args;
	t_struct flags;
	int		i = 0;
	int		len = 0;

	va_start(args, f);
	while (f[i])
	{
		if (f[i] == '%')
		{
			flags.zeros = -1; flags.spaces = 0; flags.neg = 1; flags.type = ' ';
			i++;
			while ((f[i] >= '0') && (f[i] <= '9'))
				flags.spaces = (flags.spaces * 10) + (f[i++] - 48);
			if (f[i] == '.')
			{
				i++;
				flags.zeros = 0;
				while ((f[i] >= '0') && (f[i] <= '9'))
					flags.zeros = (flags.zeros * 10) + (f[i++] - 48);
			}
			flags.type = f[i];
			len += ft_print_var((char *)f, args, flags);
		}
		else
		{
			write(1, &f[i], 1);
			len++;
		}
		if (f[i])
			i++;
	}
	return (len);
}

/*
- Vous devez gérer uniquement les conversions suivantes : s,d et x
- Vous devez gérer la taille de champ minimal. (Nous ne testerons jamais votre programme avec une taille de champ minimal de 0)
- Vous devez gérer uniquement le flag de précision `.`.

Votre fonction devra être prototypée de la façon suivante :

int ft_printf(const char *, ... ); */
