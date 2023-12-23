/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:31:10 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:18 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newhead;
	t_list	*newnode;

	newnode = lst;
	newhead = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		newnode = ft_lstnew((f)(newnode->content));
		if (!newnode)
			ft_lstclear(&newhead, (del));
		ft_lstadd_back(&newhead, newnode);
		lst = lst->next;
	}
	return (newhead);
}
// void	del(void	*lst)
// {
// 	(void) lst;
// }
//
// void	*haha(void	*cont)
// {
// 	char *str;
// 	str = cont;
// 	str[0] = 48;
// 	return (str);
// }
// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*newnode;
//
//
// 	ft_lstadd_back(&head, ft_lstnew(ft_strdup("OK")));
// 	ft_lstadd_back(&head, ft_lstnew(ft_strdup("c")));
// 	ft_lstadd_back(&head, ft_lstnew(ft_strdup("super")));
// 	ft_lstadd_back(&head, ft_lstnew(ft_strdup("map")));
// 	ft_lstadd_back(&head, ft_lstnew(ft_strdup("love")));
//
// 	newnode = head;
// 	while (newnode != NULL)
// 	{
// 		__builtin_printf("B CONT = %s\n", (char *) newnode->content);
// 		newnode = newnode->next;
// 	}
//
// 	t_list	*new;
//
// 	new = ft_lstmap(head, haha, del);
//
// 	while (new != NULL)
// 	{
// 		__builtin_printf("A CONT = %s\n", (char *) new->content);
// 		new = new->next;
// 	}
//
// }
//
