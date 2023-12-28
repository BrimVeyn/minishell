/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_h_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:43:35 by nbardavi          #+#    #+#             */
/*   Updated: 2023/12/27 17:11:39 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_h_lst	*ms_lst_new(char *content)
{
	t_h_lst	*newlst;

	newlst = (t_h_lst *)ft_calloc(1, sizeof(t_h_lst));
	if (newlst == NULL)
		return (NULL);
	newlst->content = content;
	newlst->next = NULL;
	return (newlst);
}

void	ms_lst_b(t_h_lst **lst, t_h_lst *newlst)
{
	t_h_lst	*current;

	if (*lst == NULL)
	{
		*lst = newlst;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = newlst;
}
