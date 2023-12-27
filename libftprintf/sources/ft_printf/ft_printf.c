/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbardavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:32:26 by nbardavi          #+#    #+#             */
/*   Updated: 2023/12/24 12:36:39 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_printf.h"

char		*exec_flags(const char *txt, int i, va_list args);

static int	print_and_free2(char *str, int fd)
{
	int	len;

	if (str)
	{
		len = (int)ft_strlen(str);
		ft_putstr_fd(str, fd);
		free(str);
		return (len);
	}
	return (0);
}

static int	handle_format2(const char *txt, unsigned int *i, va_list args)
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
	return (print_and_free2(temp, 2));
}

int	ft_printf(const char *txt, ...)
{
	va_list			args;
	unsigned int	i;
	int				count;

	if (txt == NULL)
		return (-1);
	va_start(args, txt);
	count = 0;
	i = 0;
	while (txt[i])
	{
		if (txt[i] == '%')
			count += handle_format2(txt, &i, args);
		else
		{
			ft_putchar_fd(txt[i], 2);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}

// int	main(void)
// {
// 	int count = printf("|%02.X|", 0);
//
// 	printf("\n");
// 	int count2 = ft_printf("|%02.X|", 0);
// 	printf("\nvalue printf: %d\nvalue ft_printf: %d\n", count, count2);
// 	return (0);
// }
