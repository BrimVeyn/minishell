/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 07:00:20 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
//
//
// int	main(void)
// {
// 	t_list *head = NULL;
// 	t_list *node1 = ft_lstnew("iddd");
// 	ft_lstadd_front(&head, node1);
// 	t_list *newnode = ft_lstnew("hello world");
// 	ft_lstadd_front(&head, newnode);
// 	t_list *current = head;
//
// 	write(1, "B:\n", 3);
// 	while (current != NULL)
// 	{
// 		__builtin_printf("String = %s\n", (char *) current->content);
// 		current = current->next;
// 	}
// }
