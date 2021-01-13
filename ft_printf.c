/*
- Vous devez gérer uniquement les conversions suivantes : s,d et x
- Vous devez gérer la taille de champ minimal. (Nous ne testerons jamais votre programme avec une taille de champ minimal de 0)
- Vous devez gérer uniquement le flag de précision `.`.

Votre fonction devra être prototypée de la façon suivante :

int ft_printf(const char *, ... );
*/

#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>


char *ft_strdup(char *str)
{
	int i;
	char *dstr;

	if (!str)
		return (str);
	i = 0;
	while (str[i++]) ;
	dstr = (char*)malloc(sizeof(char) * (i+1));
	i = 0;
	while (str[i])
	{
		dstr[i] = str[i];
		i++;
	}
	dstr[i] = 0;
	return (dstr);
}

char *ft_atoi_base(long int n, char *basenum)
{
	int base;
	int	len;
	char *str;
	long int n2;

	if (n < 0)
		n = n * -1;
	n2 = n;
	base = -1;
	while (basenum[++base]) ;
	len = 0;
	if (n == 0)
	{
		str = ft_strdup("0");
		return (str);
	}
	while (n > 0)
	{
			n = n / base;
			len++;
	}
	str = (char*)malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	while (len > 0)
	{
		str[--len] = basenum[(n2 % base)];
		n2 = n2/base;
	}
	return(str);
}



void		ft_read_flag(char *f, int *i, int *prec1, int *prec2)
{
	*prec1 = -1;
	*prec2 = -1;
	if (f[*i] == '-')
		*i = *i + 1;
	while (((f[*i] >= '0') && (f[*i] <= '9')) && (f[*i] != '.'))
	{
		if (*prec1 < 0)
			*prec1 = 0;
		*prec1 =  (*prec1 * 10) + (f[*i] - 48);
		*i = *i + 1;
	}
	if (f[*i] == '.')
	{
		*i = *i + 1;
		if (f[*i] == '-')
			*i = *i + 1;
		while ((f[*i] >= '0') && (f[*i] <= '9'))
		{
			if (*prec2 < 0)
				*prec2 = 0;
			*prec2 = (*prec2 * 10) + (f[*i] - 48);
			*i = *i + 1;
		}
 	}
}

char	*ft_apply_flag(char *prstr, int prec1, int prec2, char spec)
{
	int i;
	int j;
	int k;
	char *str;


	if (prec2 >= 0)
	{
		if (spec == 's')
			prstr[prec2] = 0;
		if ((spec == 'd') || (spec == 'x'))
		{
			i = 0;
			while (prstr[i++]);
			i--;
			if (i < prec2)
			{
				str = (char *)malloc(sizeof(char) * (prec2 + 1));
				j = 0;
				while(j < (prec2 - i))
					str[j++] = '0';
				k = 0;
				while ((j + k) < prec2)
				{
					str[j+k] = prstr[k];
					k++;
				}
				str[j + k] = 0;
				free(prstr);
				prstr = str;
			}

		}
	}
	if (prec1 > 0)
	{
		i  = 0;
		while (prstr[i++]) ;
		if (i < prec1)
		{
			str = (char *)malloc(sizeof(char) * (prec1 + 1));
			j = 0;
			while (j <= (prec1 - i))
			{
				str[j++] = ' ';
			}
			k = 0;
			while ((j + k) < prec1)
			{
				str[j+k] = prstr[k];
				k++;
			}
			str[j + k] = 0;
			free(prstr);
			prstr = str;
		}			
	}
	return(prstr);
}

int		ft_print_var(char *f, va_list args, int *i)
{
	int	prec1;
	int	prec2;
	int	len;
	char	spec;
	char	*prstr;

	prstr = NULL;
	ft_read_flag(f, i, &prec1, &prec2);
	spec = f[*i];
	if (spec == 's')
		prstr = ft_strdup(va_arg(args, char *));
	if (spec == 'd')
		prstr = ft_atoi_base((va_arg(args, int)), "0123456789");
	if (spec == 'x')
		prstr = ft_atoi_base((va_arg(args, unsigned int)), "0123456789abcdef");	
	if (!prstr)
		prstr = ft_strdup("(null)");	
	if ((prec1 >= 0) || (prec2 >= 0))
		prstr = ft_apply_flag(prstr, prec1, prec2, spec);
	len = 0;
	while(prstr[len])
		write(1, &prstr[len++], 1);
	free(prstr);
	return (len);
}

int ft_printf(const char *f, ... )
{
	va_list	args;
	int		i;
	int		len;

	va_start(args, f);
	len = 0;
	i = 0;
	while(f[i])
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
		if (f[i])
			i++;
	}
	va_end(args);
	return (len);
}
