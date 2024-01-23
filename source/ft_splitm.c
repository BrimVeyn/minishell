/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:23:00 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/23 14:55:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int count_words(char *str)
{
    int x[5];

    if (ms_setint(&x[COUNT], 0), ms_setint(&x[IX], 0), ms_setint(&x[DQ], 0), ms_setint(&x[SQ], 0), str)
		(void) str;
    while (str[x[IX]])
    {
		x[TRIGGER] = 0;
        while ((str[x[IX]] && !ms_isws(str[x[IX]])) || (str[x[IX]] && (x[DQ] || x[SQ])))
        {
			x[DQ] ^= (str[x[IX]] == DQUOTE);
			x[SQ] ^= (str[x[IX]] == SQUOTE);
            x[TRIGGER] = 1; 
			x[IX]++;
        }
        if (x[TRIGGER] && x[DQ] == 0 && x[SQ] == 0) 
			x[COUNT]++;
        while (str[x[IX]] && ms_isws(str[x[IX]])) 
			x[IX]++;
    }
    return (x[COUNT]);
}

void	fill_split(char **split, char *str)
{
	int		x[3];
	int		trigger;
	char	qt;

	if (ms_setint(&x[I], 0), ms_setint(&x[J], 0), ms_setchar(&qt, 0), str)
		(void) str;
	while (ms_setint(&x[K], 0), str[x[I]])
	{
		trigger = 0;
		while ((str[x[I]] && !ms_isws(str[x[I]])) || (str[x[I]] && (qt & DQ || qt & SQ)))
		{
			qt ^= (str[x[I]] == DQUOTE) << SQ;
			qt ^= (str[x[I]] == SQUOTE) << DQ;
			trigger = 1;
			x[K]++;
			x[I]++;
		}
        if (trigger == 1 && !(qt & DQ) && !(qt & SQ))
		{
			split[x[J]] = ft_substr(str, x[I] - x[K], x[K]);
			x[J]++;
		}
		while (str[x[I]] && ms_isws(str[x[I]]))
			x[I]++;
	}
}

char	*r_dollarquestion(char *split, int *i, t_tok *tdata)
{
	char *p1;
	char *var;
	char *p2;

	p1 = ft_substr(split, 0, *i);
	var = ft_itoa(tdata->exitno);
	p2 = ft_substr(split, *i + 2, (ft_strlen(split) - (*i + 2)));
	*i += ft_strlen(var);
	split = ft_sprintf("%s%s%s", p1, var, p2);
	return (split);
}

char *r_dollar(char *split, int *i, int start, t_env *denv)
{
	char *p1;
	char *var;
	char *p2;
	const int end = *i;

	p1 = ft_substr(split, 0, start - 1);
	var = ms_getenv(ft_substr(split, start, end - start), denv);
	// (void) denv;
	// var = getenv(ft_substr(split, start, end - start));
	p2 = ft_substr(split, end, (ft_strlen(split) - end));
	*i = ft_strlen(split) - ft_strlen(p2);
	if (!var)
		split = ft_sprintf("%s%s%s", p1, var, p2);
	else
		split = ft_sprintf("%s%fs%s", p1, var, p2);
	return (split);
}

char *r_env(char *split, t_tok *tdata, t_env *denv)
{
	int	i;
	int start;

	i = 0;
	while (split[i])
	{
		if (!ft_strncmp(&split[i], "$?", 2))
			split = r_dollarquestion(split, &i, tdata);
		if (split[i] == '$')
		{
			if (split[i + 1])
				i++;
			start = i;
			while (split[i] && ms_strstrchr(split[i], "\'$* =") == TRUE)
				i++;
			split = r_dollar(split, &i, start, denv);
		}
		i++;
	}
	return (split);
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

void transform_split(char **split, t_tok *tdata, t_env *denv)
{
	t_starlist *strl;
	int	x[2];

	x[I] = 0;
	strl = NULL;
	while (ms_setint(&x[J], ZERO), split[x[I]])
	{
		// ft_printf("--------------------------------\n");
		while (split[x[I]][x[J]])
        {
			// ft_printf("J === %d, char = %c\n", x[J], split[x[I]][x[J]]);
			if (split[x[I]][x[J]] != '\'' && split[x[I]][x[J]] != '\"')
				ms_starlab(&strl, ms_starlnew(r_env(ms_extract(split[x[I]], &x[J], ZERO), tdata, denv), 0));
			else if (split[x[I]][x[J]] == '\"')
				ms_starlab(&strl, ms_starlnew(r_env(ms_extract(split[x[I]], &x[J], '\"'), tdata, denv), 0));
			else if (split[x[I]][x[J]] == '\'')
				ms_starlab(&strl, ms_starlnew(ms_extract(split[x[I]], &x[J], '\''), 0));
        }
		free(split[x[I]]);
		split[x[I]] = w_expand(ms_starjoin(&strl), denv);
		ms_starclear(&strl);
		x[I]++;
	}
}

char	**dupdup(void)
{
	char **self;
	
	self = ft_calloc(2, sizeof(char *));
	self[0] = ft_calloc(2, sizeof(char));
	return (self);
}

char	**ft_splitm(char *str, t_tok *tdata, t_env *denv)
{
	char	**split;
	int		wc;

	// printf("EXITNO  %d\n", tdata->exitno);
	// ft_printf("%d %d", quotes[0], quotes[1]);
	wc = count_words(str);
	// printf("STR = %s, WC = %d\n", str, wc);
	// printf("SQ = %d, DQ = %d\n", quotes[0], quotes[1]);
	// printf("WC = %d\n", wc);
	split = (char **) ft_calloc(count_words(str) + 1, sizeof(char *));
	if (!split)
	{
		return (dupdup());
	}
	fill_split(split, str);
	for(int i = 0; split[i]; i++)
		printf("SPLIT[%d] = %s\n", i, split[i]);
	transform_split(split, tdata, denv);
	// for(int k = 0; split[k]; k++)
	// 	printf("STR[%d] %s\n", k, split[k]);
	return (split);
}

