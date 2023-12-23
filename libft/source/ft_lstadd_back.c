/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:17:15 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:51 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}
//
// int	main(void)
// {
// 	t_list *head = NULL;
// 	t_list *node1 = ft_lstnew("iddd");
// 	ft_lstadd_front(&head, node1);
// 	t_list *newnode = ft_lstnew("hello world");
// 	ft_lstadd_front(&head, newnode);
// 	t_list *backnode = ft_lstnew("hello");
// 	ft_lstadd_back(&head, backnode);
// 	t_list *current = head;
//
// 	__builtin_printf("LAST = %p\n", newnode);
// 	write(1, "B:\n", 3);
// 	while (current != NULL)
// 	{
// 		__builtin_printf("String = %s\n", (char *) current->content);
// 		current = current->next;
// 	}
//
// 	__builtin_printf("I = %d\n", ft_lstsize(head));
// 	__builtin_printf("LAST = %p\n", ft_lstlast(head));
// }
