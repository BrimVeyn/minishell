/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:55:49 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:50 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	unb;

	unb = nb;
	if (nb < 0)
	{
		unb = -nb;
		write(fd, "-", 1);
	}
	if (unb >= 10)
	{
		ft_putnbr_fd(unb / 10, fd);
		ft_putnbr_fd(unb % 10, fd);
	}
	else
	{
		unb = unb + '0';
		write(fd, &unb, 1);
	}
}
/*
int	main(void)
{
	ft_putnbr(-2147483648);
}*/
