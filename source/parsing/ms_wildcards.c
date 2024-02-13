/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:15:52 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/01 11:32:58 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_dlist	*get_flist(t_env *denv)
{
	struct dirent	*entry;
	DIR				*dir;
	t_dlist			*head;
    char            cdir[PATH_MAX];

    (void) denv;
	head = NULL;
	dir = opendir(getcwd(cdir, PATH_MAX));
	if (dir == NULL)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		ms_dlstab(&head, ms_dlstnew(ft_strdup(entry->d_name), 0));
		entry = readdir(dir);
	}
	closedir(dir);
	return (head);
}

char	*ms_xt(char *split, int *j, char c)
{
	int		start;
	char	*new;

	start = *j + (c != ZERO);
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

char	*tild_expand(char *word, t_env *denv)
{
	char	*new;

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

t_dlist	*ms_wildcard_expand(t_starlist *current, t_dlist *flist)
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

char	*w_expand(char *word, t_env *denv, t_tok *tdata)
{
	t_dlist		*flist;
	t_starlist	*slist;
	t_starlist	*current;
	int			dot_trigger;
	char		*newword;

	if (!word || ms_findstar(word, tdata) == ERROR)
		return (word);
	dot_trigger = (word[0] != '.');
	flist = get_flist(denv);
	slist = ms_starsplit(word, tdata);
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
