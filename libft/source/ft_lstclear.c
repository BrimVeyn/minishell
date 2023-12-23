/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:01:18 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:50 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = *lst;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
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
// 	t_list *head = NULL;
// 	t_list *node1 = ft_lstnew("iddd");
// 	ft_lstadd_front(&head, node1);
// 	t_list *node2 = ft_lstnew("hello world");
// 	ft_lstadd_back(&head, node2);
// 	t_list *node3 = ft_lstnew("hello");
// 	ft_lstadd_back(&head, node3);
// 	t_list *tmp = head;
//
// 	write(1, "B:\n", 3);
// 	while (tmp != NULL)
// 	{
// 		__builtin_printf("String = %s\n", (char *) tmp->content);
// 		tmp = tmp->next;
// 	}
//
// 	tmp = head;
//
// 	write(1, "A:\n", 3);
// 	node1->next = NULL;
// 	ft_lstclear(&node2, deldel);
//
// 	while (tmp != NULL)
// 	{
// 		__builtin_printf("String = %s\n", (char *) tmp->content);
// 		tmp = tmp->next;
// 	}
// }
