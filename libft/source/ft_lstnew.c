/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 06:45:12 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/12/27 16:08:55 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(1 * sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
//
// int	main(void)
// {
// 	t_list *node;
// 	int		nb[] = { 9, 4, 5 };
// 	node = ft_lstnew(&nb);
// 	int	*arr = node->content;
// 	size_t i = 0;
// 	while (i < 3)
// 	{
// 		__builtin_printf("%d ", arr[i]);
// 		i++;
// 	}
// 	// __builtin_printf("%d %p", *(int*) node->content, node->next);
// }
