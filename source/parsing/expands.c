/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:15:52 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 11:23:51 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ms_extract(char *split, int *j, char c)
{
	int const start = *j + (c != ZERO);
	char *new;

	(*j) += (c != ZERO);
	if (c == ZERO)
		while (split[*j] && (split[*j] != '\'' && split[*j] != '\"'))
			(*j)++;
	else
		while (split[*j] && split[*j] != c)
			(*j)++;
	new = ft_substr(split, start, *j - start);
	(*j) += (c != ZERO);
	return (new);
}

char *tild_expand(char *word, t_env *denv)
{
	char *new;

	if (!ft_strchr(word, '~') || tild_index(word) != 0)
		return (word);
	if (ft_strlen(word) == 1)
	{
		new = ft_strjoin_free(ft_strdup("/home/"), ft_strdup(denv->usr));
		free(word);
		return (new);
	}
	else if (!ft_strncmp(word, "~/", 2)) 
	{
		new = ft_strjoin_free(ft_strdup("/home/"), ft_strdup(denv->usr));
		new = ft_strjoin_free(new, ft_substr(word, 1, ft_strlen(word) - 1));
		return (free(word), new);
	}
	return (word);
}

t_dlist *ms_wildcard_expand(t_starlist *current, t_dlist *flist)
{
	while (current)
	{
		if (current->type == START)
			flist = ms_dlstmap(&flist, current->str, &ms_matchstart);
		else if (current->type == MID) 
			flist = ms_dlstmap(&flist, current->str, &ms_matchmid);
		else if (current->type == END)
			flist = ms_dlstmap(&flist, current->str, &ms_matchend);
		current = current->next;
	}
	return (flist);
}

char	*w_expand(char *word, t_env *denv)
{
	t_dlist		*flist;
	t_starlist	*slist;
	t_starlist	*current;
	int			dot_trigger;
	char		*newword;

	if (ms_findstar(word) == ERROR || !word)
		return (word);
	dot_trigger = (word[0] != '.');
	flist = get_flist(denv);
	slist = ms_starsplit(word);
	current = slist;
	flist = ms_wildcard_expand(current, flist);
	if (!flist)
		return (ms_dlstclear(&flist), word);
	if (dot_trigger)
		flist = ms_dlstmap(&flist, NULL, &ms_del_hidden);
	ms_dlsort(&flist);
	free(word);
	newword = ms_dlstjoin(&flist);
	ms_dlstclear(&flist);
	ms_starclear(&slist);
	return (newword);
}