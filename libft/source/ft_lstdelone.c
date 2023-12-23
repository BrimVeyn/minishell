/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:26:45 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	(del)(lst->content);
	free(lst);
}
// void	deldel(void	*cont)
// {
// 	size_t	size;
//
// 	size = ft_strlen((const char *) cont);
// 	ft_memset(cont, 0, size);
// }
//
// int	main(void)
// {
// 	t_list	*head = NULL;
// 	size_t	i = 0;
//
// 	ft_lstadd_front(&head, ft_lstnew("hello"));
// 	ft_lstadd_back(&head, ft_lstnew("world"));
//
// 	t_list *current = head;
// 	while (current != NULL)
// 	{
// 		__builtin_printf("%s\n", (char *) current->content);
// 		current = current->next;
// 	}
//
// 	current = head;
// 	while (current != NULL)
// 	{
// 		if (i++ == 1)
// 			ft_lstdelone(current, deldel);
// 		current = current->next;
// 	}
//
// 	current = head;
// 	while (current != NULL)
// 	{
// 		__builtin_printf("%s\n", (char *) current->content);
// 		// current = current->next;
// 	}
//
// }
