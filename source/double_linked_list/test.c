/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:45:24 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/15 15:39:42 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
//
// int	main(void)
// {
//
//     t_dlist *head = NULL;
//     t_dlist *to_del;
//
//     ms_dlstab(&head, ms_dlstnew("one", 0));
//     ms_dlstab(&head, ms_dlstnew("two", 0));
//     ms_dlstab(&head, ms_dlstnew("three", 0));
//     ms_dlstab(&head, ms_dlstnew("four", 0));
//
// 	head = ms_dlstmap(&head, &ms_match_check);
//     // ms_dlstclear(&head);
// 	// ms_dlstdelone(&head);
// 	// ms_dlstdelone(&head->next);
// 	// ms_dlstdelone(&head->next);
// 	// ms_dlstdelone(&head);
//
// 	t_dlist *current = head;
// 	int i = 0;
//
// 	while (current)
// 	{
// 		printf("l[%d] = %s\n", i++, current->str);
// 		current = current->next;
// 	}
//     ms_dlstclear(&head);
// }
