/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:51:26 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/17 16:29:34 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <sys/types.h>

static int	count_words(char *str)
{
	int	i;
	int	trigger;
	int count;
	int	dt;

	count = 0;
	i = 0;
	dt = 0;
	while (str[i])
	{
		trigger = 0;
		while ((str[i] && !ms_isws(str[i])) || (str[i] && dt == 1))
		{
			if (str[i] == DQUOTE)
				dt ^= 1;
			trigger = 1;
			i++;
		}
		if (trigger == 1 && dt == 0)
			count++;
		while (str[i] && ms_isws(str[i]))
			i++;
	}
	return (count);
}

void	fill_split(char **split, char *str)
{
	int	i;
	int	j;
	int	k;
	int	dt;
	int	st;
	int	trigger;

	i = 0;
	j = 0;
	k = 0;
	dt = 0;
	st = 0;
	while (str[i])
	{
		trigger = 0;
		k = 0;
		while ((str[i] && !ms_isws(str[i])) || (str[i] && (dt == 1 || st == 1)))
		{
			if (str[i] == DQUOTE)
				dt ^= 1;
			if (str[i] == SQUOTE)
				st ^= 1;
			trigger = 1;
			k++;
			i++;
		}
		if (trigger == 1 && dt == 0)
		{
			split[j] = ft_substr(str, i - k, k);
			j++;
		}
		while (str[i] && ms_isws(str[i]))
			i++;
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
			while (split[i] && split[i] != ' ' && split[i] != '\'' && split[i] != '$')
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

int	no_quotes(char *split)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (split[i])
	{
		if (split[i] == DQUOTE || split[i] == SQUOTE)
			return (ERROR);
		i++;
	}
	return (0);
}

int	last_quote(char *split)
{
	int	i;
	int quote;

	i = 0;
	quote = 0;
	while (split[i])
	{
		if (split[i] == DQUOTE || split[i] == SQUOTE)
			quote = i;
		i++;
	}
	return (quote);
}

int	find_star(char *word)
{
	int	i;

	i = -1;
	while(word[++i])
		if (word[i] == '*')
			return (1);
	return (ERROR);
}

void	ms_matchstart(t_dlist *el, char *to_match)
{
	int	i;
	int	tm_len;

	i = 0;
	tm_len = ft_strlen(to_match);
	if (!ft_strncmp(el->str, to_match, tm_len))
		el->i = tm_len;
	else
		el->i = ERROR;
}

void  ms_matchmid(t_dlist *el, char *to_match)
{
	int tm_len;
	int	str_len;
	int	valid;

	tm_len = ft_strlen(to_match);
	str_len = ft_strlen(el->str);
	valid = 0;
	while (el->str[el->i] && el->i <= str_len - tm_len)
	{
		if (!ft_strncmp(&el->str[el->i], to_match, tm_len))
        {
			el->i += tm_len;
			valid = 1;
			break;
        }
		el->i++;
	}
	if (valid == 0) 
		el->i = ERROR;
}

void ms_matchend(t_dlist *el, char *to_match)
{
	int	tm_len;
	int	str_len;

	tm_len = ft_strlen(to_match);
	str_len = ft_strlen(el->str);
	if (!ft_strncmp(&el->str[str_len - tm_len], to_match, tm_len))
		el->i = str_len;
	else
		el->i = ERROR;
}

void ms_del_hidden(t_dlist *el, char *to_match)
{
	(void) to_match;
	if (el->str[0] == '.')
		el->i = ERROR;
}

int	ms_dlstlen(t_dlist **flist)
{
	t_dlist *current;
	int		i;

	current = *flist;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

void ms_dswapstr(t_dlist *current, t_dlist *next)
{
	char	*tmp;

	tmp = ft_strdup(next->str);
	free(next->str);
	next->str = ft_strdup(current->str);
	free(current->str);
	current->str = tmp;
}

char *ms_lowdelspec(char *str)
{
	char *cpy;
	int	i;

	i = -1;
	cpy = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[++i])
		cpy[i] = ft_tolower(str[i]);
	// printf("||%s||\n", cpy);
	return (cpy);
}

int ms_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void ms_dlsort(t_dlist **flist)
{
	t_dlist *current;
	int		i;
	int	const list_len = ms_dlstlen(flist);
	char	*cstrcpy;
	char	*nstrcpy;

	i = 0;
	while (i < list_len)
    {
		current = *flist;
		while (current->next)
		{
			cstrcpy = ms_lowdelspec(current->str);
			nstrcpy = ms_lowdelspec(current->next->str);
			// printf("Current->str = %s, next %s\n", current->str, current->next->str);
			if(ms_strcmp(cstrcpy, nstrcpy) > 0)
				ms_dswapstr(current, current->next);
			current = current->next;
			free(cstrcpy);
			free(nstrcpy);
		}
		i++;
    }
}

char	*w_expand(char *word, t_env *denv)
{
	t_dlist		*flist;
	t_starlist	*slist;
	t_starlist	*current;
	int			dot_trigger;
	char		*newword;

	if (find_star(word) == ERROR || !word)
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
	// ft_printf("REGEX = %fs\n", word);
	// ft_printf("Printing the resulting list -->\n");
	// ms_dprint(&flist);
	// ft_printf("THIS IS THE WORD : %fs\n", word);
	free(word);
	newword = ms_starjoin(&flist);
	ms_dlstclear(&flist);
	ms_starclear(&slist);
	// ft_printf("WORD = %fs", word);
	// ms_starclear(&slist);

	return (newword);
}

char *ms_sstarjoin(t_starlist **slist)
{
    if (!slist || !*slist) return NULL;

    t_starlist *current = *slist;
    char *new = ft_strdup("");
    char *temp;

    while (current != NULL) {
        temp = ft_strjoin(new, current->str);
        free(new);
        new = temp;
        current = current->next;
    }
    return new;
}

char *find_bquote(char *split, int	*j)
{
	int const start = *j;

	while (split[*j] && (split[*j] != '\'' && split[*j] != '\"'))
		(*j)++;
	return (ft_substr(split, start, *j - start));
}

char *find_dquote(char *split, int *j)
{
	int const start = *j + 1;

	(*j)++;
	while (split[*j] && split[*j] != '\"')
		(*j)++;
	return (ft_substr(split, start, *j - start));
}

char *find_squote(char *split, int *j)
{
	int const start = *j + 1;

	(*j)++;
	while (split[*j] && split[*j] != '\'')
		(*j)++;
	return (ft_substr(split, start, (*j - start)));
}

void transform_split(char **split, t_tok *tdata, t_env *denv)
{
	t_starlist *strl;
	int	i;
	int	j;

	i = 0;
	strl = NULL;
	while (split[i])
	{
		j = 0;
		while (split[i][j] && j < (int) ft_strlen(split[i]))
		{
			if (split[i][j] != '\'' && split[i][j] != '\"')
				ms_starlab(&strl, ms_starlnew(r_env(find_bquote(split[i], &j), tdata), 0));
			else if (split[i][j] == '\"')
				ms_starlab(&strl, ms_starlnew(r_env(find_dquote(split[i], &j), tdata), 0));
			else if (split[i][j] == '\'')
				ms_starlab(&strl, ms_starlnew(find_squote(split[i], &j), 0));
		}
		free(split[i]);
		split[i] = w_expand(ms_sstarjoin(&strl), denv);
		ms_starclear(&strl);
		i++;
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

