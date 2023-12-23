/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:54:14 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*returnvalue;

	if (size == 0)
	{
		returnvalue = malloc(0);
		return (returnvalue);
	}
	if (nmemb <= 0 && size <= 0)
		return (NULL);
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	returnvalue = malloc(nmemb * size);
	if (returnvalue == NULL || (!nmemb && !size))
		return (NULL);
	if (returnvalue)
	{
		ft_memset(returnvalue, 0, nmemb * size);
	}
	return (returnvalue);
}
