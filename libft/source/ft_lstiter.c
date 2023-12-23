/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:24:46 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/18 11:38:49 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;

	current = lst;
	while (current != NULL)
	{
		(f)(current->content);
		current = current->next;
	}
}
// void	haha(void	*cont)
// {
// 	char *str;
// 	str = cont;
// 	str[0] = 48;
// }
// int	main(void)
// {
// 	t_list	*head = NULL;
//
// 	ft_lstadd_front(&head, ft_lstnew(ft_strdup("src")));
// 	ft_lstadd_back(&head, ft_lstnew(ft_strdup("src")));
// 	ft_lstadd_back(&head, ft_lstnew(ft_strdup("src")));
//
//
// 	t_list *current = head;
// 	while (current != NULL)
// 	{
// 		__builtin_printf("%s\n", (char *) current->content);
// 		current = current->next;
// 	}
//
// 	current = head;
// 	while (current->next != NULL)
// 	{
// 		ft_lstiter(current, haha);
// 		current = current->next;
// 	}
//
// 	current = head;
// 	while (current != NULL)
// 	{
// 		__builtin_printf("%s\n", (char *) current->content);
// 		current = current->next;
// 	}
//
// }
