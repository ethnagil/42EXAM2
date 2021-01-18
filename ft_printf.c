/*
- Vous devez gérer uniquement les conversions suivantes : s,d et x
- Vous devez gérer la taille de champ minimal. (Nous ne testerons jamais votre programme avec une taille de champ minimal de 0)
- Vous devez gérer uniquement le flag de précision `.`.

Votre fonction devra être prototypée de la façon suivante :

int ft_printf(const char *, ... );
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egillesp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 13:21:51 by egillesp          #+#    #+#             */
/*   Updated: 2021/01/14 15:23:19 by egillesp         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

int ft_write(char *str, int len)
{
	write(1, str, len);
	return (len);
}

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return(i);
}

char *ft_strdup(char *str)
{
	int i;
	char *new;

	if (!str)
		return(str);
	i = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (0);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char *ft_itoa_base(unsigned long n, char *base)
{
	unsigned long n2;
	int		len;
	char	*new;
	int		b;
	int neg = 0;

	b = ft_strlen(base);
	n2 = n;
	len = 0;
	if (n == 0)    
	{
		new = ft_strdup("0");
		return(new);
	} 
	while (n > 0)
	{
		n = n / b;
		len++;
	}
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (0);
	new[len] = '\0';
	while (n2 > 0)
	{
		new[--len] = base[n2 % b];
		n2 = n2 / b;
	}
	return(new);
}

int		ft_apply_flag(char *prstr, int p1, int p2, char spec, int neg)
{
	int len;
	int zero;
	int space;
	int count;

	zero = 0;
	space = 0;
	count = 0;
	if (prstr[0] == '\0')     /** ! **/
		return (0);
	len = ft_strlen(prstr);
	if (p2 >= 0)
	{
		if (((spec == 's') && (len > p2)) || ((spec != 's') &&   /** ! **/
				(len == 1) && (prstr[0] == '0')))
			prstr[p2] = '\0';
		if (((spec == 'd') || (spec == 'x')) && (p2 > len))
			zero = p2 - len;
	}
	len = ft_strlen(prstr);  /***  if s, len can be truncated **/
	if (p1 >= 0)
	{
		if ((len + zero) < p1)
			space = p1 - len - zero;
	}
	if (neg)
		space--;
	while (space > 0)
	{
		count += ft_write(" ", 1);
		space--;
	}
	if (neg)
		count += ft_write("-", 1);
	while (zero-- > 0)
		count += ft_write("0", 1);
	return (count);
}

void	ft_read_flag(char *f, int *i, int *p1, int *p2)
{
	int		p2neg = 0;

	*p1 = -1;
	*p2 = -1;
	if (f[*i] == '-')
		*i = *i + 1;
	while((f[*i]) && (f[*i] >= '0') && (f[*i] <= '9'))
	{
		if (*p1 < 0)
			*p1 = 0;
		*p1 = (*p1 * 10) + (f[*i] - 48);
		*i = *i + 1;
	}
	if (f[*i] == '.')
	{
		*i = *i + 1;
		if (f[*i] == '-')
			*i = *i + 1;
		while((f[*i]) && (f[*i] >= '0') && (f[*i] <= '9'))
		{
			if (*p2 < 0)
				*p2 = 0;
			*p2 = (*p2 * 10) + (f[*i] - 48);
			*i = *i + 1;
		}
		if (*p2 == -1)    /** ! **/
			*p2 = 0;
	}
}

int		ft_print_var(char *f, va_list args, int *i)
{
	int	p1;
	int p2;
	long n;
	char *prstr;
	char spec;
	int	j;
	int neg;

	prstr = NULL;
	neg = 0;
	ft_read_flag(f, i, &p1, &p2);
	spec = f[*i];
	if (spec == 's')
		prstr = ft_strdup(va_arg(args, char*));
	if (spec == 'd')
	{
		n = va_arg(args, int);
		if (n < 0)
		{
			neg = 1;
			n = n * -1;
		}
		prstr = ft_itoa_base((unsigned long)n, "0123456789");
	}
	if (spec == 'x')
		prstr = ft_itoa_base((unsigned long)(va_arg(args, unsigned int)), "0123456789abcdef");
	if (!prstr)							 /** ! **/
		prstr = ft_strdup("(null)");
	j = ft_apply_flag(prstr, p1, p2, spec, neg);
	j += ft_write(prstr, ft_strlen(prstr));	
	free(prstr); 						 /** ! **/
	return (j);
}

int		ft_printf(const char *f, ...)
{
	va_list args;
	int		i;
	int		len;

	va_start(args, f);
	i = 0;
	len = 0;
	while (f[i])
	{
		if (f[i] == '%')
		{
			i++;
			len += ft_print_var((char *)f, args, &i);
		}
		else
		{
			write(1, &f[i], 1);
			len++;
		}
		if (f[i])      /** ! **/
			i++;
	}
	va_end(args);       /** ! **/
	return(len);
}
