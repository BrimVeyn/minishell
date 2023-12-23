/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:32:26 by nbardavi          #+#    #+#             */
/*   Updated: 2023/12/23 18:54:19 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

char		*exec_flags(const char *txt, int i, va_list args);

char	*check_p(const char *txt, unsigned int i, va_list args)
{
	if (txt[i] == 'd' || txt[i] == 'i')
		return (ft_itoa(va_arg(args, int)));
	if (txt[i] == 'c')
		return (itc(va_arg(args, int)));
	if (txt[i] == 's')
		return (interdup(va_arg(args, char *)));
	if (txt[i] == 'p')
		return (to_hexa_p(va_arg(args, unsigned long long)));
	if (txt[i] == 'u')
		return (ft_itoa_u(va_arg(args, unsigned int)));
	if (txt[i] == 'x' || txt[i] == 'X')
		return (to_hexa(va_arg(args, unsigned int), txt[i]));
	if (txt[i] == '%')
		return (ft_strdup("%"));
	return (NULL);
}

static char	*print_and_free(char *str, char *returnchar)
{

	if (str)
		return (ft_strjoin_free(returnchar, str));
	return (0);
}

static char	*handle_format(const char *txt, unsigned int *i, va_list args, char* returnchar)
{
	int		nbf;
	char	*temp;

	nbf = c_flags(txt, *i + 1);
	if (nbf == 0)
		temp = check_p(txt, ++(*i), args);
	else
	{
		temp = exec_flags(txt, ++(*i), args);
		if (temp)
			*i += nbf;
	}
	return (print_and_free(temp, returnchar));
}

char	*ft_sprintf(char *txt, ...)
{
	va_list			args;
	unsigned int	i;
	int				count;
	char	*returnchar;

	returnchar = ft_strdup("");
	va_start(args, txt);
	count = 0;
	i = 0;
	while (txt[i])
	{
		if (txt[i] == '%')
			returnchar = handle_format(txt, &i, args, returnchar);
		else
		{
			returnchar = ft_strjoin_free(returnchar, ft_strdup_char(txt[i]));
			count++;
		}
		i++;
	}
	va_end(args);
	return (returnchar);
}

// int	main(void)
// {
// 	char *count2 = ft_sprintf("%05d %s", 232, "Coucou");
// 	printf("%s", count2);
// 	free(count2);
// 	return (0);
// }
