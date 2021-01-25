/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egillesp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:48:37 by egillesp          #+#    #+#             */
/*   Updated: 2021/01/25 17:22:37 by egillesp         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

typedef struct s_struct
{
	int z;
	int s;
	int neg;
	char type;
} t_struct;

void ft_init_flags(t_struct *fl)
{
	fl->z = -1;
	fl->s = 0;
	fl->neg = 1;
	fl->type = ' ';
}

int ft_write(char *str, int len)
{
	write(1, str, len);
	return len;
}

int ft_strlen(char *str)
{
	int j = 0;

	if (!str)
		return (0);
	while (str[j])
		j++;
	return (j);
}

char *ft_strdup(char *str)
{
	char *new = NULL;
	int j = 0;

	if (!str)
		return(str);
	j = ft_strlen(str);
	new = (char *)malloc(sizeof(char) * (j + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (str[j])
	{
		new[j] = str[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}

char *ft_itoa_base(unsigned long n, char *base)
{
	int len = 0;
	int bn = 0;
	unsigned long n2;
	char *new;

	bn = ft_strlen(base);
	n2 = n;
	while (n2 > 0)
	{
		n2 = n2 /bn;
		len++;
	}
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	new[len] = '\0';
	while (n > 0)
	{
		new[--len] = base[n % bn];
		n = n / bn;
	}
	return (new);
}

int	ft_apply_flags(char *pstr, t_struct fl)
{
	int ls = 0;
	int len = 0;
	int j = 0;
	int k = 0;

	ls = ft_strlen(pstr);
	if (fl.z >= 0)
	{
		if ((fl.type == 's') && (ls > fl.z))
			pstr[fl.z] = '\0';
		else if ((fl.type != 's') && (fl.z == 0) && ((ls == 1) && (pstr[0] == '0')))
			pstr[0] = '\0';
	}
	ls = ft_strlen(pstr);
	if (fl.neg == -1)
		j = fl.s - 1;
	else
		j = fl.s;
	if (fl.z >= len)
		k = fl.z;
	else
		k = ls;
	while ((j-- > k) && (fl.s > ls))
		len += ft_write(" ", 1);
	if (fl.neg == -1)
		len += ft_write("-",1);
	if (fl.type != 's')
		j = fl.z;
	else
		j = 0;
	while ((j-- > ls) && (fl.z > ls))
		len += ft_write("0", 1);
	return (len);
}

int ft_print_var(va_list args, t_struct fl)
{
	char *pstr = NULL;
	long	n;
	int		len = 0;

	if (fl.type == 's')
		pstr = ft_strdup(va_arg(args, char*));
	if (fl.type == 'd')
	{
		n = va_arg(args, int);
		if (n < 0)
			fl.neg = -1;
		pstr = ft_itoa_base((unsigned long)(n * fl.neg), "0123456789");
	}
	if (fl.type == 'x')
		pstr = ft_itoa_base(((unsigned long)va_arg(args, unsigned int)), "0123456789abcdef");
	if (!pstr)
		pstr = ft_strdup("(null)");
	len += ft_apply_flags(pstr, fl);
	len += ft_write(pstr, ft_strlen(pstr));
	free(pstr);
	return (len);
}

int ft_printf(const char *f, ...)
{
	t_struct fl;
	va_list	args;
	int len = 0;
	int i = 0;

	va_start(args, f);
	while(f[i])
	{
		if (f[i] == '%')
		{
			ft_init_flags(&fl);
			i++;
			while((f[i] >= '0') && (f[i] <= '9'))
				fl.s = (fl.s * 10) + (f[i++] - 48);
			if (f[i] == '.')
			{
				i++;
				fl.z = 0;
				while((f[i] >= '0') && (f[i] <= '9'))
					fl.z = (fl.z * 10) + (f[i++] - 48);
			}
			fl.type = f[i];
			len += ft_print_var(args, fl);
		}
		else
		{
			write(1, &f[i], 1);
			len++;
		}
		if (f[i])
			i++;
	}
	va_end(args);
	return (len);
}
