/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:51:26 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/18 14:17:14 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int count_words(char *str)
{
    int x[5];

    if (ms_setint(&x[0], 0), ms_setint(&x[1], 0), ms_setint(&x[2], 0), ms_setint(&x[3], 0), str)
		(void) str;
    while (str[x[1]])
    {
		x[4] = 0;
        while ((str[x[1]] && !ms_isws(str[x[1]])) || (str[x[1]] && (x[2] || x[3])))
        {
            if (str[x[1]] == DQUOTE) 
				x[2] ^= 1;
            if (str[x[1]] == SQUOTE) 
				x[3] ^= 1;
            x[4] = 1; 
			x[1]++;
        }
        if (x[4] && x[2] == 0 && x[3] == 0) 
			x[0]++;
        while (str[x[1]] && ms_isws(str[x[1]])) 
			x[1]++;
    }
    return (x[0]);
}

void	fill_split(char **split, char *str)
{
	int	x[3];
	int qt[2];
	int	trigger;

	x[I] = 0;
	x[J] = 0;
	qt[DQ] = 0;
	qt[SQ] = 0;
	while (ms_setint(&x[K], 0), str[x[I]])
	{
		trigger = 0;
		while ((str[x[I]] && !ms_isws(str[x[I]])) || (str[x[I]] && (qt[DQ] == 1 || qt[SQ] == 1)))
		{
			if (str[x[I]] == DQUOTE)
				qt[DQ] ^= 1;
			if (str[x[I]] == SQUOTE)
				qt[SQ] ^= 1;
			trigger = 1;
			x[K]++;
			x[I]++;
		}
		if (trigger == 1 && qt[DQ] == 0 && qt[SQ] == 0)
		{
			split[x[J]] = ft_substr(str, x[I] - x[K], x[K]);
			x[J]++;
		}
		while (str[x[I]] && ms_isws(str[x[I]]))
			x[I]++;
	}
}

char *r_env(char *split, t_tok *tdata)
{
	int	i;
	int start;
	int end;
	char *p1;
	char *var;
	char *p2;

	i = 0;
	while (split[i])
	{
		if (!ft_strncmp(&split[i], "$?", 2))
		{
			p1 = ft_substr(split, 0, i);
			var = ft_itoa(tdata->exitno);
			p2 = ft_substr(split, i + 2, (ft_strlen(split) - (i + 2)));
			i += ft_strlen(var);
			split = ft_sprintf("%s%s%s", p1, var, p2);
		}
		if (split[i] == '$')
		{
			if (split[i + 1])
				i++;
			start = i;
			while (split[i] && split[i] != ' ' && split[i] != '\'' && split[i] != '$' && split[i] != '*')
				i++;
			end = i;
			p1 = ft_substr(split, 0, start - 1);
			var = getenv(ft_substr(split, start, end - start));
			p2 = ft_substr(split, end, (ft_strlen(split) - end));
			i = ft_strlen(split) - ft_strlen(p2);
			if (!var)
				split = ft_sprintf("%s%s%s", p1, var, p2);
			else
				split = ft_sprintf("%s%fs%s", p1, var, p2);
			// new = ft_sprintf("%s%s%s", p1, var, p2);
			// printf("P1 = %s\nP2 = %s\nVAR = %s\n", p1, p2, var);
		}
		i++;
	}
	return (split);
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
	flist = NULL;
	flist = get_flist(denv);
	slist = NULL;
	slist = ms_starsplit(word);
	current = slist;
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
	if (!flist)
		return (word);
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

	(*j) += (c != ZERO);
	if (c == ZERO)
		while (split[*j] && (split[*j] != '\'' && split[*j] != '\"'))
			(*j)++;
	else
		while (split[*j] && split[*j] != c)
			(*j)++;
	return (ft_substr(split, start, *j - start));
}

void transform_split(char **split, t_tok *tdata, t_env *denv)
{
	t_starlist *strl;
	int	x[2];

	x[I] = 0;
	strl = NULL;
	while (ms_setint(&x[J], ZERO), split[x[I]])
	{
		while (split[x[I]][x[J]])
			if (split[x[I]][x[J]] != '\'' && split[x[I]][x[J]] != '\"')
				ms_starlab(&strl, ms_starlnew(r_env(ms_extract(split[x[I]], &x[J], ZERO), tdata), 0));
			else if (split[x[I]][x[J]] == '\"')
				ms_starlab(&strl, ms_starlnew(r_env(ms_extract(split[x[I]], &x[J], '\"'), tdata), 0));
			else if (split[x[I]][x[J]] == '\'')
				ms_starlab(&strl, ms_starlnew(ms_extract(split[x[I]], &x[J], '\''), 0));
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
	printf("WC = %d\n", wc);
	split = (char **) ft_calloc(count_words(str) + 1, sizeof(char *));
	if (!split)
	{
		return (dupdup());
	}
	fill_split(split, str);
	transform_split(split, tdata, denv);
	// for(int k = 0; split[k]; k++)
	// 	printf("STR[%d] %s\n", k, split[k]);
	return (split);
}

