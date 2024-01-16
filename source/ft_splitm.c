/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:51:26 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/16 16:29:18 by bvan-pae         ###   ########.fr       */
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

char *t_squote(char *split, int *j)
{
	int	i;
	int start;
	int end;
	char *p1;
	char *new;
	char *p2;

	i = 0;
	while(split[i] && split[i] != SQUOTE)
		i++;
	start = i + 1;
	i++;
	while (split[i] && split[i] != SQUOTE)
		i++;
	end = i;
	p1 = ft_substr(split, 0, start - 1);
	new = ft_substr(split, start, end - start);
	p2 = ft_substr(split, end + 1, (ft_strlen(split) - end));
	// printf("p1 : %s, new : %s, p2 : %s\n", p1, new, p2);
	char *final = ft_sprintf("%s%s%s", p1, new, p2);
	// printf("final : %s\n", final);
	*j = end - 1;
	return (final);
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

char *t_dquote(char *split, int *j, t_tok *tdata)
{
	int	i;
	int	start;
	int	end;
	char *p1;
	char *new;
	char *p2;

	i = 0;
	while (split[i] && split[i] != DQUOTE)
		i++;
	start = i + 1;
	i++;
	while (split[i] && split[i] != DQUOTE)
		i++;
	end = i;
	p1 = ft_substr(split, 0, start - 1);
	new = r_env(ft_substr(split, start, end - start), tdata);
	p2 = ft_substr(split, end + 1, (ft_strlen(split) - end));
	*j = ft_strlen(p1) + ft_strlen(new);
	// printf("POINTER = %d\n", *j);
	return(ft_sprintf("%s%s%s", p1, new, p2));
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

char	*w_expand(char *word, t_env *denv)
{
	t_dlist		*flist;
	t_starlist	*slist;
	t_starlist	*current;

	flist = NULL;
	flist = get_flist(denv);
	// denv->flist = get_flist(denv);
	if (find_star(word) == ERROR || !word)
	{
		// ms_dlstclear(&flist);
		return (word);
	}
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
	// ft_printf("REGEX = %fs\n", word);
	// ft_printf("Printing the resulting list -->\n");
	// ms_dprint(&flist);
	ft_printf("THIS IS THE WORD : %fs\n", word);
	word = ms_starjoin(&flist, word);
	// ms_dlstclear(&flist);
	// ms_starclear(&slist);
	// ft_printf("WORD = %fs", word);
	// ms_starclear(&slist);

	return (word);
}

void	transform_split(char **split, t_tok *tdata, t_env *denv)
{
	int	i;
	int	j;
	int k;

	i = 0;
	j = 0;
	while (split[i])
	{
		j = 0;
		k = 0;
		while(split[i][j] && split[i][j] != DQUOTE && split[i][j] != SQUOTE)
        {
			j++;
			k++;
        }
		split[i] = ft_sprintf("%s%s", w_expand(r_env(ft_substr(split[i], 0, k), tdata), denv), ft_substr(split[i], k, ft_strlen(split[i]) - k));
		while (split[i][j] && j < last_quote(split[i]))
		{
			if (split[i][j] == SQUOTE)
			{
				split[i] = t_squote(split[i], &j);
				// printf("SRESTE = %s\n",split[i]);
			}
			if (split[i][j] == DQUOTE)
			{
				split[i] = t_dquote(split[i], &j, tdata);
				// printf("DRESTE = %s\n",split[i]);
			}
			j++;
		}
		j--;
		// printf("J et LEN = %d %zu\n", j, ft_strlen(split[i]));
		// printf("P1 : %s SUB : %s\n", ft_substr(split[i], 0, j), r_env(ft_substr(split[i], j, ft_strlen(split[i]) - j), tdata));
		split[i] = ft_sprintf("%s%fs", ft_substr(split[i], 0, j), r_env(ft_substr(split[i], j, ft_strlen(split[i]) - j), tdata), denv);
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

	printf("EXITNO  %d\n", tdata->exitno);
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

